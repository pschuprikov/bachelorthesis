//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

// Created: 2022-3-15 for project Test

package test;

import ned.DatarateChannel;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;



module Pod2
{
    parameters:
        int k;
    gates:
        inout port[int((k/2)^2)];
        inout hosts[int((k/2)^2)];
    submodules:
        aggregateSwitch[int(k/2)]: Router;
        edgeSwitch[int(k/2)]: Router;
    connections:
        for i=0..sizeof(aggregateSwitch)-1, for j=0..int(k/2) - 1 {
            aggregateSwitch[i].ethg++ <--> port[i*int(k/2)+j];
        }

        for i=0..sizeof(hosts)-1 {
            hosts[i] <--> edgeSwitch[int(i%(k/2))].ethg++;

        }

        for i=0..sizeof(edgeSwitch)-1, for j=0..sizeof(aggregateSwitch)-1 {
            edgeSwitch[i].ethg++ <--> SwitchToSwitch <--> aggregateSwitch[j].ethg++;
        }

}

module Hosts
{
    parameters: 
        int k;
    gates:
        inout hosts[int((k^3)/4)];
       
    submodules:
        client: StandardHost;
        coordinator: StandardHost;
        replica[int(((k^3)/4)-2)]: StandardHost;
    connections:
        client.ethg++ <--> hosts[0];
        coordinator.ethg++  <--> hosts[1];
        
        for i=0..sizeof(replica)-1 {
            replica[i].ethg++ <--> hosts[i+2];
        }
            
    
}


network KFatTreeNew
{
    parameters:
        int k;

    submodules:
        coreSwitch[int((k/2)^2)]: Router;
        pod[k]: Pod2 {
            k = k;
        }
		hosts: Hosts {
		    k = k;
		}
        configurator: Ipv4NetworkConfigurator;

    connections:
        
        for i=0..sizeof(pod)-1, for j=0..sizeof(coreSwitch)-1 {
            pod[i].port++ <--> SwitchToSwitch <--> coreSwitch[j].ethg++;
        }
        
        for i=0..sizeof(pod)-1, for j=0..int((k/2)^2)-1 {
            hosts.hosts++<--> HostToSwitch <--> pod[i].hosts++;
        }

}
