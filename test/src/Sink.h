
#ifndef __TEST_SINK_H
#define __TEST_SINK_H

#include <omnetpp.h>

namespace test {
class Sink : public cSimpleModule
{
private:
    // parameters
    simtime_t radioDelay;
    double txRate;
    cPar *pkLenBits;


    // state variables, event pointers etc
    cModule *node;
    cMessage *endTxEvent;
    enum {IDLE=0, TRANSMIT=1} state;
    simsignal_t stateSignal;




protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);


};

}; // namespace

#endif


