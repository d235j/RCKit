// EthernetTransceiver.cpp
//
// Class for Ethernet based RCOIP transceiver
/// \author  Mike McCauley (mikem@airspayce.com)
///
// Copyright (C) 2012 Mike McCauley
// $Id: EthernetTransceiver.cpp,v 1.1 2012/09/23 21:55:57 mikem Exp mikem $

#include <EthernetTransceiver.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <RCOIP.h>
#include <RCRx.h>

/////////////////////////////////////////////////////////////////////
EthernetTransceiver::EthernetTransceiver(byte* macaddress, IPAddress* ipaddress, unsigned int port)
{
    memcpy(_thisMACaddress, macaddress, sizeof(_thisMACaddress));
    _thisIpAddress = *ipaddress;
    _thisPort = port;
}

/////////////////////////////////////////////////////////////////////
void EthernetTransceiver::init()
{
    // start the Ethernet and UDP:
    Ethernet.begin(_thisMACaddress, _thisIpAddress);
    _udp.begin(_thisPort);
}

/////////////////////////////////////////////////////////////////////
void EthernetTransceiver::run()
{
    int packetSize = _udp.parsePacket();
    if (_udp.available())
    {
	// read the packet into packetBufffer
	_udp.read(_packetBuffer, UDP_TX_PACKET_MAX_SIZE);

	// Call the delegate with the message
	receivedRequest((uint8_t*)_packetBuffer, packetSize, 0);
    }
}

/////////////////////////////////////////////////////////////////////
void EthernetTransceiver::sendReply(uint8_t* msg, uint16_t len)
{
    // These are the address and port of the sender of the current request
    _udp.beginPacket(_udp.remoteIP(), _udp.remotePort());
    _udp.write(msg, len);
    _udp.endPacket();
}
