// MotorControllerSetter.cpp
//
// Template for a CPP file
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: MotorControllerSetter.cpp,v 1.1 2012/08/25 06:18:13 mikem Exp $

#include "MotorControllerSetter.h"
#if (ARDUINO < 100)
#include "WProgram.h"
#else
#include "Arduino.h"
#endif

/////////////////////////////////////////////////////////////////////
MotorControllerSetter::MotorControllerSetter(Setter* targetA, Setter* targetB) : Setter(targetA)
{
    _targetB = targetB;
}

/////////////////////////////////////////////////////////////////////
void MotorControllerSetter::setTargets(Setter* targetA, Setter* targetB)
{
    Setter::setTarget(targetA);
    _targetB = targetB;
}

/////////////////////////////////////////////////////////////////////
void MotorControllerSetter::input(int value)
{
    // Output the value
    int outA, outB;
    if (value >= 127)
    {
	// Forward
	outA = 255;
	outB = (value - 127) << 1;
    }
    else // value < 127
    {
	// Reverse
	outA = 0;
	outB = (127 - value) << 1;
    }
//    Serial.println("motorcontroller");
//    Serial.println(outA, DEC);
//    Serial.println(outB, DEC);
    Setter::input(outA);
    if (_targetB)
	_targetB->input(outB);
}

/////////////////////////////////////////////////////////////////////
void MotorControllerSetter::failsafe()
{
    Setter::failsafe();
    if (_targetB)
	_targetB->failsafe();
}

