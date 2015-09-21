// WiShieldTransceiver.h
//
// Base class for an RCRx transceiver device
// Copyright (C) 2010 Mike McCauley
// $Id: DifferentialSetter.h,v 1.2 2010/06/30 02:48:59 mikem Exp $

#ifndef WiShieldTransceiver_h
#define WiShieldTransceiver_h

#include "Transceiver.h"
#include "RCOIP.h"

/////////////////////////////////////////////////////////////////////
/// \class WiShieldTransceiver WiShieldTransceiver.h <WiShieldTransceiver.h>
/// \brief Defines a WiSHield RCOIP Transceiver
///
/// This is one of several types of Transceiver that RCRx can use to communicate with
/// an RCOIP transmitter.
/// It works with the WiShield library, and with the following hardware:
/// - WiShield WiFi shield
/// - Yellowjacket (an Arduino with built in WiFi module)
///
/// The default WiFi configuration is:
/// - IP Address: 169.254.1.100
/// - Gateway and transmitter address: 169.254.1.1
/// - SSID: RCArduino
/// - WiFi security type: NONE (i.e. an open unencrypted, no password WiFi network)
/// - WiFi mode: ad-hoc (ie direct node-to-node communications)
/// You can change these default settings by editing WiShieldTransceiver.cpp. (I know thats ugly, but
/// it is a consequence of the way the WiShield library is built).
///
/// There is only permitted to be one instance of WiShieldTransceiver. This is because of the low level 
/// C code that glues the WiShield code to WiShieldTransceiver, and the fact there can also be only one instance of 
/// the WiShield object.
class WiShieldTransceiver : public Transceiver
{   
public:
    /// Constructor.
    /// Creates a new WiShieldTransceiver object.
    WiShieldTransceiver();

    /// Initialise the WiShield using the WiFi configuration in WiShieldTransceiver.cpp
    /// Call this once before using the Transceiver
    virtual void init();

    /// Poll the object for activity.
    /// This is expected to be called frequently in the main loop.
    /// It processes the WiFi stack, checking for received messages.
    /// During processing, and RCOIP message received by the preconfigured port and address
    /// will be given to the RCRx object pointed to by _delegate
    virtual void run();

    /// Send an RCOIP reply message to the sender of the current received message.
    /// \param[in] msg Pointer to the RCOP message.
    /// \param[in] len Length of the RCOIP message in bytes.
    virtual void   sendReply(uint8_t* msg, uint16_t len);
};

#endif 
