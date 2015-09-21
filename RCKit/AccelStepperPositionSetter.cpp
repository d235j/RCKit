// AccelStepperPositionSetter.cpp
//
// Setter to set the speed of an AccelStepperPosition
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: AccelStepperPositionSetter.cpp,v 1.1 2010/06/18 22:34:41 mikem Exp $

#include "AccelStepperPositionSetter.h"
#include <AccelStepper.h>

/////////////////////////////////////////////////////////////////////
AccelStepperPositionSetter::AccelStepperPositionSetter(AccelStepper* stepper) : Setter()
{
    _stepper = stepper;
}

/////////////////////////////////////////////////////////////////////
void AccelStepperPositionSetter::input(int value)
{
    // Output the value to the servo
    if (_stepper)
	_stepper->moveTo(value);
}

