// AccelStepperSpeedSetter.cpp
//
// Setter to set the speed of an AccelStepper
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: AccelStepperSpeedSetter.cpp,v 1.1 2010/06/18 22:34:41 mikem Exp $

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

