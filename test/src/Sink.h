
#ifndef __TEST_SINK_H
#define __TEST_SINK_H

#include <omnetpp.h>
#include "Data_m.h"
#include "Nack_m.h"

namespace test {
class Sink : public cSimpleModule
{
private:
    // parameters
    simtime_t radioDelay;
    double txRate;
    cPar *pkLenBits;
    int seq[30];
    cModule *node;
    cMessage *endTxEvent;
    int checkPoint;
    bool miss;
    int  misq[30];
    int key;
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    Nack *createNack();
    bool isCheckPoint(int seq, int next);
    void sendNack(Data *p);
};

}; // namespace

#endif


