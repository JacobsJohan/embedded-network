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
* 2020-04-11: Configure Buildroot to build a bootable RPI4 image.
* 2020-04-13: Test I2C on the RPI4
* 2020-04-14: Use Bosch BMP280 API to read out temperature.
* 2020-04-15: Cross-compile libzmq for linux-arm-gnueabihf

## Configuring I2C on the RPI4
* Toggle *dtparam=i2c_arm=on* in ```/boot/config```. This can also be changed with **raspi-config**.

## ioctl() explained
[Detailed information](https://sysplay.github.io/books/LinuxDrivers/book/Content/Part09.html)

ioctl() is a Linux system call that stands for Input Output Control and is used for controlling hardware peripherals. It
is for example used to control the volume of an audio device, for the configuration of a video device or for reading out
device registers.


## Cross-compiling instructions
```
git clone https://github.com/zeromq/libzmq
cd libzmq
mkdir build_output
./autogen.sh
./configure --prefix=$(pwd)/build_output --host=arm-none-linux-gnueabi CC=arm-linux-gnueabi-gcc CXX=arm-linux-gnueabi-g++
make
make install
```
