#include "Sensor.h"
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
    bubble("Get a new data!");
    send(sendata,"out");
    scheduleAt(simTime()+dblrand(),timerMsg);
}


}; // namespace
