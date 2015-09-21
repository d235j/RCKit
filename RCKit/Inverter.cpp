// Inverter.cpp
//
// Template for a CPP file
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: Inverter.cpp,v 1.1 2010/06/18 22:34:41 mikem Exp $

#include "Inverter.h"

/////////////////////////////////////////////////////////////////////
void Inverter::input(int value)
{
    Setter::input(-value);
}

