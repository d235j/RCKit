// DigitalSetter.cpp
//
// Template for a CPP file
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: DigitalSetter.cpp,v 1.2 2010/06/28 00:56:10 mikem Exp $

#include "DigitalSetter.h"
#include "WProgram.h"

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

