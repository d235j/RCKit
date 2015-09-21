// MotorControllerSetter.h
//
// Setter class that outputs its value to a MotorController configured on 1 digital and one analog output pins
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: MotorControllerSetter.h,v 1.3 2010/06/28 00:56:10 mikem Exp $

#ifndef MotorControllerSetter_h
#define MotorControllerSetter_h

#include "Setter.h"
#include <inttypes.h>

/////////////////////////////////////////////////////////////////////
/// \class MotorControllerSetter MotorControllerSetter.h <MotorControllerSetter.h>
/// \brief Setter class that outputs its value to a MotorController configured on 1 digital and one analog output pins
///
/// A MotorController is used to drive a motor in forward and reverse directions. It requires 2 Setters as output:
/// one to specify the direction, and one to specify the speed. 
///
/// Inputs 0 to 127 set direction to 0 (reverse) and speed to 254 to 0 respectively
/// Inputs 128 to 255 set direction to 1 (forward) and speed to 0 to 256 respectively
/// This means than an input of 0 will produce full speed reverse, and input of 127 will produce stop and 
/// 255 will produce full speed forward. Truth table:
/// input   A    B
/// 0       0    254
/// 100     0    54
/// 127     255  0
/// 128     255  2
/// 203     255  146
/// 255     255  256
///
/// This is compatible with many motor controllers, such as the Arduino Motor Shield (L298N) (SKU:DRI0009) and many others
///
/// Typically the outputs would be a DigitalSetter and an AnalogSetter to control a motor through a digital (direction) 
/// and an analog (PWM speed) outputs
///
class MotorControllerSetter : public Setter
{   
public:
    /// \param[in] targetA The Setter to use for direction, typically a DigitalSetter.
    /// \param[in] targetB The Setter to use for speed, typically an AnalogSetter.
    MotorControllerSetter(Setter* targetA, Setter* targetB);

    /// Set or change the output pin
    /// \param[in] targetA The Setter to use for output A.
    /// \param[in] targetB The Setter to use for output B.
    void setTargets(Setter* targetA, Setter* targetB);

    /// Input the value to be used to set the 2 output Setters.
    /// Input of 127 produces 255 on A and 0 on B (forward but stopped)
    /// Input of 128 to 255 translates to output Setter A to 256 (forward)
    /// and output Setter B at 0 to 254 (full speed).
    /// Input of 127 to 0 translates to output Setter A to 0 (reverse)
    /// and output Setter B at 0 to 254 (full speed).
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

#endif 
