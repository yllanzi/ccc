
#include "DelayControl.h"
#include "comm.h"
#include <string>
#include "Data_m.h"


using std::string;
namespace test {

Define_Module(DelayControl);

void DelayControl::initialize()
{
lastTime = simTime();
ln = 1;
lq = 0;
state = hstate = 0;
Time.setName("time");
qlength.setName("length of the queue");
}

void DelayControl::handleMessage(cMessage *msg)
{
    int nstate=0;
    if(msg->isSelfMessage()){//send package directly
        EV<<"SELF MESSAGE\n";
        if(n.length()!=0)
        {
            send(n.pop(),"send");
        }else
        send(d.pop(),"send");
        }
    else{
            Data *pk = check_and_cast<Data *>(msg);
            if(pk->getType()==0){//this is normal data
                ln = pk->getState();
                d.insert(pk);
            }
            else n.insert(pk);
            cMessage *notice = new cMessage("notice");
            int lq = n.length()+d.length();
            if(lq == 0){
                state = 1;
            }
            else
                state = lq/ln + 0.8*hstate;
            EV << "STATE = "<<state <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            double t=2.0;
            if(state ==ln){
                t = dblrand()*2;
            }
            else
                t = ln/(state+1)*dblrand()*5;

            scheduleAt(lastTime+t,notice);
            Time.record(t);
            qlength.record(state);
            lastTime = lastTime +t;
       //     EV <<pk->getState()<<"this is status of sensor \n";
        }
    EV <<simTime()<<"  CORRECT \n";


}




}; // namespace
