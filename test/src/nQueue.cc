#include "nQueue.h"
#include <Data_m.h>
#include "Nack_m.h"
#include <string>
using std::string;
namespace test {

Define_Module(nQueue);
//module nQueue is used to receive the data,generate Message and add it to the queue.
//if the node is not busy, it will send message to DelayControl. Candice Jiang
void nQueue::initialize()
{
    seq = 0;
    all = wrong = 0.0;
    qlength = queue.length();
    rate.setName("rate of channel");
    s = par("num");
    dest = getModuleByPath("Gateway")->getId();

}

void nQueue::handleMessage(cMessage *msg)
{
    all++;
    if(msg->getArrivalGateId() == this->gate("in")->getId()){
        //receive data from sensor
         double data = atof(msg->getName());
         Data *pkt = createPkt(data);
         queue.insert(pkt->dup());
         int i =buf.add(pkt);
         EV << "the data index = "<< i <<"\n";
         send(pkt->dup(),"control");
         seq++;
    }
    else{ //receive NACK
         Nack *nack =  check_and_cast<Nack *>(msg);
         if(nack->getSource() != getParentModule()->getId()){
             this->getParentModule()->bubble("cqueue receive Nack");
             wrong++;
             int num = nack->getNum();
             int seq;
             for(int i=0;i<num;i++){
                 seq = nack->getSeq(i);
                 EV <<seq <<"will get from buf buf length is"<<buf.size()<<"\n";
                 if(seq <buf.size()){
            Data *ack =  check_and_cast<Data *>(buf.get(seq)->dup());
                                //  给出头的消息副本next
                    char temp[30];
               sprintf(temp,"resend data %lf,seq = %d",ack->getData(),ack->getSeq());
                 ack->setName(temp);
                 ack->setState(nack->getStatus());
                 EV << "NODE RECEIVE NACK FORM SINK, THE STATE OF SINK = " <<nack->getStatus()<<"\n";
                 ack->setType(1);//the data was missed in the previous transmit.
                 send(ack,"control");
             }
             }

        }

         else {send(nack,"control"); EV <<"SELF NACK SEND TO CONTROL\n";}// if NACK packet is generate from self,send directly.
    }
    double r = (all-wrong)/all;
    rate.record(r);

}
Data *nQueue::createPkt(double data){
    char temp[20];

    sprintf(temp," %s send %lf",getParentModule()->getName(),data);
    Data *pkt  = new Data(temp);
    pkt->setSource(getParentModule()->getId());
    pkt->setDest(dest);
    pkt->setSeq(seq);
    pkt->setData(data);
    pkt->setType(0);//zero means this is sensor data
    pkt->setState(5);

    return pkt;
}

}; // namespace
