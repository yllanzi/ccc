
package test;
simple SendReceive
{
    parameters:
        double txRate @unit(bps);
        volatile int pkLenBits @unit(b);
        @display("i=block/process");
        double errorRate;
        string nexthop;
    gates:
      input in @directIn;
      output queue;
      input delay;
     
}
