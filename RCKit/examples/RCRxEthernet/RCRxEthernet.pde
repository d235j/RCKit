// RCRxEthernet
//
// Sample RCRx RCOIP receiver
// Receives RCOIP commmands from Ethernet and uses them to set servo
// and digital outputs.
//
// This compiles to about 12000 bytes on Duemilanove.
//
// This simple example handles 5 RCOIP receiver channels. Its configured like this:
// 4 Servos (receiver channels 0, 1, 2, 3)
// 1 Digital output (horn) (receiver channel 4)
// which is consistent with the default setup of the RCTx iPhone app.
//
// However, almost any combination of up to a large number of channels can be used as you see fit.
// Output devices supported are:
// analog output pins
// digital output pins
// Servo
// AccelStepper speed
// AccelStepper position
// HBridge to drive 2 other outputs
//
// Also you can string varies objects together top modify channel values as
// they make their way from the receiver to an output:
// Limiter
// Inverter
// This can be used off the shelf with the RCTx transmitter app for iPhone
// Copyright (C) 2010 Mike McCauley

#include <SPI.h>
#include <WiShield.h>
#include <Ethernet.h>
#include <EthernetTransceiver.h>
#include <RCRx.h>
#include <Servo.h>
#include <ServoSetter.h>
#include <AnalogSetter.h>
#include <DigitalSetter.h>
#include <AccelStepper.h>

// Declare the receiver object. It will handle messages received from the
// transceiver and turn them into channel outputs.
// The receiver and transceiver obects are connected together during setup()
RCRx rcrx;

// Declare the transceiver object, in this case an Ethernet shield for
// Arduino, with the defined MAC and IP address
// Note: other types of transceiver are supported by RCRx, including:
// WiShieldTransceiver for WiShield and Yellowjacket arduinos
// Note: other type of transceiver are supported by RCRx
IPAddress thisIPAddress(203, 63, 154, 100);
byte thisMACaddress[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
EthernetTransceiver transceiver(thisMACaddress, &thisIPAddress);

#define HORN_PIN 8
#define NUM_OUTPUTS 5
#define SERVO_0_PIN 3
#define SERVO_1_PIN 4
#define SERVO_2_PIN 5
#define SERVO_3_PIN 6

// There are 5 outputs for 5 channels:
// 4 Servos (receiver channels 0, 1, 2, 3)
// 1 Digital output (horn) (receiver channel 4)

// These are the low level Servo drivers
#define NUM_SERVOS 4
Servo servos[NUM_SERVOS];

// These Setter set the output value onto a Servo
ServoSetter servoSetter0(&servos[0]);
ServoSetter servoSetter1(&servos[1]);
ServoSetter servoSetter2(&servos[2]);
ServoSetter servoSetter3(&servos[3]);

// This setter sets a digital output
DigitalSetter horn(HORN_PIN);

// This array of all the outputs is in channel-number-order so RCRx knows which
// Setter to call for each channel received. We define an array of 5 Setters for receiver channels 0 through 4
Setter*  outputs[NUM_OUTPUTS] = {&servoSetter0, &servoSetter1, &servoSetter2, &servoSetter3, &horn};

void setup()
{
  Serial.begin(9600);
  
  // Ensure we can output on the horn digital pin
  pinMode(HORN_PIN, OUTPUT);
  
  // Attach the Servo drivers to the servo output pins
  servos[0].attach(SERVO_0_PIN); 
  servos[1].attach(SERVO_1_PIN); 
  servos[2].attach(SERVO_2_PIN); 
  servos[3].attach(SERVO_3_PIN); 
  
  // Tell the receiver where to send the 5 channels
  rcrx.setOutputs((Setter**)&outputs, NUM_OUTPUTS);

  // Join the transceiver and the RCRx receiver object together
  rcrx.setTransceiver(&transceiver);
  
  // Initialise the receiver and transceiver
  rcrx.init();
}

void loop()
{
  // And do it
  rcrx.run();
}


