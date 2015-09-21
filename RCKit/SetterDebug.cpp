// SetterDebug.cpp
//
// Class for testing and debugging Setter and subclasses
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: SetterDebug.cpp,v 1.3 2010/06/28 00:56:10 mikem Exp $

#include "HardwareSerial.h"
#include "SetterDebug.h"

/////////////////////////////////////////////////////////////////////
void SetterDebug::input(int value)
{
    _lastValue = value;
    _failed = false;
//    Serial.print("Set value to ");
//    Serial.println(value, DEC);
}

/////////////////////////////////////////////////////////////////////
int SetterDebug::lastValue()
{
    return _lastValue;
}

/////////////////////////////////////////////////////////////////////
boolean SetterDebug::failed()
{
    return _failed;
}

/////////////////////////////////////////////////////////////////////
void SetterDebug::failsafe()
{
    input(failsafeValue());
    _failed = true;
}

