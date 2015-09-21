// Linear.cpp
//
// Setter class that limits its input to between specified min and max values
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: Linear.cpp,v 1.1 2012/08/25 06:18:13 mikem Exp mikem $

#include "Linear.h"

/////////////////////////////////////////////////////////////////////
Linear::Linear(float gain, int offset) : Setter()
{
    _gain = gain;
    _offset = offset;
}


/////////////////////////////////////////////////////////////////////
void Linear::input(int value)
{
    Setter::input((int)((_gain * value) + _offset));
}

