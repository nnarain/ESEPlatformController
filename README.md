
ESE Platform Controller
=======================

The Platform Controller is a, HCS12 based, embedded system designed to control a robot platform in a future project.

It is responsible for controlling the platform's DC motors, angling a camera using a stepper and servo. It also controls a LCD display for status messages, has accelerometer input, a DAC and a CAN Bus. 

The platform controller communicates to a host through serial interface using an ASCII protocol.

Note this code uses CodeWarrior to compile, included in just individual modules and no project files.

Modules
-------

* Serial Communication Interface
* Serial Peripheral Interface
* Digital to Analog Converter
* Timer Module
* Indicator LEDs
* LCD
* Servo
* Stepper Motor Control
* DC Motor Control
* PWM Module
* Platform to Host Communication Module

Utilities
---------

* Bit operation macros
* delay

Protocol
--------

The Platform controller uses an ASCII protocol for communication with the host. Using this form of protocol allows better cross communication with varying host platforms.

The protocol consists of sending text packets in the form:

	<CMD ARG1 ARG2 ARG3 ... ARGx>

* Packet enclosed with '<' and '>'
* The instruction to the platform is issued with CMD (must be first)
* Any number of arguments delimited by a space character

For example the ping instruction looks like:

	<P>

* 'P' command
* No arguments

List of Valid Commands
----------------------

**Sync**

	<Z>

Before the platform enters its main command dispatch loop it must synchronize with the host. The platform will wait for this specific sync packet before continuing.

**Ping**

	<P>

Pinging the Platform Controller will cause it to respond with its own ping.

**Echo**

	<E %s>

Issuing an echo command will tell the platform to response with an identical packet.

	Host:
	<E hello>

	Platform Response:
	<E hello>

**Servo Angle**

	<S %d>

Set the servo's angle.

**Stepper Position**

	<ST %d>

Set the position of the stepper motor.

**Motor Speed**

	<MS %d>

Set the speed of the motor in cm/s

**Motor State**

	<MD %d %d>

Set the motors state of a specific motor.

Argument 1 - Specified motor. (Left Motor = 0, Right Motor = 1)

Argument 2 - Motor State.     (Off = 0, Forwards = 1, Backwards = 2)

Info
----

**Related blog posts**

[HCS12 Design Complete](https://nnarain.github.io/2015/02/28/HCS12-Board-Complete!.html)

[Board Assembly](https://nnarain.github.io/2015/03/18/Board-Assembly!!!.html)

[Board Bring Up](https://nnarain.github.io/2015/03/27/Board-Bring-Up.html)


