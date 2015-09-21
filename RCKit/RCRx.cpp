// RCRx.cpp
//
// Remote Control Receiver module for RCOIP protocol
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: RCRx.cpp,v 1.4 2012/08/25 06:18:13 mikem Exp mikem $

#include "RCRx.h"
#include "Setter.h"
#include "RCOIP.h"
#include "Transceiver.h"

// There is precisely one RCRx instance
static RCRx* rcrx;

/////////////////////////////////////////////////////////////////////
RCRx::RCRx()
{
    _analogOutputs = 0;
    _numAnalogOutputs = 0;
    _batteryVoltageAnalogPin = 0;
    _replyInterval = RCOIP_DEFAULT_REPLY_INTERVAL;
    _failInterval = RCOIP_DEFAULT_FAIL_INTERVAL;
    _lastRequestTime = 0;
    _lastReplyTime = 0;
    _connected = 0;
    _rssi = 0;

    // record this as the singleton
    rcrx = this;
}

/////////////////////////////////////////////////////////////////////
void RCRx::setTransceiver(Transceiver* transceiver)
{
    _transceiver = transceiver;
    transceiver->setDelegate(this);
}

/////////////////////////////////////////////////////////////////////
void RCRx::setOutputs(Setter** analogOutputs, uint8_t numAnalogOutputs)
{
    _analogOutputs = analogOutputs;
    _numAnalogOutputs = numAnalogOutputs;
}

/////////////////////////////////////////////////////////////////////
void RCRx::setAnalogOutput(uint8_t channel, int value)
{
    if (channel < _numAnalogOutputs && _analogOutputs[channel])
	_analogOutputs[channel]->input(value);
}

/////////////////////////////////////////////////////////////////////
void RCRx::init()
{
    _transceiver->init();
}

/////////////////////////////////////////////////////////////////////
void RCRx::run()
{
    _transceiver->run();
    periodicTask();
}

/////////////////////////////////////////////////////////////////////
// Sends a Reply message to the transmitter
void RCRx::sendReply()
{
    RCOIPv1ReplyReceiverStatus reply;
    reply.version = RC_VERSION;
    reply.RSSI = _rssi;
    reply.batteryVoltage = analogRead(_batteryVoltageAnalogPin) >> 2; // Arduino is 10 bits analog
    _transceiver->sendReply((uint8_t*)&reply, sizeof(reply));
    _lastReplyTime = _lastRequestTime;
}

/////////////////////////////////////////////////////////////////////
// This is called when a new UDP message is received in the RC port
// Caution: RSSI support requires mods to WiShield g2100.c as per 
// http://asynclabs.com/forums/viewtopic.php?f=10&t=385&start=0
void RCRx::handleRequest(uint8_t *msg, uint16_t len, uint16_t rssi)
{
    _rssi = rssi;
    RCOIPCmdSetAnalogChannels* setAnalogChannels = (RCOIPCmdSetAnalogChannels*)msg;
    if (len >= 1 && setAnalogChannels->version == RC_VERSION1)
    {
	int i;
	for (i = 0; i < len-1; i++)
	    setAnalogOutput(i, setAnalogChannels->channels[i]);
	
	// Only reply at most once per _replyInterval millis
	// Transmitter will typically interpret gap in replies
	// of 2 sec or more as bad connection
	_lastRequestTime = millis();
	if (_lastRequestTime > _lastReplyTime + _replyInterval)
	    sendReply();
    }
}

/////////////////////////////////////////////////////////////////////
boolean RCRx::connected()
{
    return _connected;
}

/////////////////////////////////////////////////////////////////////
// Call the failsafe functions of all outputs
void RCRx::failsafe()
{
    int i;
    for (i = 0; i < _numAnalogOutputs; i++)
	if (_analogOutputs[i])
	    _analogOutputs[i]->failsafe();
}

/////////////////////////////////////////////////////////////////////
// This is called during the main loop
// do some maintenance like looking for lost connections etc
void RCRx::periodicTask()
{
    boolean wasConnected = _connected;
    _connected = millis() < (_lastRequestTime + _failInterval);
    // If we just lost the connection, fail safe
    if (wasConnected && !_connected)
	failsafe();
}
