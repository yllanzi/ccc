
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
    state = hstate = 0;
    Time.setName("time");
    qlength.setName("length of the queue");

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
            else {n.insert(pk);EV <<"INSERT ONE TO QUEUE n \n";}
            cMessage *notice = new cMessage("notice");
        int lq = n.length()+d.length();
        if(lq == 0){
            state = 1;
        }
        else
            state = 1;
            //state = lq/ln + 0.8*hstate;

        double t=2.0;
        if(state == 1){
            t = 0.001;//dblrand()/10;
        }
        else
            t = 0.005;///ln/((state+1)*dblrand()*5);
        //schedule the task
        scheduleAt(simTime()+dblrand(),notice);
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
