// EthernetTransceiver.h
//
// Base class for an RCRx transceiver device
// Copyright (C) 2010 Mike McCauley
// $Id: DifferentialSetter.h,v 1.2 2010/06/30 02:48:59 mikem Exp $

#ifndef EthernetTransceiver_h
#define EthernetTransceiver_h

#include "Transceiver.h"
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <IPAddress.h>
#include "RCOIP.h"

/////////////////////////////////////////////////////////////////////
/// \class EthernetTransceiver EthernetTransceiver.h <EthernetTransceiver.h>
/// \brief Defines an Ethernet RCOIP Transceiver.
///
/// This is one of several types of Transceiver that RCRx can use to communicate with
/// an RCOIP transmitter.
/// It works with the standard Arduino Ethernet library, and with the following hardware:
/// - EthernetShield
///
class EthernetTransceiver : public Transceiver
{   
public:
    /// Constructor.
    /// Creates a new EthernetTransceiver object with the given addresses.
    /// The addresses should be unique in your network.
    /// \param[in] macaddress The MAC address for this hsot, an array of 6 bytes
    /// \param[in] ipaddress The IPv4 IP address for this host
    /// \param[in] port The UDP port to listen for RCOIP requests, defaults to RCOIP_DEFAULT_RECEIVER_UDP_PORT (9048)
    EthernetTransceiver(byte* macaddress, IPAddress* ipaddress, unsigned int port = RCOIP_DEFAULT_RECEIVER_UDP_PORT);

    /// Initialise the object.
    /// Call this once before using the Transceiver
    virtual void init();

    /// Poll the object for activity.
    /// This is expected to be called frequently in the main loop
    /// It processes the Ethernet stack, checking for received messages.
    /// During processing, and RCOIP message receibed by the preconfigured port and address
    /// will be given to the RCRx object pointed to by _delegate
    virtual void run();

    /// Send an RCOIP reply message to the sender of the current received message.
    /// \param[in] msg Pointer to the RCOP message.
    /// \param[in] len Length of the RCOIP message in bytes.
    virtual void   sendReply(uint8_t* msg, uint16_t len);

private:

    /// The MAC address of this node as passed to the constructor
    byte         _thisMACaddress[6];

    /// The IPv$ IP address of this node as passed to the constructor
    IPAddress    _thisIpAddress;

    /// The UDP port to listen on as passed to the constructor
    unsigned int _thisPort;
    
    /// Buffer for receiving UDP packets
    char _packetBuffer[UDP_TX_PACKET_MAX_SIZE]; 

    /// Instance of the EthernetUDP instance to let us send and receive packets over UDP
    EthernetUDP _udp;
};

#endif 
