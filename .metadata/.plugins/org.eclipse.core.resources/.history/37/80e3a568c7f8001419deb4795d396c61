
package test;

simple Sink
{
    parameters:
         bool sendInitialMessage = default(false);
        @signal[state](type="long");
        @statistic[radioState](source="state";title="Radio state";enum="IDLE=0,TRANSMIT=1";record=vector);
        double txRate @unit(bps);         // transmission rate
        double radioDelay @unit(s);       // propagation delay of radio link
      volatile int pkLenBits @unit(b);
        
        @display("i=device/antennatower");
    gates:
        input in @directIn;
        
}
