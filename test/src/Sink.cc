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
#include "Nack_m.h"

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
 //   EV << "CHECK THE MSG ,FOUND ERROR \n";
}
else if(p->getType() == 0){
    int src = p->getSource();

    if(seq[src] != p->getSeq()){
        //set parameters
        pkLenBits = &par("pkLenBits");
        txRate = par("txRate");

        //notice the user
        EV << "NODE[" << p->getSeq() <<"]  seq = "<<p->getSeq()<<"\n";
        bubble("send Nack");

        //set destination
        char dest[10];
        sprintf(dest,"node[%d]",src);
        node = simulation.getModuleByPath(dest);
        if (!node) error("node not found");

        //create the packet
        Nack *pk = createNack(seq[src]);
        pk->setBitLength(pkLenBits->longValue());
        simtime_t duration = pk->getBitLength() / txRate;
        sendDirect(pk, radioDelay, duration, node->gate("in"));

        //update the check symbol
        seq[src] = p->getSeq();
        seq[src]++;
    }
    else {
        //receive the missing data
        bubble("receive the missing data");
    }




}
// ��   EV << "SINK IS OK , HANDEL FINISHED" << endl;
}

Nack *Sink::createNack(int seq){
    char temp[20];
    sprintf(temp,"Nack %d",seq);
    Nack *pkt = new Nack(temp);
    pkt->setSeq(0,seq);
    pkt->setNum(1);
    pkt->setStatus(0);

return pkt;
}
}; // namespace
