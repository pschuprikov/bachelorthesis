/*
 * tictocFunction.cc
 *
 *  Created on: 3 Apr 2022
 *      Author: luca
 */




#include <String.h>
#include <omnetpp.h>

using namespace omnetpp;

class tictocNode: public cSimpleModule {

protected:
    void initialize() override;
    void handleMessage(cMessage * msg) override;

};

Define_Module(tictocNode); //register Omnet++

void tictocNode::initialize() {
    if (strcmp("tic", getName()) == 0) {
        cMessage * msg = new cMessage("hello world");
        send(msg, "portOut");
    }
}

void tictocNode::handleMessage(cMessage * msg) {
    send(msg, "portOut");
}
