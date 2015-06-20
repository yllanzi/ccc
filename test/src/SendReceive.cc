#include "SendReceive.h"
#include <string>


using std::string;
namespace test {

Define_Module(SendReceive);

void SendReceive::initialize()
{
   errorRate = par("errorRate");
   nexthop = getModuleByPath(par("nexthop"))->getId();
   battery = 20000;
  battry.setName("energy release");
}

void SendReceive::handleMessage(cMessage *msg)
{
    battry.record(battery);
    if(msg->getArrivalGateId() == this->gate("in")->getId())
    {
     //   Nack *pk = check_and_cast<Nack *>(msg);

        send(msg->dup(),"queue");
        EV <<"SUCCESS SEND TO QUTUE";
        battery -= 10;

    }
    else { //send directly to the sink===========gate("In")=========

        pkLenBits = &par("pkLenBits");
           txRate = par("txRate");
           destination = simulation.getModule(nexthop);
           try{
                Data *pk = check_and_cast<Data *>(msg);
                if(dblrand()>errorRate)pk->setBitError(true);
                simtime_t duration = pkLenBits->longValue()/ txRate;
                sendDirect(pk, radioDelay, duration, destination->gate("in"));
                battery -= 10;
           }
           catch(...){
               Nack *pk = check_and_cast<Nack *>(msg);
               destination = simulation.getModule(pk->getDest());
               simtime_t duration =pkLenBits->longValue()/txRate;
               sendDirect(pk, radioDelay, duration,destination->gate("in"));
               battery -= 10;
           }

}
   //
}


}; // namespace
