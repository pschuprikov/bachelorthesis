//
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
#include "inet/applications/base/ApplicationPacket_m.h"
#include "inet/applications/udpapp/CoordApp.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/TimeTag_m.h"
#include "inet/common/packet/Packet.h"
#include "inet/networklayer/common/FragmentationTag_m.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"

namespace inet {

Define_Module(CoordApp);

CoordApp::~CoordApp()
{
    cancelAndDelete(selfMsg);
}

void CoordApp::initialize(int stage)
{
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        numReceived = 0;
        numReceived = 0;
        WATCH(numReceived);

        localPort = par("localPort");
        destPort = par("destPort");

        startTime = par("startTime");
        stopTime = par("stopTime");


        if (stopTime >= SIMTIME_ZERO && stopTime < startTime)
            throw cRuntimeError("Invalid startTime/stopTime parameters");
        selfMsg = new cMessage("UDPSinkTimer");
    }
}

void CoordApp::handleMessageWhenUp(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        ASSERT(msg == selfMsg);
        switch (selfMsg->getKind()) {
            case START:
                processStart();
                break;

            case STOP:
                processStop();
                break;

            default:
                throw cRuntimeError("Invalid kind %d in self message", (int)selfMsg->getKind());
        }
    }
    else if (msg->arrivedOn("socketIn"))
        socket.processMessage(msg);
    else
        throw cRuntimeError("Unknown incoming gate: '%s'", msg->getArrivalGate()->getFullName());
}

void CoordApp::socketDataArrived(UdpSocket *socket, Packet *packet)
{
    // process incoming packet
    processPacket(packet);
}

void CoordApp::socketErrorArrived(UdpSocket *socket, Indication *indication)
{
    EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
    delete indication;
}

void CoordApp::socketClosed(UdpSocket *socket)
{
    if (operationalState == State::STOPPING_OPERATION)
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void CoordApp::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();

    char buf[50];
    sprintf(buf, "rcvd: %d pks", numReceived);
    getDisplayString().setTagArg("t", 0, buf);
}

void CoordApp::finish()
{
    ApplicationBase::finish();
    EV_INFO << getFullPath() << ": received " << numReceived << " packets\n";
}

void CoordApp::setSocketOptions()
{
    bool receiveBroadcast = par("receiveBroadcast");
    if (receiveBroadcast)
        socket.setBroadcast(true);

    socket.setCallback(this);
}

void CoordApp::processStart()
{
    socket.setOutputGate(gate("socketOut"));
    socket.bind(localPort);
    setSocketOptions();

    const char *destAddrs = par("destAddresses");
    cStringTokenizer tokenizer(destAddrs);
    const char *token;

    while ((token = tokenizer.nextToken()) != nullptr) {
        if (strstr(token, "Broadcast") != nullptr)
            destAddresses.push_back(Ipv4Address::ALLONES_ADDRESS);
        else {
            L3Address addr = L3AddressResolver().resolve(token);
            destAddresses.push_back(addr);
        }
    }

    numReplicas = par("numReplicas");

    if (stopTime >= SIMTIME_ZERO) {
        selfMsg->setKind(STOP);
        scheduleAt(stopTime, selfMsg);
    }
}

void CoordApp::processStop()
{
   socket.close();
}

Packet *CoordApp::createPacket(int transactionId, msgType type, bool value)
{
    char msgName[32];

    if (type == PREPARE) sprintf(msgName, "prepare-T%d", transactionId);
    else if (type == COMMIT) sprintf(msgName, "commit-T%d [%d]", transactionId, value);
    else if (type == RESPONSE) sprintf(msgName, "response-T%d [%d]", transactionId, value);

    Packet *pk = new Packet(msgName);

    const auto& payload = makeShared<ApplicationPacket>();
    long msgLength = type == PREPARE ? 3236 : 36;
    payload->setChunkLength(B(msgLength/8.0));
    payload->setSequenceNumber(numSent);
    payload->addTag<CreationTimeTag>()->setCreationTime(simTime()); //difference between tag and addPar? not sure where to add transaction details



    pk->insertAtBack(payload);
    pk->addPar("TransactionId") = transactionId;
    pk->addPar("Type")  = type;
    pk->addPar("Value") = value;
    pk->addPar("msgId") = numSent;

    return pk;
}



