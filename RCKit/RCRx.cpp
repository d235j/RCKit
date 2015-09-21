// RCRx.cpp
//
// Remote Control Receiver module for RCOIP protocol
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: RCRx.cpp,v 1.3 2010/06/28 00:56:10 mikem Exp $

#if (ARDUINO < 100)
#include "WProgram.h"
#else
#include "Arduino.h"
#endif
#include "RCRx.h"
#include "Setter.h"
#include "RCOIP.h"
#include <HardwareSerial.h>
#include "g2100.h"

// There is precisely one RCRx instance
static RCRx* rcrx;

// WiShield Wireless configuration parameters ----------------------------------------

// AdHoc connection for direct connection to iPhone etc.
unsigned char local_ip[] = {169,254,1,100};
unsigned char gateway_ip[] = {169,254,1,1};
unsigned char subnet_mask[] = {255,255,0,0};
const prog_char ssid[] PROGMEM = {"RCArduino"};		// max 32 bytes
unsigned char security_type = ZG_SECURITY_TYPE_NONE;	// _NONE, _WEP, _WPA, _WPA2
unsigned char wireless_mode = WIRELESS_MODE_ADHOC;

// Infrastructure connection to a wireless access point
//unsigned char local_ip[] = {203,63,154,100};
//unsigned char gateway_ip[] = {203,63,154,248};
//unsigned char subnet_mask[] = {255,255,255,0};
//const prog_char ssid[] PROGMEM = {"zyxel-b-3000a"};	// max 32 bytes
//unsigned char security_type = ZG_SECURITY_TYPE_WPA;	// _NONE, _WEP, _WPA, _WPA2
//unsigned char wireless_mode = WIRELESS_MODE_INFRA;

// WPA/WPA2 passphrase (if wireless_mode ZG_SECURITY_TYPE_WPA or ZG_SECURITY_TYPE_WPA2)
const prog_char security_passphrase[] PROGMEM = {"donot8me"};	// max 64 characters

// WEP 128-bit keys if wireless_mode ZG_SECURITY_TYPE_WEP
// sample HEX keys
prog_uchar wep_keys[] PROGMEM = 
{ 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,	// Key 0
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Key 1
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Key 2
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	// Key 3
};

unsigned char ssid_len;
unsigned char security_passphrase_len;
uint16_t port = RCOIP_DEFAULT_RECEIVER_UDP_PORT;

/////////////////////////////////////////////////////////////////////
// Glue between the WiShield C side and the RCRx C++ side
// Most of this is equivalent to the contents of udpapp.c example in WiShield
extern "C"
{
#include "uip.h"
#include "udpapp.h"
#include "config.h"

    static struct udpapp_state s;

    // Call this to send a UDP reply to the current message
    static void udpSendReply(uint8_t* msg, uint16_t len)
    {
	uip_send(msg, len);
    }
    
    // This is required to satisfy references in WiShield
    // It is to do with the (unused) TCP support in the WiShield UIP stackg.
    void dummy_app_appcall(void)
    {
    }

    // REVISIT: should be configurable from outside here
    void udpapp_init(void)
    {
	uip_ipaddr_t addr;
	struct uip_udp_conn *c;
    
	uip_ipaddr(&addr, 0, 0, 0, 0); // Take requests from address
	c = uip_udp_new(&addr, HTONS(0)); // and any port
	if(c != NULL)
	    uip_udp_bind(c, HTONS(port)); // and directed to this port
	PT_INIT(&s.pt);
    }
    // This thread will handle one UDP 'connection'
    // Caution: RSSI support requires mods to WiShield g2100.c as per 
    // http://asynclabs.com/forums/viewtopic.php?f=10&t=385&start=0
    extern uint16_t get_rssi();
    static PT_THREAD(handle_connection(void))
    {
	PT_BEGIN(&s.pt);
	do
	{
	    PT_WAIT_UNTIL(&s.pt, uip_newdata());
	    // Give it to the singleton instance of RCRx
	    rcrx->handleRequest((uint8_t*)uip_appdata, uip_len, get_rssi());
	    uip_flags &= (~UIP_NEWDATA);
	} while (1); // Forever, one connection only, need to reset after
	PT_END(&s.pt);
    }

    // This is called by the WiShield UIP code
    void udpapp_appcall(void)
    {
	rcrx->periodicTask();
	handle_connection();
    }
}

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
    WiFi.init();
}

/////////////////////////////////////////////////////////////////////
void RCRx::run()
{
    WiFi.run();
}

/////////////////////////////////////////////////////////////////////
// Sends a Reply message to the transmitter
void RCRx::sendReply()
{
    RCOIPv1ReplyReceiverStatus reply;
    reply.version = RC_VERSION;
    reply.RSSI = _rssi;
    reply.batteryVoltage = analogRead(_batteryVoltageAnalogPin) >> 2; // Arduino is 10 bits analog
    udpSendReply((uint8_t*)&reply, sizeof(reply));
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
// This is called twice per second or so by the UDP code
// do some maintenance like looking for lost connections etc
void RCRx::periodicTask()
{
    boolean wasConnected = _connected;
    _connected = millis() < (_lastRequestTime + _failInterval);
    // If we just lost the connection, fail safe
    if (wasConnected && !_connected)
	failsafe();
}
