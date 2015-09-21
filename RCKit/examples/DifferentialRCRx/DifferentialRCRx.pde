// RCRx
//
// Sample RCRx RCOIP receiver
// Receives RCOIP commmands on a WiShield and uses them to set analog
// and digital outputs.
// This compiles to about 15000 bytes on Duemilanove, and will not fit in Diecimila.
//
// This simple example handles 3 RCOIP receiver channels. Its configured like this:
// 1 Differential motor driver (receiver channels 0 and 1) driving 4 analog outputs configured as 2 HBridges
// 1 Digital output (horn) (receiver channel 4)
// This is the program used for the tank shown in http://www.open.com.au/mikem/arduino/RCKit/tank.mp4
//
// This can be used off the shelf with the RCTx transmitter app for iPhone
// Copyright (C) 2010 Mike McCauley

#include <WiShield.h>
#include <RCRx.h>
#include <Servo.h>
#include "AnalogSetter.h"
#include "HBridgeSetter.h"
#include "DifferentialSetter.h"
#include "DigitalSetter.h"
#include <AccelStepper.h>

// We handle 3 channels:
// Receiver channel 2 is unused
// 1 Differential motor drive (receiver channels 0 and 1) driving analog outputs on pins 3, 5, 6 and 9
// 1 Digital output (horn) (receiver channel 4) driving pin 8
// receiver channels 2 and 3 (the right joystick on RCTx)
//
// Note Smaller arduinos like the duemilanove can only handle analog outputs on pins 3, 5, 6, 9, 10 and 11.
// 10 and 11 are used by the WiShield, and 9 is normally the WiShield 'ready' LED. We need 4 analog outs to drive the 
// 2 motors in forward and reverse, so we coopt pin 9 as the 4th analog output.
// That means we have to quickly turn it off after the radio is set up.

// Declare the receiver object
RCRx rcrx;

#define HORN_PIN 8
#define NUM_OUTPUTS 5
#define MOTOR_L_FWD 3
#define MOTOR_L_REV 5
#define MOTOR_R_FWD 6
#define MOTOR_R_REV 9

// HBridge motor outputs
AnalogSetter analogSetter0(MOTOR_L_FWD);
AnalogSetter analogSetter1(MOTOR_L_REV);
HBridgeSetter hbridgeSetter0(&analogSetter1, &analogSetter0);
AnalogSetter analogSetter2(MOTOR_R_FWD);
AnalogSetter analogSetter3(MOTOR_R_REV);
HBridgeSetter hbridgeSetter1(&analogSetter2, &analogSetter3);
DifferentialSetter ds1(&hbridgeSetter1, &hbridgeSetter0);
DifferentialLRSetter di1(&ds1);

// This setter sets a digital output
DigitalSetter horn(HORN_PIN);

// This array of all the outputs is in channel-number-order so RCRx knows which
// Setter to call for each channel received. We define an array of 5 Setters for receiver channels 0 through 4
Setter*  outputs[NUM_OUTPUTS] = {&di1, &ds1, 0, 0, &horn};

void setup()
{
  Serial.begin(9600);
  
  // Ensure we can output on the horn digital pin
  pinMode(HORN_PIN, OUTPUT);
    
  // Tell the receiver where to send the 5 channels
  rcrx.setOutputs((Setter**)&outputs, NUM_OUTPUTS);
  
  // Initialise the receiver
  rcrx.init();
  
  // Turn off the LED pin becuase we have it connected to a motor :-(
  analogWrite(MOTOR_R_REV, 0);
}

void loop()
{
  // Do WiFi processing
  rcrx.run();
}


