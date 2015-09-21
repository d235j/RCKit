// AnalogSetter.cpp
//
// Template for a CPP file
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: AnalogSetter.cpp,v 1.3 2010/06/28 00:56:10 mikem Exp $

#include "AnalogSetter.h"
#include <wiring.h>
#include <HardwareSerial.h>

/////////////////////////////////////////////////////////////////////
AnalogSetter::AnalogSetter(uint8_t pin) : Setter()
{
    _pin = pin;
}

/////////////////////////////////////////////////////////////////////
void AnalogSetter::setPin(uint8_t pin)
{
    _pin = pin;
}

/////////////////////////////////////////////////////////////////////
void AnalogSetter::input(int value)
{
    // Clamp the value to the limits of analog output
    if (value < 0)
	value = 0;
    if (value > 255)
	value = 255;
    // Output the value
//    Serial.println("analog");
//    Serial.println(value, DEC);
    analogWrite(_pin, value);
}

/////////////////////////////////////////////////////////////////////
// Output the failsafe value
void AnalogSetter::failsafe()
{
    input(_failsafeValue);
}

