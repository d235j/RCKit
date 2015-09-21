// DifferentialSetter.cpp
//
// Template for a CPP file
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: DifferentialSetter.cpp,v 1.1 2010/06/28 00:56:10 mikem Exp $

#include "DifferentialSetter.h"
#if (ARDUINO < 100)
#include "WProgram.h"
#endif

/////////////////////////////////////////////////////////////////////
DifferentialLRSetter::DifferentialLRSetter(DifferentialSetter* target) : Setter(target)
{
}

/////////////////////////////////////////////////////////////////////
void DifferentialLRSetter::input(int value)
{
    // The raget is expcetd to be a DifferentialSetter, whose 
    // inputB value we set
    if (_target)
	((DifferentialSetter*)_target)->inputB(value);
}

/////////////////////////////////////////////////////////////////////
DifferentialSetter::DifferentialSetter(Setter* targetA, Setter* targetB) : Setter(targetA)
{
    _targetB = targetB;
}

/////////////////////////////////////////////////////////////////////
void DifferentialSetter::setTargets(Setter* targetA, Setter* targetB)
{
    Setter::setTarget(targetA);
    _targetB = targetB;
}

/////////////////////////////////////////////////////////////////////
void DifferentialSetter::input(int value)
{
    _lastInputA = value;
    doOutput();
}

/////////////////////////////////////////////////////////////////////
void DifferentialSetter::inputB(int value)
{
    _lastInputB = value;
    doOutput();
}

/////////////////////////////////////////////////////////////////////
void DifferentialSetter::doOutput()
{
    // First compute the fore-aft
    int outA, outB;
    outA = outB = _lastInputA;

    // Then adjust it for left/right
    outA += (_lastInputB - 127);
    outB -= (_lastInputB - 127);
    if (outA > 255)
    {
	outB -= outA - 255;
	outA = 255;
    }
    else if (outB > 255)
    {
	outA -= outB - 255;
	outB = 255;
    }
    if (outA < 0)
    {
	outB -= outA;
	outA = 0;
    }
    else if (outB < 0)
    {
	outA -= outB;
	outB = 0;
    }

    Setter::input(outA);
    if (_targetB)
	_targetB->input(outB);
}

/////////////////////////////////////////////////////////////////////
void DifferentialSetter::failsafe()
{
    Setter::failsafe();
    if (_targetB)
	_targetB->failsafe();
}

