// AccelStepperSpeedSetter.h
//
// Setter class that outputs its value to set the speed of an AccelStepper
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: AccelStepperSpeedSetter.h,v 1.2 2010/06/21 01:33:53 mikem Exp $

#ifndef AccelStepperSpeedSetter_h
#define AccelStepperSpeedSetter_h

#include "Setter.h"

class AccelStepper;

/////////////////////////////////////////////////////////////////////
/// \class AccelStepperSpeedSetter AccelStepperSpeedSetter.h <AccelStepperSpeedSetter.h>
/// \brief Setter class that outputs its value to set the speed of an AccelStepper
///
/// Requires the AccelStepper library seehttp://www.open.com.au/mikem/arduino/AccelStepper/
///
class AccelStepperSpeedSetter : public Setter
{   
public:
    /// \param[in] stepper The target AccelStepper instance. It is the callers job to configure
    /// the AccelStepper
    AccelStepperSpeedSetter(AccelStepper* stepper);

    /// Input the value to be used to set the stepper speed.
    /// \param[in] value The inpout value to be used to set the speed of the stepper in steps per second. 
    // Positive is clockwise. 
    virtual void input(int value);

protected:

private:
    /// The AccelStepper to be set by this Setter
    AccelStepper* _stepper;
};

#endif 
