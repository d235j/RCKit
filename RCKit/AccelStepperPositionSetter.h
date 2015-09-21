// AccelStepperPositionSetter.h
//
// Setter class that outputs its value to set the position of an AccelStepper
/// \author  Mike McCauley (mikem@airspayce.com)
///
// Copyright (C) 2010 Mike McCauley
// $Id: AccelStepperPositionSetter.h,v 1.2 2010/06/21 01:33:53 mikem Exp $

#ifndef AccelStepperPositionSetter_h
#define AccelStepperPositionSetter_h

#include "Setter.h"

class AccelStepper;

/////////////////////////////////////////////////////////////////////
/// \class AccelStepperPositionSetter AccelStepperPositionSetter.h <AccelStepperPositionSetter.h>
/// \brief Setter class that outputs its value to set the position of an AccelStepper
///
/// Requires the AccelStepper library seehttp://www.airspayce.com/mikem/arduino/AccelStepper/
///
class AccelStepperPositionSetter : public Setter
{   
public:
    /// \param[in] stepper The target AccelStepper instance. It is the callers job to configure
    /// the AccelStepper
    AccelStepperPositionSetter(AccelStepper* stepper);

    /// Input the value to be used to set the stepper position.
    /// \param[in] value The input value to be used to set the position of the stepper.
    // Positive is clockwise. 
    virtual void input(int value);

protected:

private:
    /// The AccelStepper to be set by this Setter
    AccelStepper* _stepper;
};

#endif 
