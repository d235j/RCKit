// RCRx
//
// Sample RCRx RCOIP receiver
// Receives RCOIP commmands on a WiShield and uses them to set servo
// and digital outputs.
// This compiles to about 15000 bytes on Duemilanove, and will not fit in Diecimila.
//
// This simple example handles 4 RCOIP receiver channels. Its configured like this:
// 2 Servos (receiver channels 0, 1) (left joystick on RCTx)
// 1 HBridge (receiver channel 3) driving 2 analog outputs (right joystick on RCTx)
// 1 Digital output (horn) (receiver channel 4)
//
// This can be used off the shelf with the RCTx transmitter app for iPhone
// Copyright (C) 2010 Mike McCauley


#include <SPI.h>
#include <WiShield.h>
#include <Ethernet.h>
#include <WiShieldTransceiver.h>
#include <RCRx.h>
#include <Servo.h>
#include <ServoSetter.h>
#include <AnalogSetter.h>
#include <HBridgeSetter.h>
#include <DigitalSetter.h>
#include <AccelStepper.h>


// We handle 5 channels:
// 2 Servos (receiver channels 0, 1) driving pins 3 and 4
// Receiver channel 2 is unused
// 1 HBridge (receiver channel 3) driving analog outputs on pins 5 and 6
// 1 Digital output (horn) (receiver channel 4) driving pin 8

// Declare the receiver object
RCRx rcrx;

// Declare the transceiver object, in this case a WiShield WiFi shield for
// Arduino, or Yellowjacket board (an Arduino with WiShield built in)
// If you want to change the default IP address, SSID etc, edit
// WiShieldTtransceiver.cpp
// Note: other type of transceiver are supported by RCRx
WiShieldTransceiver transceiver;

#define HORN_PIN 8
#define NUM_OUTPUTS 5
#define SERVO_0_PIN 3
#define SERVO_1_PIN 4
#define MOTOR_FWD 5
#define MOTOR_REV 6

// These are the low level Servo drivers
#define NUM_SERVOS 2
Servo servos[NUM_SERVOS];

// These Setters set the output value onto a Servo
ServoSetter servoSetter0(&servos[0]);
ServoSetter servoSetter1(&servos[1]);

// HBridge motor outputs
AnalogSetter analogSetter0(MOTOR_FWD);
AnalogSetter analogSetter1(MOTOR_REV);
HBridgeSetter hbridgeSetter0(&analogSetter1, &analogSetter0);

// This setter sets a digital output
DigitalSetter horn(HORN_PIN);

// This array of all the outputs is in channel-number-order so RCRx knows which
// Setter to call for each channel received. We define an array of 5 Setters for receiver channels 0 through 4
Setter*  outputs[NUM_OUTPUTS] = {&servoSetter0, &servoSetter1, 0, &hbridgeSetter0, &horn};

void setup()
{
  Serial.begin(9600);
  
  // Ensure we can output on the horn digital pin
  pinMode(HORN_PIN, OUTPUT);
  
  // Attach the Servo drivers to the servo output pins
  servos[0].attach(SERVO_0_PIN); 
  servos[1].attach(SERVO_1_PIN); 
  
  // Tell the receiver where to send the 5 channels
  rcrx.setOutputs((Setter**)&outputs, NUM_OUTPUTS);
  
  // Join the transceiver and the RCRx receiver object together
  rcrx.setTransceiver(&transceiver);
  
  // Initialise the receiver
  rcrx.init();

}

void loop()
{
  // And do it
  rcrx.run();
}


