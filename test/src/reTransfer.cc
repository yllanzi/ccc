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

#include "reTransfer.h"
#include "comm.h"
#include <Data_m.h>
#include <Nack_m.h>
#include <string>
using std::string;
namespace test {

Define_Module(reTransfer);
//module nQueue is used to receive the data,generate Message and add it to the queue.
//if the node is not busy, it will send message to sr to send it.
void reTransfer::initialize()
{
      for(int i=0;i<30;i++) {
           seq[i]=0;//each node just have one seq[i]
           checkpt[i]=1;
      }
      miss = false;
     key = 0;//mark misnum in one group
     nack.setName("length of sink");
       int n=0;
}

void reTransfer::handleMessage(cMessage *msg)
{

    Data *p = check_and_cast<Data *>(msg);
        EV  << p->getType()<<"\n";

    if(p->hasBitError()){
        delete(msg);//MESSAGE WITH ERROR
     //   EV << "CHECK THE MSG ,FOUND ERROR \n";
    }
    //MESSAGE WITHOUT ERROR
    else if(p->getType() == 0){ //is new data
        int src = p->getSource();
        char temp[20]="";
        sprintf(temp,"%f",p->getData());
        cMessage *data = new cMessage(temp);
        send(data,"data");//send data to queue to generate a  new package;
                            //TO FORWARD THE PACKAGE

        if(isCheckPoint(p->getSeq(),p->getState(),p->getSource())){
            EV <<"CHECKING POINT***************************************************\n";
            if(miss){
                EV <<"CHECKING POINT******************************&&&&&&&&&&&&&&*\n";
                    sendNack(p);
                    miss =false;
                    key = 0;
                }
         }
        if(seq[src] != p->getSeq()){
            //update the check symbol
            miss = true;
            misq[key] = seq[src];
            key++;
            seq[src] = p->getSeq();
            seq[src]++;
            }
        }
        else {
            //is  missing data
            bubble("receive the missing data");
            EV << p->getType()<<" receive the missing data\n";
    }
  //  send(p->dup(),"")
}
Nack *reTransfer::createNack(){
    char temp[20];
    sprintf(temp,"Nack %d",seq[0]);
    Nack *pkt = new Nack(temp);
    for(int i=0;i<key;i++){
       pkt->setSeq(i,misq[i]);
       EV << misq[i] <<" ";
    }
    EV <<" =================\n";

    pkt->setSource(getParentModule()->getId());
    pkt->setNum(key);
    pkt->setStatus(1000);
    pkt->setFinalkey(key);


return pkt;
}
bool reTransfer::isCheckPoint(int seq,int next,int source){

    if(seq >= checkpt[source]){
        checkpt[source] += next;
        return true;
    }
    else
        return false;
}
void reTransfer::sendNack(Data *p){

    //notice the user

    bubble("Found packet missing,send Nack");

    //set destination
    char dest[10];//请确认sr中是否有定位目的接点的职责
    sprintf(dest,"node[%d]",p->getSource());
//    node = simulation.getModuleByPath(dest);
///   if (!node) error("node not found");

    //create the packet
    Nack *pk = createNack();//====================
    send(pk,"queue");
    EV <<"NACK PACKET GENERATED\n";
    //send to next level
 //   pk->setBitLength(pkLenBits->longValue());
 //   simtime_t duration = pk->getBitLength() / txRate;
 //   sendDirect(pk, radioDelay, duration, node->gate("in"));

    }
}; // namespace