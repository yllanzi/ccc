
#ifndef __TEST_NODE_H
#define __TEST_NODE_H

#include <omnetpp.h>
#include "comm.h"
#include "Data_m.h"
#include "Nack_m.h"
using std::string;
namespace test {
class SendReceive : public cSimpleModule
{


private:
    double txRate;
    cPar *pkLenBits;
    cModule *destination;
    simtime_t radioDelay;
    double errorRate;
    int nexthop;
    int battery;
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
     cOutVector  battry;
};

}; // namespace

#endif


