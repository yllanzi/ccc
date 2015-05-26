
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
    double wrong;
    double all;
    int s;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    Data *createPkt(double data);
    cOutVector rate;
};

}; // namespace

#endif


