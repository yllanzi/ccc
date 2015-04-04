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

package test;

//
// Immediately sends out any message it receives. It can optionally generate
// a message at the beginning of the simulation, to bootstrap the process.
//
module Node
{
   
        
        parameters:
        bool sendInitialMessage = default(false);
        @signal[state](type="long");
        @statistic[radioState](source="state"; title="Radio state"; enum="IDLE=0,TRANSMIT=1"; record=vector);
        double txRate @unit(bps);         // transmission rate
        double radioDelay @unit(s);       // propagation delay of radio link
        volatile int pkLenBits @unit(b);
        volatile double sendInterval @unit(s) = default(exponential(1s));
        @display("i=device/antennatower_s");
    gates:
        input in @directIn;
    submodules:
        data: Sensor {
            parameters:
            	@display("p=36,56");
        }
        queue: nQueue {
            parameters:
           		@display("p=115,56");
        }
        sr: SendReceive {
            parameters:
                txRate = txRate;
            	pkLenBits = pkLenBits;
            	@display("p=204,56");
            
                
        }
    connections:
        data.out --> queue.in;
        queue.sr <--> sr.queue;
        in --> sr.in;
        sr.out --> {ber = 0.999;} --> sr.In; //use bit error rate to replace the lost rate of the network
}
