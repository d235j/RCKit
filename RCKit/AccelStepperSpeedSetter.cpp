// AccelStepperSpeedSetter.cpp
//
// Setter to set the speed of an AccelStepper
/// \author  Mike McCauley (mikem@airspayce.com)
///
// Copyright (C) 2010 Mike McCauley
// $Id: AccelStepperSpeedSetter.cpp,v 1.2 2012/09/23 21:55:57 mikem Exp mikem $

#include "AccelStepperSpeedSetter.h"
#include <AccelStepper.h>

/////////////////////////////////////////////////////////////////////
AccelStepperSpeedSetter::AccelStepperSpeedSetter(AccelStepper* stepper) : Setter()
{
    _stepper = stepper;
}

/////////////////////////////////////////////////////////////////////
void AccelStepperSpeedSetter::input(int value)
{
    // Output the value to the servo
    if (_stepper)
	_stepper->setSpeed(value);
}

