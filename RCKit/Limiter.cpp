// Limiter.cpp
//
// Setter class that limits its input to between specified min and max values
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: Limiter.cpp,v 1.1 2010/06/18 22:34:41 mikem Exp $

#include "Limiter.h"

/////////////////////////////////////////////////////////////////////
Limiter::Limiter(int min, int max) : Setter()
{
    _min = min;
    _max = max;
}


/////////////////////////////////////////////////////////////////////
void Limiter::input(int value)
{
    if (value < _min)
	value = _min;
    if (value > _max)
	value = _max;
    Setter::input(value);
}

