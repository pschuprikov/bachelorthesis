package test;

@license(LGPL);


import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import ned.DatarateChannel;

network Network
{
    parameters:
        int k; //number of ports per router
    @display("bgb=566,455");
    types:
        channel HostToSwitch extends DatarateChannel
        {
            datarate = 10Gbps;
        }
        channel SwitchToSwitch extends DatarateChannel
        {
            datarate = 100Gbps;
        }
    submodules:
        standardHost: StandardHost {
            @display("p=63,368");
        }
        standardHost1: StandardHost {
            @display("p=161,368");
        }
        router: Router {
            @display("p=134,295");
        }
        router1: Router {
            @display("p=309,302");
        }
        router2: Router {
            @display("p=134,207");
        }
        standardHost2: StandardHost {
            @display("p=276,368");
        }
        standardHost3: StandardHost {
            @display("p=374,368");
        }
        router3: Router {
            @display("p=309,207");
        }
        router4: Router {
            @display("p=113,112");
        }
        router5: Router {
            @display("p=260,112");
        }
        router6: Router {
            @display("p=385,112");
        }
        router7: Router {
            @display("p=522,112");
        }
    connections:
        router2.ethg[0] <--> SwitchToSwitch <--> router.ethg[0];
        router.ethg[0] <--> SwitchToSwitch <--> router3.ethg[0];
        router1.ethg[0] <--> SwitchToSwitch <--> router2.ethg[0];
        router1.ethg[0] <--> SwitchToSwitch <--> router3.ethg[0];
        standardHost.ethg[0] <--> HostToSwitch <--> router.ethg[0];
        standardHost1.ethg[0] <--> HostToSwitch <--> router.ethg[0];
        standardHost2.ethg[0] <--> HostToSwitch <--> router1.ethg[0];
        standardHost3.ethg[0] <--> HostToSwitch <--> router1.ethg[0];
        router2.ethg[0] <--> SwitchToSwitch <--> router4.ethg[0];
        router2.ethg[0] <--> SwitchToSwitch <--> router5.ethg[0];
        router3.ethg[0] <--> SwitchToSwitch <--> router6.ethg[0];
        router3.ethg[0] <--> SwitchToSwitch <--> router7.ethg[0];
}
