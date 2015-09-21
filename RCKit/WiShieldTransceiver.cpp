// WiShieldTransceiver.cpp
//
// Class for WiShield based RCOIP transceiver
/// \author  Mike McCauley (mikem@airspayce.com)
///
// Copyright (C) 2012 Mike McCauley
// $Id: WiShieldTransceiver.cpp,v 1.1 2012/09/23 21:55:57 mikem Exp mikem $

#include "WiShieldTransceiver.h"
// .pde file must also #include <WiShield.h>
#include <WiShield.h>
#include <witypes.h>
#include <g2100.h>
#include "RCRx.h"

// WiShield Wireless configuration parameters ----------------------------------------
// YOU MUST EDIT THESE HERE TO SUIT YOUR NETWORK

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

/// WPA/WPA2 passphrase (if wireless_mode ZG_SECURITY_TYPE_WPA or ZG_SECURITY_TYPE_WPA2)
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

// Rememeber the singleton instance of the WiShieldTransceiver
// Need this because of ugly C glue code
WiShieldTransceiver* theTransceiver = NULL;

/////////////////////////////////////////////////////////////////////
// Glue between the WiShield C side and the RCRx C++ side
// Most of this is equivalent to the contents of udpapp.c example in WiShield
// This C interface explains why we can only have at most one instance of WiShieldTransceiver
// Also works with Seeed Studio WiFi-Bee, provided you do not use Arduino Digital pin 4 as an output 
// (it is cponnected to HIBERNATE on the WiFi Bee).
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
	    // Give it to the delegate
	    if (theTransceiver)
		theTransceiver->receivedRequest((uint8_t*)uip_appdata, uip_len, get_rssi());
	    uip_flags &= (~UIP_NEWDATA);
	} while (1); // Forever, one connection only, need to reset after
	PT_END(&s.pt);
    }

    // This is called by the WiShield UIP code
    void udpapp_appcall(void)
    {
	handle_connection();
    }
}

/////////////////////////////////////////////////////////////////////
WiShieldTransceiver::WiShieldTransceiver()
{
    theTransceiver = this;
}

/////////////////////////////////////////////////////////////////////
void WiShieldTransceiver::init()
{
    WiFi.init();
}

/////////////////////////////////////////////////////////////////////
void WiShieldTransceiver::run()
{
    WiFi.run();
}

/////////////////////////////////////////////////////////////////////
void WiShieldTransceiver::sendReply(uint8_t* msg, uint16_t len)
{
    udpSendReply(msg, len);
}
