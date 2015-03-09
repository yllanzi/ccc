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

#include "Node.h"

namespace test {

Define_Module(Node);

void Node::initialize()
{

    if (par("sendInitialMessage").boolValue()){
        pkLenBits = &par("pkLenBits");
        txRate = par("txRate");
        sink = simulation.getModuleByPath("sink");
        if (!sink) error("sink not found");
  //          else EV << toc << "lello---------\n";
            char pkname[40]="asdfdf";


       cPacket *pk = new cPacket(pkname);
       pk->setBitLength(pkLenBits->longValue());
       simtime_t duration = pk->getBitLength() / txRate;
       sendDirect(pk, radioDelay, duration, sink->gate("in"));
     //  scheduleAt(simTime(), endTxEvent);
    }

}

void Node::handleMessage(cMessage *msg)
{
    pkLenBits = &par("pkLenBits");
            txRate = par("txRate");
            sink = simulation.getModuleByPath("sink");
            if (!sink) error("sink not found");

                char pkname[40]="asdfdf";


           cPacket *pk = new cPacket(pkname);
           pk->setBitLength(pkLenBits->longValue());
           simtime_t duration = pk->getBitLength() / txRate;
           sendDirect(pk, radioDelay, duration, sink->gate("in"));
}

}; // namespace
