# Embedded network project
This is a small project to play around with embedded systems. The current idea is to use a Raspberry Pi 4 which is
connected to a temperature sensor over I2C. The Pi will periodically read out the temperature from the sensor. This part
of the project is programmed in C.

The Pi will also be connected to a laptop via an Ethernet cable. It will transmit the temperature to the laptop where it
will be displayed graphically using a Qt C++ application.

## Current status
* Can communicate between laptop and Pi using ZMQ.
* The hardware (temperature sensor, buzzer, jumper cables, breadboards) has been ordered.

## Goal for today
* 2020-04-08: Create a Qt C++ GUI application: done
* 2020-04-09: Update graph axes on new data point. Send data from Pi to laptop and display on graph.
* 2020-04-10: Integrate ZMQ REQ/REP into main C++ program. Hope that hardware arrives.
    * Create start/stop measuring button.

