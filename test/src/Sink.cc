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

void Sink::initialize() //��Ӱ������
{
        pkLenBits = &par("pkLenBits");
        txRate = par("txRate");
        for(int i=0;i<30;i++) seq[i]=0;//each node just have one seq[i]

}

void Sink::handleMessage(cMessage *msg)
{
    Data *p = check_and_cast<Data *>(msg);
if(p->hasBitError()){
    delete(msg);
    EV << "CHECK THE MSG ,FOUND ERROR \n";
}
else{
    int src = p->getSource();

    if(seq[src] != p->getSeq()){
        EV << "NODE[" << p->getSeq() <<"]  seq = "<<p->getSeq()<<"\n";
        bubble("send Nack ");
        pkLenBits = &par("pkLenBits");
        txRate = par("txRate");
        seq[src] = p->getSeq(); //update the
        char dest[10];
        sprintf(dest,"node[%d]",src);
        node = simulation.getModuleByPath(dest);
        if (!node) error("node not found");
            char pkname[40];
            sprintf(pkname,"NACK send to node[%d]",src);
            cPacket *pk = new cPacket(pkname);
           pk->setBitLength(pkLenBits->longValue());
           simtime_t duration = pk->getBitLength() / txRate;
           sendDirect(pk, radioDelay, duration, node->gate("in"));

    }
    seq[src]++;



}
// ��   EV << "SINK IS OK , HANDEL FINISHED" << endl;
}
}; // namespace
