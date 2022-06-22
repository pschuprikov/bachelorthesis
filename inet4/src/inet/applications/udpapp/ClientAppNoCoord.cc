//
// Copyright (C) 2000 Institut fuer Telematik, Universitaet Karlsruhe
// Copyright (C) 2007 Universidad de Málaga
// Copyright (C) 2011 Zoltan Bojthe
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//


#include "inet/applications/base/ApplicationPacket_m.h"
#include "inet/applications/udpapp/ClientAppNoCoord.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/TimeTag_m.h"
#include "inet/common/packet/Packet.h"
#include "inet/networklayer/common/FragmentationTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"

namespace inet {

EXECUTE_ON_STARTUP(
        cEnum * e = cEnum::find("inet::ChooseDestAddrMode");
        if (!e)
            OMNETPP6_CODE(omnetpp::internal::)enums.getInstance()->add(e = new cEnum("inet::ChooseDestAddrMode"));
        e->insert(ClientAppNoCoord::ONCE, "once");
        e->insert(ClientAppNoCoord::PER_BURST, "perBurst");
        e->insert(ClientAppNoCoord::PER_SEND, "perSend");
        );

Define_Module(ClientAppNoCoord);

int ClientAppNoCoord::counter;
int ClientAppNoCoord::transactionID;

simsignal_t ClientAppNoCoord::outOfOrderPkSignal = registerSignal("outOfOrderPk");

ClientAppNoCoord::~ClientAppNoCoord()
{
    cancelAndDelete(timerNext);
}

void ClientAppNoCoord::initialize(int stage)
{
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        counter = 0;
        numSent = 0;
        numReceived = 0;
        numDeleted = 0;
        numDuplicated = 0;

        successfulCommit = 0;

        transactionID = 0;

        delayLimit = par("delayLimit");
        startTime = par("startTime");
        stopTime = par("stopTime");
        if (stopTime >= SIMTIME_ZERO && stopTime <= startTime)
            throw cRuntimeError("Invalid startTime/stopTime parameters");

        sendIntervalPar = &par("sendInterval");
        nextSleep = startTime;
        nextBurst = startTime;
        nextPkt = startTime;
        dontFragment = par("dontFragment");

        WATCH(numSent);
        WATCH(numReceived);
        WATCH(numDeleted);
        WATCH(numDuplicated);

        localPort = par("localPort");
        destPort = par("destPort");

        timerNext = new cMessage("ClientAppNoCoordTimer");
    }
}

Packet *ClientAppNoCoord::createPreparePacket(int transId)
{
    char msgName[32];
    sprintf(msgName, "prepare-T%d", transId);

    Packet *pk = new Packet(msgName);

    const auto& payload = makeShared<ApplicationPacket>();
    payload->setChunkLength(B(3234/8.0));
    payload->setSequenceNumber(numSent);
    payload->addTag<CreationTimeTag>()->setCreationTime(simTime());



    pk->insertAtBack(payload);
    pk->addPar("TransactionId") = transId;
    pk->addPar("Type")  = PREPARE;
    pk->addPar("msgId") = numSent;

    return pk;
}

void ClientAppNoCoord::processStart()
{
    socket.setOutputGate(gate("socketOut"));
    socket.setCallback(this);
    socket.bind(localPort);

    bool joinLocalMulticastGroups = par("joinLocalMulticastGroups");
    if (joinLocalMulticastGroups) {
        MulticastGroupList mgl = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this)->collectMulticastGroups();
        socket.joinLocalMulticastGroups(mgl);
    }

    int timeToLive = par("timeToLive");
    if (timeToLive != -1)
        socket.setTimeToLive(timeToLive);

    int dscp = par("dscp");
    if (dscp != -1)
        socket.setDscp(dscp);

    int tos = par("tos");
    if (tos != -1)
        socket.setTos(tos);

    const char *destAddrs = par("destAddresses");
    cStringTokenizer tokenizer(destAddrs);
    const char *token;
    bool excludeLocalDestAddresses = par("excludeLocalDestAddresses");

    IInterfaceTable *ift = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);

    while ((token = tokenizer.nextToken()) != nullptr) {
        if (strstr(token, "Broadcast") != nullptr)
            destAddresses.push_back(Ipv4Address::ALLONES_ADDRESS);
        else {
            L3Address addr = L3AddressResolver().resolve(token);
            if (excludeLocalDestAddresses && ift && ift->isLocalAddress(addr))
                continue;
            destAddresses.push_back(addr);
        }
    }

    nextSleep = simTime();
    nextBurst = simTime();
    nextPkt = simTime();

    destAddr = destAddresses[0];

    timerNext->setKind(SEND);
    processSend();
}

void ClientAppNoCoord::processSend()
{
    if (stopTime < SIMTIME_ZERO || simTime() < stopTime) {
        //sendQuery(transactionID++);
        broadcastAll(transactionID++);
    }
}

