#ifndef TEST_CONTROLLER_H
#define TEST_CONTROLLER_H

#include <inet/common/InitStages.h>
#include <omnetpp.h>
#include <memory>
#include <Tunnel.h>
#include <Topology.h>

class TestController : public omnetpp::cSimpleModule {
    public:
        void createTunnel(std::string const& sender, 
                          std::vector<std::string> const& receivers, 
                          std::string const& multicastAddress);
    protected:
        void initialize(int stage) override;
        virtual int numInitStages() const override { return inet::NUM_INIT_STAGES; }
    private:
        std::unique_ptr<TrafficEngineering::Topology> topology_;
        std::vector<TrafficEngineering::Tunnel> tunnels_;
};

#endif
