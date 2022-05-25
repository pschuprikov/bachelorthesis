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
#include <math.h>
#include "inet/applications/base/ApplicationPacket_m.h"
#include "inet/applications/udpapp/ReplicaApp.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/TimeTag_m.h"
#include "inet/common/packet/Packet.h"
#include "inet/networklayer/common/FragmentationTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"

namespace inet {

Define_Module(ReplicaApp);

ReplicaApp::~ReplicaApp()
{
    cancelAndDelete(selfMsg);
}

void ReplicaApp::initialize(int stage)
{
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        numReceived = 0;
        numReceived = 0;
        currentlyProcessing = 0;


        WATCH(numReceived);

        localPort = par("localPort");
        destPort = par("destPort");

        startTime = par("startTime");
        stopTime = par("stopTime");
        messageLengthPar = &par("messageLength");

        if (stopTime >= SIMTIME_ZERO && stopTime < startTime)
            throw cRuntimeError("Invalid startTime/stopTime parameters");
        selfMsg = new cMessage("ReplicaAppTimer");
    }
}

void ReplicaApp::handleMessageWhenUp(cMessage *msg)
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

void ReplicaApp::socketDataArrived(UdpSocket *socket, Packet *packet)
{
    // process incoming packet
    processPacket(packet);
}

void ReplicaApp::socketErrorArrived(UdpSocket *socket, Indication *indication)
{
    EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
    delete indication;
}

void ReplicaApp::socketClosed(UdpSocket *socket)
{
    if (operationalState == State::STOPPING_OPERATION)
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void ReplicaApp::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();

    char buf[50];
    sprintf(buf, "rcvd: %d pks", numReceived);
    getDisplayString().setTagArg("t", 0, buf);
}

void ReplicaApp::finish()
{
    ApplicationBase::finish();
    EV_INFO << getFullPath() << ": received " << numReceived << " packets\n";
}

void ReplicaApp::setSocketOptions()
{
    bool receiveBroadcast = par("receiveBroadcast");
    if (receiveBroadcast)
        socket.setBroadcast(true);

    socket.setCallback(this);
}

void ReplicaApp::processStart()
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

    destAddr = destAddresses[0];


    if (stopTime >= SIMTIME_ZERO) {
        selfMsg->setKind(STOP);
        scheduleAt(stopTime, selfMsg);
    }
}

void ReplicaApp::processStop()
{
   socket.close();
}



Packet *ReplicaApp::createCommitResponsePacket(int transactionId,  msgType type)
{
    Packet *pk = new Packet(msgName);

    const auto& payload = makeShared<ApplicationPacket>();
    long msgByteLength = *messageLengthPar;
    payload->setChunkLength(B(msgByteLength));
    payload->setSequenceNumber(numSent);
    payload->addTag<CreationTimeTag>()->setCreationTime(simTime());

    pk->insertAtBack(payload);
    pk->addPar("TransactionId") = transactionId;
    pk->addPar("Type")  = type;
    pk->addPar("msgId") = numSent;


    char msgName[32];

    if (type == VOTE) {
        int simultaneousTransactions = currentlyProcessing > 0 ? currentlyProcessing : 1;
        bool vote = cComponent::uniform(0, 1) >= pow(0.09 * simultaneousTransactions,2)+0.05; //randomly decide whether transaction can be prepared

        sprintf(msgName, "Vote-T%d [%d]", transactionId, vote);

        pk->addPar("Value") = vote;

    } else if (type == ACKNOWLEDGE) {
        sprintf(msgName, "ACK-T%d", transactionId, vote);
    }



    return pk;
}


void ReplicaApp::processPacket(Packet *pk)
{
    EV_INFO << "Received packet: " << UdpSocket::getReceivedPacketInfo(pk) << endl;
    emit(packetReceivedSignal, pk);



    numReceived++;

    switch (pk->par("Type").longValue()) {
        case PREPARE: {
            currentlyProcessing++;
            Packet * toSend = createCommitResponsePacket(pk->par("TransactionId").longValue());
            socket.sendTo(toSend, destAddr, destPort);
            break;
        }

        case COMMIT: {
            currentlyProcessing--;
            //SHOULD ADD THE ACKNOWLEDGEMENT
            break;
        }

        default: {
            throw cRuntimeError("Invalid kind %d in message", (int)pk->par("Type").longValue());
        }
    }

    delete pk;
}

void ReplicaApp::handleStartOperation(LifecycleOperation *operation)
{
    simtime_t start = std::max(startTime, simTime());
    if ((stopTime < SIMTIME_ZERO) || (start < stopTime) || (start == stopTime && startTime == stopTime)) {
        selfMsg->setKind(START);
        scheduleAt(start, selfMsg);
    }
}

void ReplicaApp::handleStopOperation(LifecycleOperation *operation)
{
    cancelEvent(selfMsg);
    socket.close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}

void ReplicaApp::handleCrashOperation(LifecycleOperation *operation)
{
    cancelEvent(selfMsg);
    if (operation->getRootModule() != getContainingNode(this)) {     // closes socket when the application crashed only
        socket.destroy();    //TODO  in real operating systems, program crash detected by OS and OS closes sockets of crashed programs.
    }
}

} // namespace inet

