// DigitalSetter.cpp
//
// Template for a CPP file
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: DigitalSetter.cpp,v 1.3 2012/08/25 06:18:13 mikem Exp mikem $

#include "DigitalSetter.h"
#if (ARDUINO < 100)
#include "WProgram.h"
#else
#include "Arduino.h"
#endif

/////////////////////////////////////////////////////////////////////
DigitalSetter::DigitalSetter(uint8_t pin) : Setter()
{
    setPin(pin);
}

/////////////////////////////////////////////////////////////////////
void DigitalSetter::setPin(uint8_t pin)
{
    _pin = pin;
}

/////////////////////////////////////////////////////////////////////
void DigitalSetter::input(int value)
{
    // Output the value
    digitalWrite(_pin, value ? HIGH : LOW);
}

/////////////////////////////////////////////////////////////////////
// Output the failsafe value
void DigitalSetter::failsafe()
{
    input(_failsafeValue);
}

