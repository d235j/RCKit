// DifferentialSetter.h
//
// Setter class cluster that controls 2 analog outputs based on 2 analog inputs so that a joystic
// can be used to control 2 motors like on a tank or bulldozer
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: DifferentialSetter.h,v 1.2 2010/06/30 02:48:59 mikem Exp mikem $

#ifndef DifferentialSetter_h
#define DifferentialSetter_h

#include "Setter.h"
#include <inttypes.h>

/////////////////////////////////////////////////////////////////////
/// \class DifferentialSetter DifferentialSetter.h <DifferentialSetter.h>
/// \brief Setter class cluster that controls 2 analog outputs based on 2 analog inputs so that a joystic
/// can be used to control 2 motors like on a tank or bulldozer or concentric rotor helicopter.
/// inputA controls forwars/reverse and inputB controls left/right.
///
/// A Differential is used to drive 2 motors in forward and reverse directions 
/// in response to the inputs from 2 joysticks.
///
/// It requires 2 HBridges as output:
/// one to drive the left motor forward/reverse and one to drive the right motor forward/reverse. 
///
/// It also requires 2 inputs, 
/// one for the fore-aft and one for the left-right. The 2 outputs drive 2 reversible motors 
/// that act like the motors on a tank
/// or bulldozer, allowing forward, reverse and turning under the control of an x-Y joystick.
///
/// In general, the fore/aft input (inputA) is replicated on the 2 outputs, but if inputB varies
/// either side of 127, outputA is increased/decreased and outputB in decreased/increased. 
/// The outputs are never permitted outside the range 0 - 255.
///
/// The standard input (inputA) to this Setter controls the forward/reverse. The left/right controls come
/// through an instance of the DifferentialLRSetter class.
///
/// Typically the outputs would be two HBridgeSetter instances to control a pair of motors 
/// but could be ServoSetter, AccelStepperSpeedSetter 
/// or AccelStepperPositionSetter or any other combination.
///
class DifferentialSetter : public Setter
{   
public:
    /// \param[in] targetA The Setter to use for output A.
    /// \param[in] targetB The Setter to use for output B.
    DifferentialSetter(Setter* targetA, Setter* targetB);

    /// Set or change the output pin
    /// \param[in] targetA The Setter to use for output A.
    /// \param[in] targetB The Setter to use for output B.
    void setTargets(Setter* targetA, Setter* targetB);

    /// Input the value to be used to set the 2 output Setters.
    /// \param[in] value The fore/aft value.
    virtual void input(int value);

    /// This is the B input, controlling left-right differential. It has to come from
    /// an instance of DifferentialLRSetter.
    /// \param[in] value The input value to set.
    virtual void inputB(int value);

    /// Called when the source of input data is lost, and the Setter is required to fail in a safe way.
    /// Calls the failsafes of targetA and targetB
    virtual void failsafe();

protected:
    /// Internal function that computes the two output vlaues based on themost recent input values
    void doOutput();

private:
    /// The B output Setter. targetA is the setter that is included in the Setter class
    Setter* _targetB;
    int _lastInputA;
    int _lastInputB;
};

/////////////////////////////////////////////////////////////////////
/// \class DifferentialLRSetter DifferentialSetter.h <DifferentialSetter.h>
/// \brief Setter class cluster that provides the left-right input to a DifferentialSetter
///
/// Looks like a conventional; setter, but sets the B input of a DifferentialSetter
/// This is for setting the left-right inputs into a DifferentialSetter
class DifferentialLRSetter : public Setter
{
public:
    /// \param target The DifferentialSetter whose inputB is to be set by this Setter
    DifferentialLRSetter(DifferentialSetter* target);

    /// \param value The left/right value (inputB) to set in the target DifferentialSetter
    virtual void input(int value);
};


#endif 
