
#include "DelayControl.h"
#include "comm.h"
#include <string>
#include "Data_m.h"


using std::string;
namespace test {

Define_Module(DelayControl);

void DelayControl::initialize()
{

}

void DelayControl::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
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
                d.insert(pk);
            }
            else n.insert(pk);
            cMessage *hello = new cMessage("hello");
            scheduleAt(simTime(),hello);
        }
    EV <<simTime()<<"  CORRECT \n";


}


}; // namespace
