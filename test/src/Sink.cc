#include "Sink.h"
#include "Nack_m.h"

namespace test {

Define_Module(Sink);

void Sink::initialize()
{
        pkLenBits = &par("pkLenBits");
        txRate = par("txRate");
        for(int i=0;i<30;i++) {
            seq[i]=0;//each node just have one seq[i]
            checkpt[i]=1;
        }

        miss = false;
        key = 0;//mark misnum in one group
        nack.setName("length of sink");
        int n=0;
}

void Sink::handleMessage(cMessage *msg)
{
    Data *p = check_and_cast<Data *>(msg);
    EV  << p->getType()<<"\n";


if(p->hasBitError()){
    delete(msg);
 //   EV << "CHECK THE MSG ,FOUND ERROR \n";
}
else if(p->getType() == 0){ //is new data
    int src = p->getSource();
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
    else {
        //is  missing data
        bubble("receive the missing data");
        EV << p->getType()<<" receive the missing data\n";
}
// ��   EV << "SINK IS OK , HANDEL FINISHED" << endl;
}

Nack *Sink::createNack(){
    char temp[20];
    sprintf(temp,"Nack %d",seq[0]);
    Nack *pkt = new Nack(temp);
    for(int i=0;i<key;i++){
       pkt->setSeq(i,misq[i]);
       EV << misq[i] <<" ";
    }
    EV <<" =================\n";
    pkt->setNum(key);
    pkt->setStatus(1000);
    pkt->setFinalkey(key);

return pkt;
}
bool Sink::isCheckPoint(int seq,int next,int source){
    if(seq >= checkpt[source]){
        checkpt[source] += next;
        return true;
    }
    else
        return false;
}
void Sink::sendNack(Data *p){
    //set parameters
    pkLenBits = &par("pkLenBits");
    txRate = par("txRate");

    //notice the user
    EV << "NODE[" << p->getSeq() <<"]  seq = "<<p->getSeq()<<"\n";
    bubble("Found packet missing,send Nack");

    //set destination
    char dest[10];
    sprintf(dest,"node[%d]",p->getSource());
    node = simulation.getModuleByPath(dest);
    if (!node) error("node not found");

    //create the packet
    Nack *pk = createNack();//====================
    pk->setBitLength(pkLenBits->longValue());
    simtime_t duration = pk->getBitLength() / txRate;
    sendDirect(pk, radioDelay, duration, node->gate("in"));

    }
}; // namespace
