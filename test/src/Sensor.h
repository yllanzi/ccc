
#ifndef __TEST_NODE_H
#define __TEST_NODE_H

#include <omnetpp.h>
#include "comm.h"
#include "Data_m.h"
using std::string;
namespace test {
class Sensor : public cSimpleModule
{


private:
    // parameters
    simtime_t radioDelay;
    double txRate;
    cPar *pkLenBits;
    cMessage *timerMsg;
    // state variables, event pointers etc
    cModule *sink;
    NodeBuf Nbuf[];
    int i;
    int head,tail;
    int blength;
    int seq;
    cQueue queue;
    cArray array;
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
   // NodeBuf newBuf(); //
  //  void newData(int i); //

};

}; // namespace

#endif


