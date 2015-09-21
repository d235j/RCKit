// TestSuite.pde
//
// Self test suite for RCKit classes
//
// Runs correctly on Duemilanova and Mega. 
// Subset tests all run OK on Diecimila, but all tests together uses too much RAM?
//
// Copyright (C) 2010 Mike McCauley
// $Id: $

#include <WiShield.h>
#include <Ethernet.h>
#include <SPI.h>
#include <Servo.h>
#include "Setter.h"
#include "Inverter.h"
#include "Limiter.h"
#include "Linear.h"
#include "ServoSetter.h"
#include "AnalogSetter.h"
#include "HBridgeSetter.h"
#include "DigitalSetter.h"
#include "AccelStepper.h"
#include "AccelStepperSpeedSetter.h"
#include "AccelStepperPositionSetter.h"
#include "DifferentialSetter.h"
#include "MotorControllerSetter.h"
#include "SetterDebug.h"

#define ANALOG_TEST_PINA 0
#define ANALOG_TEST_PINB 1
#define DIGITAL_TEST_PIN 2

SetterDebug d1, d2;
Setter s1(&d1); // Sets the target at construction time
Inverter i1;
Inverter i2;
Limiter l1(110, 120);
Linear lin1(0.5, 10);
Servo servo;
ServoSetter ss1(&servo);
AnalogSetter as1(ANALOG_TEST_PINA); 
AnalogSetter as2(ANALOG_TEST_PINB); 
HBridgeSetter hs1(&d1, &d2); 

DigitalSetter ds1(DIGITAL_TEST_PIN);
AccelStepper stepper;
AccelStepperSpeedSetter asss1(&stepper); 
AccelStepperPositionSetter asps1(&stepper); 
DifferentialSetter diff1(&d1, &d2);
DifferentialLRSetter di1(&diff1);

MotorControllerSetter mc1(&d1, &d2);

void setup()
{
  Serial.begin(9600);
  pinMode(DIGITAL_TEST_PIN, OUTPUT);
  stepper.setMaxSpeed(1000);
}

unsigned int errors = 0;

void error(const char *m)
{
  Serial.print("Error: ");
  Serial.println(m);
  errors++;
}

void check(boolean t, const char *m)
{
  if (!t)
    error(m);
}

