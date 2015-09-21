// HBridgeSetter.h
//
// Setter class that outputs its value to a HBridge configured on 2 analog output pins
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: HBridgeSetter.h,v 1.3 2010/06/28 00:56:10 mikem Exp $

#ifndef HBridgeSetter_h
#define HBridgeSetter_h

#include "Setter.h"
#include <inttypes.h>

/////////////////////////////////////////////////////////////////////
/// \class HBridgeSetter HBridgeSetter.h <HBridgeSetter.h>
/// \brief Setter class that outputs its value to a HBridge configured on 2 output Setter
///
/// A HBridge is used to drive a motor in forward and reverse directions. It requires 2 Setters as output:
/// one to drive the motor forwards and one to drive it in reverse. When driving forward the reverse 
/// output is 0 and vice versa.
///
/// Typically the outputs would be AnalogSetters to control a motor through a pair of analog outputs,
/// but could be ServoSetter, AccelStepperSpeedSetter 
/// or AccelStepperPositionSetter or any other combination.
///
class HBridgeSetter : public Setter
{   
public:
    /// \param[in] targetA The Setter to use for output A.
    /// \param[in] targetB The Setter to use for output B.
    HBridgeSetter(Setter* targetA, Setter* targetB);

    /// Set or change the output pin
    /// \param[in] targetA The Setter to use for output A.
    /// \param[in] targetB The Setter to use for output B.
    void setTargets(Setter* targetA, Setter* targetB);

    /// Input the value to be used to set the 2 output Setters.
    /// Input of 127 produces 0 on both outputs (stopped)
    /// Input of 128 to 255 translates to output Setter A from 0 to 256
    /// and output Setter B at 0 (forward).
    /// Input of 127 to 0 translates to output Setter B from 0 to 254
    /// and output Setter A at 0 (reverse).
    /// \param[in] value The input value to set.
    virtual void input(int value);

    /// Called when the source of input data is lost, and the Setter is required to fail in a safe way.
    /// Calls the failsafes of targetA and targetB
    virtual void failsafe();

protected:

private:
    /// The B output Setter. targetA is the setter that is included in the Setter class
    Setter* _targetB;
};

#endif g
