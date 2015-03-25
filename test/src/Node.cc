//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Node.h"
#include "comm.h"
#include <string>


using std::string;
namespace test {

Define_Module(Node);
Node::Node()
{

    timerMsg = NULL;
    blength =10;
    Nbuf[10];

}

void Node::initialize()
{
      timerMsg = new cMessage("timer");
      scheduleAt(simTime(), timerMsg);

      seq = 0;

      //init ָ��
      head = tail =0;//�����ȳ�������ģ��
}

void Node::handleMessage(cMessage *msg)
{
    EV << "HELLO THIS IS NODE, START HANDLING THE TIMERMSG" <<endl;
  ASSERT(msg==timerMsg);
    pkLenBits = &par("pkLenBits");
            txRate = par("txRate");
            sink = simulation.getModuleByPath("sink");
            if (!sink) error("sink not found"); //����Ѱ�ҽڵ�

            int n = seq%10; //define the position of the buffer

          NodeBuf  a ;

          a.data =dblrand()*100;
          a.seq = seq;
 char pkname[40];
         sprintf(pkname,"this is seq = %d ,and data is %lf",  seq++,a.data);
         EV << "generating packet " << pkname << endl;
         Data *p = createPkt();
         simtime_t duration = p->getBitLength() / txRate;
         sendDirect(p, radioDelay, duration, sink->gate("in"));
//seq++;


 //   EV <<"HELLO ,THIS IS NODE , HANDLE FINISHED " << endl;


    scheduleAt(simTime()+par("sendInterval").doubleValue(),timerMsg);

}
Data *Node::createPkt(){
    double data = dblrand();
    char temp[20];
    sprintf(temp,"Node[%d] send %lf",data);
    Data *pkt  = new Data(temp);
 //   pkt->setName("hello");
    pkt->setBitLength(pkLenBits->longValue());
    pkt->setSource(5);
    pkt->setSeq(seq);
    pkt->setData(data);
    return pkt;
}


}; // namespace
