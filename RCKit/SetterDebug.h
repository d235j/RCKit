// SetterDebug.h
//
// Class for testing and debugging Setter and subclasses
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: SetterDebug.h,v 1.3 2010/06/28 00:56:10 mikem Exp $

#ifndef SetterDebug_h
#define SetterDebug_h

#include "Setter.h"
#include <wiring.h>

/////////////////////////////////////////////////////////////////////
/// \class SetterDebug SetterDebug.h <SetterDebug.h>
/// \brief Class for testing Setters.
/// Used by the sample TestSuite sketch.
///
class SetterDebug : public Setter
{   
public:
    /// Input the value to be inverted
    /// \param[in] value The input value
    virtual void input(int value);

    /// Return the last value that 
    /// was set here
    int lastValue();

    /// Called when the source of input data is lost, 
    /// and the Setter is required to fail in a safe way
    virtual void failsafe();

    /// Returns whether there has been a 
    /// failsafe event
    boolean failed();

protected:

private:
    int     _lastValue;
    boolean _failed;
};

#endif 
