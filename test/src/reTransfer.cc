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
try{
    Data *p = check_and_cast<Data *>(msg);
        EV  << p->getType()<<"\n";

    if(p->hasBitError()){
        delete(msg);//MESSAGE WITH ERROR
    }

    //MESSAGE WITHOUT ERROR
    else if(p->getDest()!= getParentModule()->getId()){  //the sink is not gateway
        if(p->getType() >= 0){ //
         int src = p->getSource();
        char temp[20]="";
        sprintf(temp,"%f",p->getData());
        cMessage *data = new cMessage(temp);
        send(data,"data");//send data to queue to generate a  new package;
                            //TO FORWARD THE PACKAGE

        if(isCheckPoint(p->getSeq(),p->getState(),p->getSource())){
            if(miss){
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
//===
    }
    else {
        getParentModule()->bubble("Gateway get data");
    }
}
catch(...){
        send(msg->dup(),"queue");//Nack from other nodes send to queue directly
}



}
Nack *reTransfer::createNack(int source){
    char temp[20];
    sprintf(temp,"Nack ask for %d packets",key);
    Nack *pkt = new Nack(temp);
    for(int i=0;i<key;i++){
       pkt->setSeq(i,misq[i]);
       EV << misq[i] <<"  ->";
    }
    EV <<source<<" =================\n";
    pkt->setDest(source);
    pkt->setSource(getParentModule()->getId());
    pkt->setNum(key);
    pkt->setStatus(0);
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

    //create the packet
    Nack *pk = createNack(p->getSource());
    send(pk,"queue");
    EV <<"NACK PACKET GENERATED\n";
    }
}; // namespace
