
#ifndef __TEST_NODE_H
#define __TEST_NODE_H

#include <omnetpp.h>
#include "comm.h"
#include "Data_m.h"
using std::string;
namespace test {
class SendReceive : public cSimpleModule
{


private:

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

};

}; // namespace

#endif


