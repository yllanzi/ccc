
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
    NodeBuf Nbuf[];
    int i;
    int head,tail;//记录队列头尾
    //缓冲区长度
    int blength;
    volatile int seq;//节点中seq序号，作为初始值为0
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    NodeBuf newBuf(); //初始化节点中的数据
    void newData(int i); //给定序号，将相应的节点放入数据，相当于产生新数据。
};

}; // namespace

#endif