void ClientAppNoCoord::broadcastAll(int transactionId) {
//    for (int i = 0; i < 1; ++i) {
//        Packet * toSend = createPreparePacket(transactionId);
//        socket.sendTo(toSend, destAddresses[i], destPort);
//    }

    for (auto addr : destAddresses) {
        Packet * toSend = createPreparePacket(transactionId);
        socket.sendTo(toSend, addr, destPort);
    }
}

void ClientAppNoCoord::sendQuery(int transId)
{
    Packet * pk = createPreparePacket(transId);
    pk->setTimestamp();
    emit(packetSentSignal, pk);
    socket.sendTo(pk, destAddr, destPort);
    lastSent = simTime();
    responsesReceived[transId] = 0;
}

void ClientAppNoCoord::processStop()
{
    socket.close();
    socket.setCallback(nullptr);
}

void ClientAppNoCoord::handleMessageWhenUp(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        switch (msg->getKind()) {
            case START:
                processStart();
                break;

            case SEND:
                processSend();
                break;

            case STOP:
                processStop();
                break;

            default:
                throw cRuntimeError("Invalid kind %d in self message", (int)msg->getKind());
        }
    }
    else
        socket.processMessage(msg);
}

void ClientAppNoCoord::socketDataArrived(UdpSocket *socket, Packet *packet)
{
    // process incoming packet
    processPacket(packet);
}

void ClientAppNoCoord::socketErrorArrived(UdpSocket *socket, Indication *indication)
{
    EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
    delete indication;
}

void ClientAppNoCoord::socketClosed(UdpSocket *socket)
{
    if (operationalState == State::STOPPING_OPERATION)
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void ClientAppNoCoord::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();

    char buf[100];
    sprintf(buf, "rcvd: %d pks\nsent: %d pks", numReceived, numSent);
    getDisplayString().setTagArg("t", 0, buf);
}

void ClientAppNoCoord::processPacket(Packet *pk)
{
    if (pk->getKind() == UDP_I_ERROR) {
        EV_WARN << "UDP error received\n";
        delete pk;
        return;
    }

    if (pk->hasPar("sourceId") && pk->hasPar("msgId")) {
        // duplicate control
        int moduleId = pk->par("sourceId");
        int msgId = pk->par("msgId");
        auto it = sourceSequence.find(moduleId);
        if (it != sourceSequence.end()) {
            if (it->second >= msgId) {
                EV_DEBUG << "Out of order packet: " << UdpSocket::getReceivedPacketInfo(pk) << endl;
                emit(outOfOrderPkSignal, pk);
                delete pk;
                numDuplicated++;
                return;
            }
            else
                it->second = msgId;
        }
        else
            sourceSequence[moduleId] = msgId;
    }

    if (delayLimit > 0) {
        if (simTime() - pk->getTimestamp() > delayLimit) {
            EV_DEBUG << "Old packet: " << UdpSocket::getReceivedPacketInfo(pk) << endl;
            PacketDropDetails details;
            details.setReason(CONGESTION);
            emit(packetDroppedSignal, pk, &details);
            delete pk;
            numDeleted++;
            return;
        }
    }

    if (pk->par("Type").longValue() == RESPONSE) {
        int transactionId = pk->par("TransactionId").longValue();
        responsesReceived[transactionId]++;

        EV_INFO << "RECEIVED RESPONSE " << responsesReceived[transactionId] << endl;

        if (responsesReceived[transactionId] == 1) {
            if (pk->par("Value").boolValue()) {
                emit(registerSignal("successfulTransactionLatency"), (simTime() - lastSent));
            } else {
                emit(registerSignal("unsuccessfulTransactionLatency"), (simTime() - lastSent));
            }
            scheduleAt(simTime()+ *sendIntervalPar, timerNext);
        }

        if (responsesReceived[transactionId] == destAddresses.size()) {
            EV_INFO << "RECEIVED ALL RESPONSES FOR T" << transactionId << endl;
        }


    }

    EV_INFO << "Received packet: " << UdpSocket::getReceivedPacketInfo(pk) << endl;
    emit(packetReceivedSignal, pk);
    numReceived++;
    delete pk;
}



void ClientAppNoCoord::finish()
{
    recordScalar("Total sent", numSent);
    recordScalar("Total received", numReceived);
    recordScalar("Total deleted", numDeleted);
    ApplicationBase::finish();
}

void ClientAppNoCoord::handleStartOperation(LifecycleOperation *operation)
{
    simtime_t start = std::max(startTime, simTime());

    if ((stopTime < SIMTIME_ZERO) || (start < stopTime) || (start == stopTime && startTime == stopTime)) {
        timerNext->setKind(START);
        scheduleAt(start, timerNext);
    }
}

void ClientAppNoCoord::handleStopOperation(LifecycleOperation *operation)
{
    if (timerNext)
        cancelEvent(timerNext);

    socket.close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}

void ClientAppNoCoord::handleCrashOperation(LifecycleOperation *operation)
{
    if (timerNext)
        cancelEvent(timerNext);

    if (operation->getRootModule() != getContainingNode(this))     // closes socket when the application crashed only
        socket.destroy();         //TODO  in real operating systems, program crash detected by OS and OS closes sockets of crashed programs.
}

} // namespace inet

