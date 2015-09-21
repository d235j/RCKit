// AnalogSetter.h
//
// Setter class that outputs its value to a analog output pin
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: AnalogSetter.h,v 1.2 2010/06/21 01:33:53 mikem Exp $

#ifndef AnalogSetter_h
#define AnalogSetter_h

#include "Setter.h"
#include <inttypes.h>

/////////////////////////////////////////////////////////////////////
/// \class AnalogSetter AnalogSetter.h <AnalogSetter.h>
/// \brief Setter class that sets its value to an analog output pin
///
class AnalogSetter : public Setter
{   
public:
    /// \param[in] pin The pin number of the analog output to set
    AnalogSetter(uint8_t pin);

    /// Set or change the output pin
    /// \param[in] pin The Arduino pin to use for output
    void setPin(uint8_t pin);

    /// Input the value to be used to set the analog output
    /// Analog outputs are within the range 0 to 255 for 0.0 to 5.0 V
    /// On Duemilanove, output is PWM at approx 1kHz
    /// \param[in] value The input value
    virtual void input(int value);

    /// Called when the source of input data is lost, and the Setter is required to fail in a safe way
    virtual void failsafe();

protected:

private:
    /// The analog output pin number
    uint8_t _pin;
};

#endif 
