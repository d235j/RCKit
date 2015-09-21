// Transceiver.h
//
// Base class for an RCRx transceiver device
// Copyright (C) 2010 Mike McCauley
// $Id: Transceiver.h,v 1.1 2012/09/23 21:55:57 mikem Exp mikem $

#ifndef Transceiver_h
#define Transceiver_h

#include <RCRx.h>

/////////////////////////////////////////////////////////////////////
/// \class Transceiver Transceiver.h <Transceiver.h>
/// \brief Abstract base class for a transceiver device that will send and receive messages
/// on behalf of RCRx class.
///
/// RXRx class requires to be connected to a Transceiver, and the transceiver is responsible for
/// receiving requests from an RCOIP transmitter and sending replies back to it. 
/// Any transport or media can in principle be supported. RCRx includes some specific implementations
/// for example for WiShield and Ethernet
///
/// Real transceiver objects must inherit from this subclass and implement the 
/// sendReply() function and call delegate->handleRequest(uint8_t *msg, uint16_t len, uint16_t rssi)
/// whenever an RCOI message is received.
class Transceiver
{   
public:
    /// Initialise the object.
    /// You are required to call this once during setup().
    /// Subclasses must implement this: there is no base implementation.
    virtual void init();

    /// Poll the object for activity.
    /// You are required to call this frequently in your main loop
    /// Subclasses must implement this: there is no base implementation.
    virtual void run();

    /// Sets the delegate object.
    /// The delegate will get its handleRequest(uint8_t *msg, uint16_t len, uint16_t rssi) 
    /// function called whenever an RCOIP message is received.
    /// The delegate can use the sendReply() function to send an RCOIP message back to the 
    /// sender of the currently received message.
    /// \param[in] delegate Pointer to the delegate RXRx object
    virtual void   setDelegate(RCRx* delegate);

    /// Passes the received message to the delegate.
    /// Call this when the Transceiver has received a message from the RCOIP transmitter.
    /// The optional rssi parameter is an indication of the received signal strength, but if your
    /// Transceiver has no such measure, you dont need to supply it
    /// \param[in] msg Pointer to the RCOP message.
    /// \param[in] len Length of the RCOIP message in bytes.
    /// \param[in] rssi Receiver Signal Strength as reported by the WiFi receiver (if any)
    virtual void receivedRequest(uint8_t* msg, uint16_t len, uint16_t rssi = 0);

    /// Sends an RCOIP reply message to the sender of the current message
    /// Subclasses must implement this: there is no base implementation.
    /// \param[in] msg Pointer to the RCOP message.
    /// \param[in] len Length of the RCOIP message in bytes.
    virtual void   sendReply(uint8_t* msg, uint16_t len);

protected:
    /// Object whose handleRequest() function will be called whenever an RCOIP message is received
    RCRx*  _delegate;
};

#endif 
