// RCRx
//
// Sample RCRx RCOIP receiver
// Receives RCOIP commmands on a WiShield and uses them to set analog
// and digital outputs.
// This compiles to about 15000 bytes on Duemilanove, and will not fit in Diecimila.
//
// This simple example handles 3 RCOIP receiver channels. Its configured like this:
// This is the program used for the car shown in http://www.open.com.au/mikem/arduino/RCKit/car1.mp4
//
// This can be used off the shelf with the RCTx transmitter app for iPhone
// Copyright (C) 2010 Mike McCauley


#include <WiShield.h>
#include <Ethernet.h>
#include <SPI.h>
#include <WiShieldTransceiver.h>
#include <RCRx.h>
#include <Servo.h>
#include <ServoSetter.h>
#include <AnalogSetter.h>
#include <HBridgeSetter.h>
#include <DigitalSetter.h>
#include <AccelStepper.h>


// We handle 3 channels:
// 1 HBridge (receiver channel 0) driving analog outputs 3, 5 (left joystick left/right on RCTx) LEFT/RIGHT
// 1 HBridge (receiver channel 1) driving analog outputs 6, 9 (left joystick up/down RCTx) FWD/REV
// 1 Digital output (horn) (receiver channel 4)
// It can therefore be used to control a conventional cheap model car with 2 hbridges, 
// one for fwd/rev motor control and one for left/right motor control.
// Receiver channels 0, 1 unused
//
// Note Smaller arduinos like the duemilanove can only handle analog outputs on pins 3, 5, 6, 9, 10 and 11.
// 10 and 11 are used by the WiShield, and 9 is normally the WiShield 'ready' LED. We need 4 analog outs to drive the 
// 2 motors in forward and reverse, so we coopt pin 9 as the 4th analog output.
// That means we have to quickly turn it off after the radio is set up.

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

#define MOTOR1_FWD 3
#define MOTOR1_REV 5
#define MOTOR2_FWD 6
#define MOTOR2_REV 9

// HBridge motor outputs
AnalogSetter analogSetter0(MOTOR1_FWD);
AnalogSetter analogSetter1(MOTOR1_REV);
HBridgeSetter hbridgeSetter0(&analogSetter1, &analogSetter0);
AnalogSetter analogSetter2(MOTOR2_FWD);
AnalogSetter analogSetter3(MOTOR2_REV);
HBridgeSetter hbridgeSetter1(&analogSetter2, &analogSetter3);

// This setter sets a digital output
DigitalSetter horn(HORN_PIN);

// This array of all the outputs is in channel-number-order so RCRx knows which
// Setter to call for each channel received. We define an array of 5 Setters for receiver channels 0 through 4
Setter*  outputs[NUM_OUTPUTS] = {0, 0, &hbridgeSetter0, &hbridgeSetter1, &horn};

void setup()
{
  Serial.begin(9600);
  
  // Ensure we can output on the horn digital pin
  pinMode(HORN_PIN, OUTPUT);

  // Tell the receiver where to send the 5 channels
  rcrx.setOutputs((Setter**)&outputs, NUM_OUTPUTS);
  
  // Join the transceiver and the RCRx receiver object together
  rcrx.setTransceiver(&transceiver);
  
  // Initialise the receiver
  rcrx.init();
  
  // Turn off the LED pin becuase we have it connected to a motor :-(
  analogWrite(MOTOR2_REV, 0);
}

void loop()
{
  // And do it
  rcrx.run();
}


