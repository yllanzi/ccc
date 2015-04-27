
#ifndef __TEST_NODE_H
#define __TEST_NODE_H

#include <omnetpp.h>
#include "Data_m.h"
using std::string;
namespace test {
class nQueue : public cSimpleModule
{
private:
    int seq;
    cPacketQueue queue;
    Data *q[40];
    cArray buf;
    int qlength;


protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    Data *createPkt(double data);
};

}; // namespace

#endif


