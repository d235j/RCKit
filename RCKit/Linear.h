// Linear.h
//
// Setter class that implements linear transform of its input value
/// \author  Mike McCauley (mikem@airspayce.com)
///
// Copyright (C) 2010 Mike McCauley
// $Id: Linear.h,v 1.1 2012/08/25 06:18:13 mikem Exp $

#ifndef Linear_h
#define Linear_h

#include "Setter.h"

/////////////////////////////////////////////////////////////////////
/// \class Linear Linear.h <Linear.h>
/// \brief Setter class that implements linear transform of its input value
///
/// Linear implements a y = mx + x linear transform of the input value.
/// The resulting output value is sent to the next Setter (the target) in the chain.
///
class Linear : public Setter
{   
public:
    /// Constructor.
    /// Output will be calculated according to out = (in * gain) + offset
    Linear(float gain, int offset);
    
    /// Input the value to be transformed
    /// \param[in] value The input value
    virtual void input(int value);

protected:

private:

    /// Offset added to the output value
    int _offset;

    /// Gain multiplied by the input value
    float _gain;
};

#endif 
