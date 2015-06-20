
package test;
simple DelayControl
{
    parameters:
        @display("i=block/delay");
        int flag;
    gates:
      input receive;
      output send;
}