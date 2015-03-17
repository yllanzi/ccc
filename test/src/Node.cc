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
#include "comm.h"
#include <string>

#include <cString>
using std::string;
namespace test {

Define_Module(Node);
Node::Node()
{
   i=0;
    timerMsg = NULL;

   *Nbuf = newBuf(10);
}

void Node::initialize()
{
      timerMsg = new cMessage("timer");
      scheduleAt(simTime(), timerMsg);
}

void Node::handleMessage(cMessage *msg)
{
    ASSERT(msg==timerMsg);
    pkLenBits = &par("pkLenBits");
            txRate = par("txRate");
            sink = simulation.getModuleByPath("sink");
            if (!sink) error("sink not found");




            cPacket *pk = new cPacket("hello");
           pk->setBitLength(pkLenBits->longValue());
           simtime_t duration = pk->getBitLength() / txRate;
           sendDirect(pk, radioDelay, duration, sink->gate("in"));

    scheduleAt(simTime()+par("sendInterval").doubleValue(),timerMsg);
    if(i<10)i=0;
    else i++;
}
NodeBuf *Node::newBuf(int i){
    NodeBuf buf[i];
    for(int j=0;j<i;j++){
        buf[i].seq = j;
        string str = "hello";
        strcpy(buf[i].data,str.c_str());

    }
    return buf;
}

}; // namespace