void CoordApp::broadcastToReplicas(int transactionId, msgType type, bool value) {
    for(auto addr : destAddresses) {
        Packet * toSend = createPacket(transactionId, type, value);
        socket.sendTo(toSend, addr, destPort);
    }
}


void CoordApp::processPacket(Packet *pk)
{
    EV_INFO << "Received packet: " << UdpSocket::getReceivedPacketInfo(pk) << endl;
    emit(packetReceivedSignal, pk);

    int transactionId = (int) pk->par("TransactionId").longValue();

    numReceived++;
    switch (pk->par("Type").longValue()) {

        case REQUEST: {
            clientAddress[transactionId] = pk->getTag<L3AddressInd>()->getSrcAddress();
            currentTransactions[transactionId] = 0;
            startTimes[transactionId] = simTime();
            broadcastToReplicas(transactionId, PREPARE);
            break;
        }

        case VOTE: {
            if (currentTransactions.count(transactionId)) {
                if (pk->par("Value").boolValue()) {
                    currentTransactions[transactionId]++; //increase votes for the transaction

                    EV_INFO << "Received "<< currentTransactions[transactionId] << " out of " << numReplicas << " votes for: " << transactionId << endl;

                    if (currentTransactions[transactionId] == numReplicas) {

                        //throughput stats
                        emit(registerSignal("successfulThroughput"), (simTime() - startTimes[transactionId]));
                        startTimes.erase(transactionId);


                        socket.sendTo(createPacket(transactionId, RESPONSE, true), clientAddress[transactionId], destPort); //send response to client - can be done after acknowledgements
                        currentTransactions[transactionId] = 0; //reset counter to count ack
                        broadcastToReplicas(transactionId, COMMIT, true);
                    }
                } else {
                    EV_INFO << "Received NO vote " << endl;

                    emit(registerSignal("unsuccessfulThroughput"), (simTime() - startTimes[transactionId]));
                    startTimes.erase(transactionId);

                    socket.sendTo(createPacket(transactionId, RESPONSE, false), clientAddress[transactionId], destPort);
                    currentTransactions.erase(transactionId);
                    broadcastToReplicas(transactionId, COMMIT, false);
                }

            }
            break;
        }

        case ACKNOWLEDGE: {
            currentTransactions[transactionId]++;
            if (currentTransactions[transactionId] == numReplicas) {
                //socket.sendTo(createPacket(transactionId, RESPONSE, true), clientAddress[transactionId], destPort);
                currentTransactions.erase(transactionId);
            }
            break;
        }

        default: {
            throw cRuntimeError("Invalid kind %d in self message", (int)pk->par("Type").longValue());
        }
    }
    delete pk;
}

void CoordApp::handleStartOperation(LifecycleOperation *operation)
{
    simtime_t start = std::max(startTime, simTime());
    if ((stopTime < SIMTIME_ZERO) || (start < stopTime) || (start == stopTime && startTime == stopTime)) {
        selfMsg->setKind(START);
        scheduleAt(start, selfMsg);
    }
}

void CoordApp::handleStopOperation(LifecycleOperation *operation)
{
    cancelEvent(selfMsg);
    socket.close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}

void CoordApp::handleCrashOperation(LifecycleOperation *operation)
{
    cancelEvent(selfMsg);
    if (operation->getRootModule() != getContainingNode(this)) {     // closes socket when the application crashed only
        socket.destroy();    //TODO  in real operating systems, program crash detected by OS and OS closes sockets of crashed programs.
    }
}

} // namespace inet