void loop()
{
  // Check basic setting
  // d1 should already be the target for this setter
  // s1->d1
  d1.setFailsafeValue(123);
  s1.input(100);
  check(d1.lastValue() == 100, "basic 1");
  s1.input(200);
  check(d1.lastValue() == 200, "basic 2");
  check(!d1.failed(), "basic 3");
  s1.failsafe();
  check(d1.failed(), "basic 4");
  check(d1.lastValue() == 123, "basic 5");
    
  // Now test the Inverter class
  // i1->d1
  i1.setTarget(&d1);
  i1.input(300);
  check(d1.lastValue() == -300, "Inverter 1");
  i1.input(-400);
  check(d1.lastValue() == 400, "Inverter 2");
       
  // 2 Inverters in series
  // i2->i1->d1
  i2.setTarget(&i1);
  i2.input(600);
  check(d1.lastValue() == 600, "Inverter 3");
  i2.input(-700);
  check(d1.lastValue() == -700, "Inverter 4");
    
  // Now test the Limiter class
  // l1->d1
  l1.setTarget(&d1);
  l1.input(300);
  check(d1.lastValue() == 120, "Limiter 1");
  l1.input(120);
  check(d1.lastValue() == 120, "Limiter 2");
  l1.input(115);
  check(d1.lastValue() == 115, "Limiter 3");
  l1.input(100);
  check(d1.lastValue() == 110, "Limiter 4");
    
  // Test the Linear class
  lin1.setTarget(&d1);
  lin1.input(0);
  check(d1.lastValue() == 10, "Linear 1");
  lin1.input(10);
  check(d1.lastValue() == 15, "Linear 2");
  lin1.input(100);
  check(d1.lastValue() == 60, "Linear 3");
  lin1.input(-100);
  check(d1.lastValue() == -40, "Linear 4");
  
  // Test ServoSetter
  // ss1->servo
  servo.attach(2);
  ss1.input(0);
  check(servo.read() == 0, "ServoSetter 1");
  ss1.input(128);
  check(servo.read() == 90, "ServoSetter 2");
  ss1.input(255);
  check(servo.read() == 180, "ServoSetter 3");
    
  // Test AnalogSetter
  // Can't test necause can't read the resulting output
  // as1->analog pin 0
  as1.input(0);  
  as1.input(128);
  as1.input(255);
 
  // Test HBridgeSetter
  hs1.input(127);    
  check(d1.lastValue() == 0 && d2.lastValue() == 0, "HBridgeSetter 1");
  hs1.input(200);  
  check(d1.lastValue() == 146 && d2.lastValue() == 0, "HBridgeSetter 2");
  hs1.input(255);
  check(d1.lastValue() == 256 && d2.lastValue() == 0, "HBridgeSetter 3");
  hs1.input(100);  
  check(d1.lastValue() == 0 && d2.lastValue() == 54, "HBridgeSetter 4");
  hs1.input(0);
  check(d1.lastValue() == 0 && d2.lastValue() == 254, "HBridgeSetter 5");
 
  // Test DigitalSetter
  // Cant really read the resulting output
  // as1->analog pin 0
  ds1.input(0);
  check(digitalRead(DIGITAL_TEST_PIN) == LOW, "DigitalSetter 1");
  ds1.input(100);
  check(digitalRead(DIGITAL_TEST_PIN) == HIGH, "DigitalSetter 2");
 
  // Test AccelStepperSpeedSetter
  // asss1->stepper
  asss1.input(0);
  check(stepper.speed() == 0.0, "AccelStepperSpeedSetter 1");
  asss1.input(100);
  check(stepper.speed() == 100.0, "AccelStepperSpeedSetter 2");

  // Test AccelStepperPositionSetter
  // asps1->stepper 
  asps1.input(0);
  check(stepper.targetPosition() == 0, "AccelStepperPositionSetter 1");
  asps1.input(100);
  check(stepper.targetPosition() == 100, "AccelStepperPositionSetter 2");

  // test DifferentialSetter
  diff1.input(127);
  di1.input(127);
  check(d1.lastValue() == 127, "DifferentialSetter 1");
  check(d2.lastValue() == 127, "DifferentialSetter 2");
  di1.input(157);
  check(d1.lastValue() == 157, "DifferentialSetter 3");
  check(d2.lastValue() == 97, "DifferentialSetter 4");
  di1.input(107);
  check(d1.lastValue() == 107, "DifferentialSetter 5");
  check(d2.lastValue() == 147, "DifferentialSetter 6");
  diff1.input(255);
  di1.input(127);
  check(d1.lastValue() == 255, "DifferentialSetter 7");
  check(d2.lastValue() == 255, "DifferentialSetter 8");
  di1.input(147);
  check(d1.lastValue() == 255, "DifferentialSetter 9");
  check(d2.lastValue() == 215, "DifferentialSetter 10");
  di1.input(107);
  check(d1.lastValue() == 215, "DifferentialSetter 11");
  check(d2.lastValue() == 255, "DifferentialSetter 12");
  diff1.input(0);
  di1.input(127);
  check(d1.lastValue() == 0, "DifferentialSetter 13");
  check(d2.lastValue() == 0, "DifferentialSetter 14");
  di1.input(147);
  check(d1.lastValue() == 40, "DifferentialSetter 15");
  check(d2.lastValue() == 0, "DifferentialSetter 16");
  di1.input(107);
  check(d1.lastValue() == 0, "DifferentialSetter 17");
  check(d2.lastValue() == 40, "DifferentialSetter 18");
     
  // Long chain
  // i1->l1->i2->asps1->stepper
  i2.setTarget(&asps1);
  l1.setTarget(&i2);
  i1.setTarget(&l1);
  i1.input(300);
  check(stepper.targetPosition() == -110, "Chaining 1");
  i1.input(-400);
  check(stepper.targetPosition() == -120, "Chaining 2");
  
  // MotorController
  mc1.input(0);
  check(d1.lastValue() == 0, "MotorControllerSetter 1");
  check(d2.lastValue() == 254, "MotorControllerSetter 2");
  mc1.input(100);
  check(d1.lastValue() == 0, "MotorControllerSetter 1");
  check(d2.lastValue() == 54, "MotorControllerSetter 2");
  mc1.input(127);
  check(d1.lastValue() == 255, "MotorControllerSetter 3");
  check(d2.lastValue() == 0, "MotorControllerSetter 4");
  mc1.input(128);
  check(d1.lastValue() == 255, "MotorControllerSetter 3");
  check(d2.lastValue() == 2, "MotorControllerSetter 4");
  mc1.input(200);
  check(d1.lastValue() == 255, "MotorControllerSetter 5");
  check(d2.lastValue() == 146, "MotorControllerSetter 6");
  mc1.input(255);
  check(d1.lastValue() == 255, "MotorControllerSetter 5");
  check(d2.lastValue() == 256, "MotorControllerSetter 6");
  
  // All done
  Serial.print("Done. Errors: ");
  Serial.println(errors, DEC);
  
  pinMode(13, OUTPUT);
  if (errors)
  {
    // Errors: Blink twice
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
  }
  else
  {
    // OK, Blink once
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
  }
  while (1)
    ;
}
