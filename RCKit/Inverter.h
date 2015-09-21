// Inverter.h
//
// Setter Class that inverts its input value and sends it to the output
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: Inverter.h,v 1.2 2010/06/28 00:56:10 mikem Exp $

#ifndef Inverter_h
#define Inverter_h

#include "Setter.h"

/////////////////////////////////////////////////////////////////////
/// \class Inverter Inverter.h <Inverter.h>
/// \brief Setter object that inverts its value.
/// 
/// Inverter inverts its input value and passes it the resulting value to the 
/// next Setter (the target) in the chain.
class Inverter : public Setter
{   
public:
    /// Input the value to be inverted
    /// \param[in] value The input value
    virtual void input(int value);

protected:

private:
};

#endif 
