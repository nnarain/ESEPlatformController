
ESE Platform Controller
=======================

The Platform Controller is a, HCS12 based, embedded system designed to control a robot platform in a future project.

It is responsible for controlling the platform's DC motors, angling a camera using a stepper and servo. It also controls a LCD display for status messages, has accelerometer input, a DAC and a CAN Bus. 

The platform controller communicates to a host through serial interface using an ASCII protocol.

Note this code uses CodeWarrior to compile, included in just individual modules and no project files.

Modules
-------

* Serial Communication Interface
* Indicator LEDs
* LCD
* Servo
* PWM

Utilities
---------

* Bit operation macros
* delay

Protocol
--------

The Platform controller uses an ASCII protocol for communication wish the host. Using this form of protocol allows better cross communication with varying host platforms.

The protocol consists of sending text packets in the form:

	<CMD ARG1 ARG2 ARG3 ... ARGx>

* Packet enclosed with '<' and '>'
* The instruction to the platform is issued with CMD (must be first)
* Any number of arguments delimited by a space character

For example the ping instruction looks like:

	<P>

* 'P' command
* No arguments

List of Valid Instructions
--------------------------

Info
----

**Related blog posts**

[HCS12 Design Complete](http://nnarain.github.io/2015/02/28/HCS12%20Board%20Complete!.html)

[Board Assembly](http://nnarain.github.io/2015/03/18/Board%20Assembly!!!.html)

[Board Bring Up](http://nnarain.github.io/2015/03/27/Board%20Bring%20Up.html)


