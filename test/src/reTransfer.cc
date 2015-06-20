#include "reTransfer.h"

#include <Data_m.h>
#include <Nack_m.h>
#include <string>
using std::string;
namespace test {

Define_Module(reTransfer);
void reTransfer::initialize()
{
      for(int i=0;i<30;i++) {
           seq[i]=0;//each node just have one seq[i]
           checkpt[i]=1;
      }
      miss = false;
     key = 0;//mark misnum in one group
     nack.setName("num");
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
    else  //the sink is not gateway
        if(p->getType() >= 0){ //

             int src = p->getSource();
        if(p->getDest()!= getParentModule()->getId()){
        char temp[20]="";
        sprintf(temp,"%f",p->getData());
        cMessage *data = new cMessage(temp);
        send(data,"data");//send data to queue to generate a  new package;
                            //TO FORWARD THE PACKAGE
         }
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

    }
    pkt->setDest(source);
    pkt->setSource(getParentModule()->getId());
    pkt->setNum(key);
    pkt->setStatus(1);
    pkt->setFinalkey(key);
    nack.record(key);

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
    char dest[10];//璇风‘璁r涓槸鍚︽湁瀹氫綅鐩殑鎺ョ偣鐨勮亴璐�

    //create the packet
    Nack *pk = createNack(p->getSource());
    send(pk,"queue");
    EV <<"NACK PACKET GENERATED\n";
    }
}; // namespace
