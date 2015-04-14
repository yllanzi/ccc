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

#include "nQueue.h"
#include "comm.h"
#include <Data_m.h>
#include "Nack_m.h"
#include <string>



using std::string;
namespace test {

Define_Module(nQueue);
//module nQueue is used to receive the data,generate Message and add it to the queue.
//if the node is not busy, it will send message to sr to send it.
void nQueue::initialize()
{
    seq = 0;

}

void nQueue::handleMessage(cMessage *msg)
{
    if(msg->getArrivalGateId() == this->gate("in")->getId()){
        //receive data from sensor
         double data = atof(msg->getName());
         Data *pkt = createPkt(data);
         buf.insert(pkt);
         send(pkt->dup(),"sr$o");

         seq++;
    }
    else{
        this->getParentModule()->bubble("cqueue receive the packet");
        //Nack *ack =  check_and_cast<Nack *>(buf.pop()->dup());
        Data *ack =  check_and_cast<Data *>(buf.front()->dup());
        char temp[30];
        sprintf(temp,"resend data %lf",ack->getData());
        ack->setName(temp);
        ack->setType(1);//the data was missed in the previous transmit.
        send(ack,"sr$o");
    }

}
Data *nQueue::createPkt(double data){
    char temp[20];
    sprintf(temp," node[%d] send %lf",getParentModule()->getIndex(),data);
    Data *pkt  = new Data(temp);
    pkt->setSource(getParentModule()->getIndex());
    pkt->setSeq(seq);
    pkt->setData(data);
    pkt->setType(0);//zero means this is sensor data
    return pkt;
}

}; // namespace
