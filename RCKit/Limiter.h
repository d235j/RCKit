// Limiter.h
//
// Setter class that limits its input to between specified min and max values
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: Limiter.h,v 1.3 2012/08/25 06:18:13 mikem Exp mikem $

#ifndef Limiter_h
#define Limiter_h

#include "Setter.h"

/////////////////////////////////////////////////////////////////////
/// \class Limiter Limiter.h <Limiter.h>
/// \brief Setter class that limits its output to between specified min and max values
///
/// Limiter limits its output to between specified min and max values
/// The resulting output value is sent to the next Setter (the target) in the chain.
///
class Limiter : public Setter
{   
public:
    /// Constructor.
    /// All output values will be constrained to be within min to max (inclusive)
    Limiter(int min, int max);
    
    /// Input the value to be inverted
    /// \param[in] value The input value
    virtual void input(int value);

protected:

private:

    /// The minimum permitted value
    int _min;

    /// The maximum permitted value
    int _max;
};

#endif 
