//
// Copyright (C) 2004 Andras Varga
// Copyright (C) 2000 Institut fuer Telematik, Universitaet Karlsruhe
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#ifndef __INET_UDPSINK_H
#define __INET_UDPSINK_H

#include "inet/common/INETDefs.h"

#include "inet/applications/base/ApplicationBase.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"
#include <omnetpp.h>

namespace inet {




/**
 * Consumes and prints packets received from the Udp module. See NED for more info.
 */
class INET_API ReplicaAppBroadcast : public ApplicationBase, public UdpSocket::ICallback
{

  protected:
    enum SelfMsgKinds { START = 1, STOP, CHECKINBOX };
    struct Comparator {
        bool operator()(Packet* lhs, const Packet* rhs) const {
            return lhs->getTimestamp() < rhs->getTimestamp();
        };
    };

    class DelayedQueue {
        private:

            std::map<Packet*, cMessage *, Comparator> store;
            simtime_t delay;


        public:
            DelayedQueue(simtime_t d) {
                delay = d;
            }


            //add packet to queue with timer to open queue
            void insert(ReplicaAppBroadcast * app,Packet * newPacket) {
                cMessage * timer = new cMessage("CheckInbox");
                timer->setTimestamp(delay);
                timer->setKind(CHECKINBOX);
                app->scheduleAt(simTime() + delay, timer);

                store.insert({newPacket, timer});
            }

            //open packets older than time (removing packets from queue and cancelling timers)
            std::vector<Packet *> openPackets(ReplicaAppBroadcast * app, simtime_t time){
                std::vector<Packet *> foundPackets;

                auto itr = store.begin();
                while ( itr != store.end() && itr->first->getTimestamp() <= time) {
                    //cancel timers
                    app->cancelAndDelete(itr->second);

                    foundPackets.push_back(itr->first);
                    itr = store.erase(itr);
                }
                return foundPackets;
            }
    };




    enum msgType {PREPARE, VOTE, RESPONSE};

    UdpSocket socket;
    int localPort, destPort = -1;
    std::vector<L3Address> destAddresses;
    L3Address destAddr;
    simtime_t startTime;
    simtime_t stopTime;
    cMessage *selfMsg = nullptr;
    int numReceived, numSent = 0;
    int currentlyProcessing = 0;

    //Packet * sorted by timestamp
    DelayedQueue inbox = DelayedQueue(0);


    //for debugging
    std::vector<int> order;


    std::map<int, std::set<int>> transactions; //(transactionId, set(replicasThatVoted) )
    std::map<int, L3Address> clientAddress; // (transactionId, addressOfClient )

    std::map<int, bool> decided;

    simtime_t maxTime = 0;
    simtime_t minTime = 10;

    int thisId;

    cPar *messageLengthPar = nullptr;

  public:
    ReplicaAppBroadcast() {}
    virtual ~ReplicaAppBroadcast();

  protected:
    virtual void processPacket(Packet *pk);
    virtual void processVote(Packet *pk);
    virtual void setSocketOptions();

  protected:
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessageWhenUp(cMessage *msg) override;
    virtual void finish() override;
    virtual void refreshDisplay() const override;

    virtual Packet* createVotePacket(int transactionId, bool vote, char* clientAddress);
    virtual void respondClient(int transactionId, bool vote);
    virtual void broadcastAll(int transactionId);

    virtual void socketDataArrived(UdpSocket *socket, Packet *packet) override;
    virtual void socketErrorArrived(UdpSocket *socket, Indication *indication) override;
    virtual void socketClosed(UdpSocket *socket) override;

    virtual void processStart();
    virtual void processStop();

    virtual void handleStartOperation(LifecycleOperation *operation) override;
    virtual void handleStopOperation(LifecycleOperation *operation) override;
    virtual void handleCrashOperation(LifecycleOperation *operation) override;
};

} // namespace inet




#endif // ifndef __INET_UDPSINK_H

