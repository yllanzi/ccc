
#ifndef __TEST_DELAYCONTROL_H
#define __TEST_DELAYCONTROL_H

#include <omnetpp.h>
#include "Data_m.h"
using std::string;
namespace test {
class DelayControl : public cSimpleModule
{
private:
    cPacketQueue d;
    cPacketQueue n;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

};

}; // namespace

#endif


