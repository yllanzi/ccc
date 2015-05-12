
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
    simtime_t lastTime;
    int ln,lq;
    int state,hstate; //current state and histroty state
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    double getNexTime(int lq,int ln);
    cOutVector Time;
    cOutVector qlength;
};

}; // namespace

#endif


