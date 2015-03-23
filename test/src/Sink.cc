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

#include "Sink.h"

namespace test {

Define_Module(Sink);

void Sink::initialize() //不影响运行
{
        pkLenBits = &par("pkLenBits");
        txRate = par("txRate");
   //     node = simulation.getModuleByPath("node");
   //     if (!node) error("Sink not found");
}

void Sink::handleMessage(cMessage *msg)
{
    /**
    pkLenBits = &par("pkLenBits");
            txRate = par("txRate");
            node = simulation.getModuleByPath("node");
            if (!node) error("sink not found");

                char pkname[40]="asdfdf";


           cPacket *pk = new cPacket(pkname);
           pk->setBitLength(pkLenBits->longValue());
           simtime_t duration = pk->getBitLength() / txRate;
           sendDirect(pk, radioDelay, duration, node->gate("in"));
*/
// 、   EV << "SINK IS OK , HANDEL FINISHED" << endl;
}
}; // namespace
