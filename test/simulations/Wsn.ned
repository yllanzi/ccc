package test.simulations;

import test.Node;
import test.Sink;

network Wsn
{
    parameters:
        double txRate @unit(bps);
        int num;
        double errorRate;
    submodules:
        Sink: Sink {
            @display("p=237,347");
        }
        Sink2: Sink {
            @display("p=129,190");
        }
        Gateway: Sink {
            @display("p=264,42");
        }
        Sensor_0: Node {
            parameters:
                errorRate = errorRate;
                @display("p=195,42");
		}
        Sensor_1: Node {
            parameters:
                errorRate = errorRate;
                @display("p=264,130");

        }
        Sensor_2: Node {
            parameters:
                errorRate = errorRate;
                @display("p=59,92");

        }
        Sensor_3: Node {
            parameters:
                errorRate = errorRate;
                @display("p=151,115");

        }
        Sensor_4: Node {
            parameters:
                errorRate = errorRate;
                @display("p=39,167");

        }
        Sensor_5: Node {
            parameters:
                errorRate = errorRate;
                @display("p=190,221");

        }
        Sensor_6: Node {
            parameters:
                errorRate = errorRate;
                @display("p=76,268");

        }
        Sensor_7: Node {
            parameters:
                errorRate = errorRate;
                @display("p=264,244");
        }
        Sensor_8: Node {
            parameters:
                errorRate = errorRate;
                @display("p=178,298");
        }
        Sensor_9: Node {
            parameters:
                errorRate = errorRate;
                @display("p=190,378");
        }
        Sensor_10: Node {
            parameters:
                errorRate = errorRate;
                @display("p=107,378");
        }
}
