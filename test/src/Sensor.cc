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

#include "Sensor.h"
#include "comm.h"
#include <string>


using std::string;
namespace test {

Define_Module(Sensor);

void Sensor::initialize()
{
      timerMsg = new cMessage("timer");
      scheduleAt(simTime(), timerMsg);
}

void Sensor::handleMessage(cMessage *msg)
{
    double data = dblrand()*10;
    char temp[30];
    sprintf(temp,"%f",data);
    cMessage *sendata = new cMessage(temp);
    send(sendata,"out");
//    scheduleAt(simTime()+par("sendInterval").doubleValue(),timerMsg);
    scheduleAt(simTime()+dblrand(),timerMsg);


}


}; // namespace
