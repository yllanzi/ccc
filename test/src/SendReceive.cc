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

}

void SendReceive::handleMessage(cMessage *msg)
{

    if(msg->getArrivalGateId() == this->gate("queue$i")->getId()){
        send(msg,"out");
        bubble("@@@@@@@@@@@@@@");
    }
    else if(msg->getArrivalGateId() == this->gate("in")->getId())
    {
        bubble("receive Nack");//===================================
    }
    else { //send directly to the sink===========gate("In")=========



        bubble("error packet!!");
     pkLenBits = &par("pkLenBits");
           txRate = par("txRate");
           destination = simulation.getModuleByPath("sink");

           Data *pk = check_and_cast<Data *>(msg);
           if(pk->hasBitError())bubble("error packet!!");
           simtime_t duration = pkLenBits->longValue()/ txRate;
           sendDirect(pk, radioDelay, duration, destination->gate("in"));

       // bubble("lost packet");
}
   //
}


}; // namespace
