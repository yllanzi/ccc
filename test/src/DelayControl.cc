
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
    ln = 1;
    lq = 0;
    state = hstate = 1;
    Time.setName("time");
    qlength.setName("length of the queue");
    nextS=1;
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
            if(pk->getType()==0){//this is normal data
                ln = pk->getState();
                d.insert(pk);
                EV <<"INSERT ONE TO QUEUE d\n";
            }
            else {n.insert(pk);

            EV <<"INSERT ONE TO QUEUE n \n";}
            cMessage *notice = new cMessage("notice");
        int lq = n.length()+d.length();
        if(lq == 0){
            state = 1;
        }
        else
           // state = 1;
            state = lq/ln + 0.8*hstate;

        double t=2.0;
        if(state == 1 || nextS){ //have no data to send
            t = dblrand()*nextS;
        }
        else
            t = ((state+1)*5)/nextS/ln*dblrand();//ln*dblrand()/((state+1)*5)
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
           send(pk,"send");
        }
    }
}






}; // namespace
