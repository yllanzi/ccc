
#ifndef __TEST_NODE_H
#define __TEST_NODE_H

#include <omnetpp.h>
#include "Data_m.h"
#include <Nack_m.h>
using std::string;
namespace test {
class reTransfer : public cSimpleModule
{
private:
        int checkPoint;
        bool miss;
        int  misq[30];
        int checkpt[30];//this one is in use?
        int key;
        int seq[30];



protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    Nack *createNack(int source);
        bool isCheckPoint(int seq, int next,int source);
        void sendNack(Data *p);
        cOutVector nack;
};

}; // namespace

#endif


