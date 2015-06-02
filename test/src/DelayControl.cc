
#include "DelayControl.h"
#include "comm.h"
#include <string>
#include "Data_m.h"
#include "Nack_m.h"


using std::string;
namespace test {

Define_Module(DelayControl);

void DelayControl::initialize()
{
    lastTime = simTime();
    ln = 0;
    lq = 0;
    state = hstate = 1;
    Time.setName("time");
    qlength.setName("length of the queue");
    getstatus.setName("status of nack");
}

void DelayControl::handleMessage(cMessage *msg)
{
    int flag=0;
    int nstate=0;
    if(msg->isSelfMessage()){//send package directly
        EV<<"SELF MESSAGE\n";
        if(n.length()!=0)
            send(n.pop(),"send");
        else
            send(d.pop(),"send");
        }
    else{
        try{//if Data type
            Data *pk = check_and_cast<Data *>(msg);
            if(pk->getType()==0){//this is new data from sensor
                pk->setState(state);
                d.insert(pk->dup());
                EV <<"INSERT ONE TO QUEUE d\n";
            }
            else {
                ln = pk->getState();
                EV << "this is Dc receive resend data,STATE GOT FROM NQUQUE" <<pk->getState() <<"\n";
                pk->setState(state);
                n.insert(pk->dup());

            EV <<"INSERT ONE TO QUEUE n \n";}

            cMessage *notice = new cMessage("notice");
        int lq = n.length()+d.length();
        if(lq == 0){
            state = 1;
        }
        else
           // state = 1;
            state = lq/(ln+1) + 0.8*hstate;
        EV << state <<"  lq = "<<lq <<" ln = "<< ln <<"hstate = "<< hstate<<"\n" ;

        double t=2.0;
        if(state == 1 || ln == 1){ //have no data to send or next hop is free
            t = dblrand()*0.5;
        }
        else
            t = dblrand()*ln/(state+1); //((state+1)*5)/nextS/ln*dblrand();//ln*dblrand()/((state+1)*5)
            pk->setState(state);
        //schedule the task
        scheduleAt(simTime()+t,notice);
        Time.record(t);
        qlength.record(state);
        lastTime = lastTime +t;
     }
        catch(...)//Nack which will be send to source (as a sink)
        {
           Nack *pk = check_and_cast<Nack *>(msg);
           pk->setStatus(state);
           EV << "THIS IS dCONTROL, state = "<<state <<"\n";
           send(pk,"send");
        }
    }
}






}; // namespace
