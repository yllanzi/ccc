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

#include "SendReceive.h"
#include "comm.h"
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
