
#ifndef __TEST_NODE_H
#define __TEST_NODE_H

#include <omnetpp.h>
#include "comm.h"
using std::string;
namespace test {
class Node : public cSimpleModule
{
public :
    Node();

private:
    // parameters
    simtime_t radioDelay;
    double txRate;
    cPar *pkLenBits;
    cMessage *timerMsg;
    // state variables, event pointers etc
    cModule *sink;
    NodeBuf *Nbuf[];
    int i;
    NodeBuf *current;
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    NodeBuf *newBuf(int num);

};

}; // namespace

#endif


