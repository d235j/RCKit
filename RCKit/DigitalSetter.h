// DigitalSetter.h
//
// Setter class that outputs its value to a analog output pin
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: DigitalSetter.h,v 1.2 2010/06/28 00:56:10 mikem Exp $

#ifndef DigitalSetter_h
#define DigitalSetter_h

#include "Setter.h"
#include <inttypes.h>

/////////////////////////////////////////////////////////////////////
/// \class DigitalSetter DigitalSetter.h <DigitalSetter.h>
/// \brief Setter class that sets its value to an analog output pin
///
class DigitalSetter : public Setter
{   
public:
    /// \param[in] pin The pin number of the digital output to set
    /// Caller is expected to have set it as an output already
    DigitalSetter(uint8_t pin);

    /// Set or change the output pin
    /// \param[in] pin The Arduino pin to use for output
    void setPin(uint8_t pin);

    /// Input the value to be used to set the analog output
    /// Digital outputs are 0 or 1
    /// Inout 0 produces digital output of 0. All other values produce output of 1
    /// \param[in] value The input 0 for off, all other values for on
    virtual void input(int value);

    /// Called when the source of input data is lost, and the Setter is required to fail in a safe way
    virtual void failsafe();
protected:

private:
    /// The analog output pin number
    uint8_t _pin;
};

#endif 
