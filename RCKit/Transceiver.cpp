// Transceiver.cpp
//
// Abstract base class for RCOIP transceivers
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2012 Mike McCauley
// $Id: Transceiver.cpp,v 1.1 2012/09/23 21:55:57 mikem Exp mikem $

#include "Transceiver.h"

/////////////////////////////////////////////////////////////////////
void Transceiver::setDelegate(RCRx* delegate)
{
    _delegate = delegate;
}

/////////////////////////////////////////////////////////////////////
void Transceiver::receivedRequest(uint8_t* msg, uint16_t len, uint16_t rssi)
{
    if (_delegate)
	_delegate->handleRequest(msg, len, rssi);
}

