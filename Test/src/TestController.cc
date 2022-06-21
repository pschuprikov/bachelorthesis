#include "TestController.h"

#include <inet/common/InitStages.h>
#include <memory>
#include <tools.h>
#include <algorithms.h>
#include <multicast.h>
#include <algorithm>


Define_Module(TestController);

void TestController::initialize(int stage) {
    if (stage == inet::INITSTAGE_TRANSPORT_LAYER) {
        EV_INFO << "Initializing multicast tunnels" << std::endl;

        topology_ = std::make_unique<TrafficEngineering::Topology>(TrafficEngineering::makeTopologyFromCurrentNetwork());

        const char *replicaType = par("replicaType").stringValue();

        inet::cTopology topology;
        topology.extractByNedTypeName(omnetpp::cStringTokenizer(replicaType).asVector());

        for (int i = 0; i < topology.getNumNodes(); i++) {
            auto const topoNode = topology.getNode(i);
            auto const senderMod = topoNode->getModule();
            auto const senderNode = senderMod->getParentModule();
            auto const senderName = std::string(senderNode->getFullPath());

            std::vector<std::string> receivers{};
            for (int j = 0; j < topology.getNumNodes(); j++) {
                if (i != j) {
                    receivers.push_back(topology.getNode(j)->getModule()->getParentModule()->getFullPath());
                }
            }
            EV_INFO << "creating tunnels from " << senderName << std::endl;
            for (auto const& receiver : receivers) {
                EV_INFO << " to " << receiver << std::endl;
            }
            createTunnel(senderName, receivers, senderMod->par("multicastAddress"));
        }
    };
}

void TestController::createTunnel(std::string const& sender,
                                  std::vector<std::string> const& receivers,
                                  std::string const& multicastAddress) {
    TrafficEngineering::MulticastRequest request;
    request.appOwnerName = sender;
    request.appReceiverNames = receivers;
    if (std::find(begin(receivers), end(receivers), sender) != end(receivers)) {
        throw omnetpp::cRuntimeError("sender can't be among receivers");
    }
    TrafficEngineering::Tunnel tunnel = optimization(*topology_, tunnels_, request);
    addMulticastGroup(this, tunnel, multicastAddress);
}
