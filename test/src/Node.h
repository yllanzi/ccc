
#ifndef __TEST_NODE_H
#define __TEST_NODE_H

#include <omnetpp.h>

namespace test {
class Node : public cSimpleModule
{
private:
    // parameters
    simtime_t radioDelay;
    double txRate;
    cPar *pkLenBits;


    // state variables, event pointers etc
    cModule *sink;
    cMessage *endTxEvent;
    enum {IDLE=0, TRANSMIT=1} state;
    simsignal_t stateSignal;




protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);


};

}; // namespace

#endif


