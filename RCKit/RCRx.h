// RCRx.h
//
// Remote Control Receiver module for RCOIP protocol
// Copyright (C) 2010-2012 Mike McCauley
// $Id: RCRx.h,v 1.6 2012/09/23 21:55:57 mikem Exp mikem $

/// \mainpage RCKit library for Arduino
///
/// This is the Arduino RCKit library.
/// 
/// RCKit provides a kit of software objects that make it easy to build an
/// RCOIP  (Remote Control Over IP) receiver on Arduino. RCOIP protocol is used to
/// carry remote control commands from a transmitter to a receiver over an IP
/// transport such as Ethernet or Wi-Fi.
///
/// As such it can be used to build Remote Controlled (RC) vehicles and devices of various kinds, along with
/// matching transmitters. Large numbers of channels can be supported, along with a back-channel 
/// which sends data from the Receiver to the Transmitter. 
/// A compatible iPhone transmitter app is also available.
/// 
/// The transmitter could be a handheld Wi-Fi enabled device such as an iPhone, iPad or Arduino based device. 
/// Or it could be an interactive program running on a desktop computer. The RCTx iPhone transmitter app is 
/// available on the Apple App Store. It provides a simple RCOIP transmitter equipped with 2 joysticks and
/// a number of switches.
///
/// The receiver (using this RCKit software) could be a remote controlled car, 
/// plane, helicopter or some other device.
///
/// The RCOIP protocol is a 2-way protocol that defines UDP messages between 
/// the RCOIP transmitter and receiver. 
/// This effectively makes the transmitter a UDP client and the receiver a UDP server. 
/// Messages sent from the transmitter to the receiver include setting analog outputs, 
/// and messages from the receiver to the transmitter include receiver status messages.
///
/// RCTx, RCKit and the RCOIP protocol offer the following advantages over conventional Remote Control:
/// \li Large numbers of channels (> 100) not just 5 or 6, including analog, digital, text, data etc.
/// \li Back channel for telemetry (voltages, signal strengths, GPS position etc)
/// \li Failsafe modes
/// \li Programmable, configurable and extensible
/// \li Works with a variety of types of vehicle and remote devices
/// \li Hackable
/// \li Opportunity to tightly integrate remote control and autonomous vehicle software control
/// \li Works with a variety of IP transports Wi-Fi (ad-hoc or infrastructure), Wired etc.
///
/// Videos explaining how it works and what you can do with it can be found at:
/// \li http://www.youtube.com/watch?v=SKwY-CcotRY
/// \li http://www.youtube.com/watch?v=i0ZogFmytPI
///
/// There is also a video showing how RCKit can be used with the IRrc library at
/// http://www.open.com.au/mikem/arduino/IRrc to control a 3 channel infra-red model helicopter at:
/// \li http://www.youtube.com/watch?v=lzRpyqnD6_M
///
/// The version of the package that this documentation refers to can be downloaded 
/// from http://www.open.com.au/mikem/arduino/RCKit/RCKit-2.4.zip
/// You can find the latest version at http://www.open.com.au/mikem/arduino/RCKit
///
/// You can also find online help and disussion at http://groups.google.com/group/rckit
/// Please use that group for all questions and discussions on this topic. 
/// Do not contact the author directly, unless it is to discuss commercial licensing.
///
/// Tested on Arduino Duemilanove, Diecimila, Mega and Asynclabs Yellowjacket
/// with arduino-1.0 and arduino 1.0.1 on OpenSuSE 12/
/// and avr-libc-1.6.2-5.11,
/// cross-avr-binutils-2.19-9.1 and cross-avr-gcc43-4.3.3_20081022-9.3
///
/// \par RCRx
///
/// RCRx class is an RCOIP receiver. It works with Arduino and a range of communications hardware like 
/// WiShield and Ethernet to receiver commands from an
/// RCOIP compliant Transmitter (such as the RCTx iPhone app available on the Apple App Store).
///
/// When the RCRx object is constructed, it must be given an array of Setter objects. 
/// When a RCOIPv1CmdSetAnalogChannels message is received by RCRx, The Setter corresponding to each 
/// Channel value in the RCOIPv1CmdSetAnalogChannels command will be passed to the 
/// respective Setter in the analogOutputs array. 
/// The Arduino software is expected to be configured so that each analogOutput is connected to a Setter that
/// will implement the received value, perhaps by setting an analog or digital output on an Arduino pin. 
/// Setter objects are provided to achieve this. See below.
///
/// RCRx will automatically respond to received commands with RCOIPv1ReplyReceiverStatus messages 
/// as appropriate to the configured timeouts etc. See the RCOIP protocol document for more details.
/// 
/// \par Setters
///
/// Setter classes are objects that receive a value, maybe transform it and then do something with it. Typically
/// they set an output pin according to the received input value, but almost any other transformation, 
/// output or communication can be imagined. 
///
/// The following output Setter objects are provided with RCKit. They can be used to translate 
/// receiver channel values into physical outputs:
/// \li AnalogSetter
/// \li DigitalSetter
/// \li ServoSetter
/// \li AccelStepperPositionSetter
/// \li AccelStepperSpeedSetter
/// \li HBridgeSetter
/// \li DifferentialSetter
///
/// The following transformation Setter objects are provided with RCKit. They can be used to 
/// transform receiver channel values before being given to one of the output Setter classes above:
/// \li Inverter
/// \li Limiter
/// \li Linear
/// 
/// \par Example Sketches
///
/// Several example Arduino sketches are included, including a regression 
/// test suite and a sample complete 5 channel receiver with Servo outputs for WiFi and Ethernet.
///
/// \par Transceivers
///
/// Version 2.0 of this library added the concept of a Transceiver, in order to be able to support 
/// multiple type of communications transport.
/// A Transceiver is an object responsible for communicating with an RCOIP transmitter. Several types of 
/// Transceiver are supported by the standard RCRx library:
/// - WiShield WiFi shield or Yellowjacket or WiFi Bee, using the WiShield library.
/// - Ethernet shield, or EtherTen, using the standard Arduino Ethernet library.
/// You can define your own subclass of the Transceiver class to implement your own transports 
/// (if you do so, consider contributing it back to the RCRx project).
/// The main RCRx reciver object must be told where it Transceiver object is, using setTransceiver(). 
/// Thereafter it will use that 
/// Transceiver to receive RCOIP requests and to send replies back to the transmitter.
///
/// \par RCTx iPhone App
///
/// RCTx is an RCOIP compliant transmitter for iPhone available on the Apple App Store 
/// at https://itunes.apple.com/us/app/rctx/id567423127?mt=8
///
/// You can use it with the WiShieldTransceiver object to use WiFi to communicate directly to a WiShield 
/// equipped RCRx receiver. Or you can use it with the EthernetTransceiver object 
/// and your LAN and Wirelesss Access Point to communicate to an Ethernet equipped RCRx receiver. 
///
/// RCTx presents a simulated RC transmitter with 2 joysticks and a number of switches. 
/// The left josystick sets channels 0 and 1 and the right joystick channels 2 and 3. 
/// The switches set channels 4 through 9 inclusive. The one connected to channel 4 is momentary contact.
///
/// To install and configure RCTx to work with a WiShield equipped RCRx:
/// \li install the RCTx app on your iPhone.
/// \li Build and upload your RCRx+WiShieldTransceiver program you your Arduino+WiShield hardware
/// \li Power up the Arduino
/// \li Turn on your iphone, go to Settings, Wi-Fi. Enable Wi-Fi
/// \li After about 30 seconds, you should see the RCArduino network appear as an available 
/// network on the iPhone. Tap on it.
/// Now tap on the RCArduino network details arrow to the right of the RCArduino line. Select 'Static'. 
/// Enter an IP Address of 169.254.1.1. Enter a Subnet Mask of 255.255.0.0
/// \li After about 10 seconds, the iPhone should be successfully connected to the RCArduino network. 
/// You now have an ad-hoc connection to the Arduino. The Arduino will have the address  169.254.1.100 
/// and the iPhone will have address 169.254.1.1
/// \li Start the RCTx app on the iPhone.
/// \li After about 5 seconds, you should see the NO CONNECT in the bottom left corner change to 
/// show RSSI and the correct battery voltage (if the Arduino is so equipped).
/// \li Move the josticks and buttons. This will send RCOIP commands to the Arduino. 
/// RCRx in the arduino will convert them to analog output signals to drive your hardware. Have fun.
///
/// To install and configure RCTx to work with an Ethernet equipped RCRx:
/// \li install the RCTx app on your iPhone.
/// \li Edit the sketch to set the desired IP address and MAC address for the Arduino
/// \li Build and upload your RCRx+EthernetTransceiver program you your Arduino+Ethernet hardware. 
/// \li Power up the Arduino, connect it to your LAN.
/// \li Turn on your iphone, go to Settings, Wi-Fi. Enable Wi-Fi and connect to your LANs 
///     wireless access point in the usual way.
/// \li Start the RCTx app on the iPhone.
/// \li Tap on the little 'i' icon on the bottom right, get the profiles page. 
///    Edit the default profile or create a new profile and enter the IP address of the Arduino that you configured above.
/// \li After about 5 seconds, you should see the NO CONNECT in the bottom left corner change to 
/// show RSSI of 0 and the correct battery voltage (if the Arduino is so equipped).
/// \li Move the josticks and buttons. This will send RCOIP commands to the Arduino. 
/// RCRx in the arduino will convert them to analog output signals to drive your hardware. Have fun.
///
///
/// \par Prerequisites
///
/// \li Arduino IDE 1.0 or later (earlier version do not support the EthernetUdp class required)
/// \li WiShield (http://asynclabs.com) edited and configured to suit (see below for help)
/// \li AccelStepper (http://www.open.com.au/mikem/arduino/AccelStepper) 
///
/// These prerequisites must be installed in the libraries directory of your Arduino devlopment environment, 
/// even if you are not going to use them with RCRx, otherwise the RCRx will not build.
/// 
/// \par Installation
///
/// Install in the usual way: unzip the distribution zip file to the libraries
/// sub-folder of your Arduino IDE sketchbook. 
///
/// \par WiShield Library Configuration
///
/// Requires the Asynclabs WiShield library to be installed, even if you are not using
/// the WiShieldTransceiver. See http://asynclabs.com/wiki/index.php?title=WiShield_library
/// Install the  WiShield library in the libraries directory of your arduino IDE installation, 
/// then follow the configuration steps below:
///
/// Support of RSSI (receiver signal strength indicator) requires mods to WiShield library g2100.c as per 
/// http://asynclabs.com/forums/viewtopic.php?f=10&t=385&start=0. You dont have to add this but its a 
/// good feature. It is included in the prebuilt WiShield library mentioned below.
///
/// Correct operation of the WiShield requires you to set the jumper on the WiShield to INT0 or DIG8 to select 
/// the arduino pin to use for WiShield interrupts, and also to make sure it agrees with the settings of 
/// USE_DIG0_INTR or  USE_DIG8_INTR in spi.h in the WiShield library (which defaults to 
/// using Arduino digital pin 2, and which means setting the WiShield jumper to INT0 setting). Yes, the naming
/// conventions are inconsistent :-(. In summary:
/// \code
///  WiShield jumper   spi.h          Arduino
///       INT0        USE_DIG0_INTR  Digital pin 2
///       D8          USE_DIG8_INTR  Digital pin 8
/// \endcode
///
/// For YellowJacket and WiFi Bee (which has no jumper), leave it as USE_DIG0_INTR.
///
/// Caution: on WiFi Bee, Arduino Digital pin 4 is connected to the WiFi Chip HIBERNATE pin. 
/// Do not use pin D4 as an RCKit output pin.
///
/// In order for WiShield library to support UDP (as needed by this module), 
/// you MUST set UIP_CONF_UDP to 1 in uip-conf.h. This is an unfortunate but necessary requirement, 
/// otherwise UDP support will not be compiled into the WiShield library. 
/// Further, you must edit apps-conf.h and make sure the only APP_* defined is APP_UDPAPP. 
/// Failure to do this will cause compile errors. 
///
/// A modified version of the WiShield library already 
/// modified and configured for use with RCKit (including RSSI support) is available at 
/// http://www.open.com.au/mikem/arduino/WiShield-v1.3.0-0-mikem-RCKit.zip
///
/// WiShield will work with Arduino Mega, but with difficulty. The problem is that with the Mega, the SPI 
/// pins that are required for interface with WiShield come out on different pins to the smaller form 
/// factor arduinos like Diecimila and Duemilanove. So, to make the Mega work with the WiShield, you 
/// have to reroute the SPI pin to different Arduino pins, as per 
/// http://asynclabs.com/forums/viewtopic.php?f=13&t=19&hilit=mega&start=10
/// 
/// By default, WiShieldTransceiver is configured as an Ad-Hoc Wi-Fi network with SSID of 'RCArduino' 
/// By default, the network is Open (ie no encryption) and
/// It is configured with a static IP address of 169.254.1.100.
/// These setting can be changed by editing WiShieldTransceiver.cpp in the RCKit distribution.
///
/// \author  Mike McCauley (mikem@open.com.au)
/// Do not contact the author directly unless it is to discuss commercial licensing. 
/// See above for support and discussion groups.
///
/// This software and the RCOIP protocol is Copyright (C) 2010-20112 Mike McCauley. Use is subject to license
/// conditions. The main licensing options available are GPL V2 or Commercial:
/// 
/// This library has been tested with Duemilanove and (WiShield 1.0 or YellowJacket or WiFi Bee 1) 
/// and iPhone 3.0
///
/// \par Open Source Licensing GPL V2
///
/// This is the appropriate option if you want to share the source code of your
/// application with everyone you distribute it to, and you also want to give them
/// the right to share who uses it. If you wish to use this software under Open
/// Source Licensing, you must contribute all your source code to the open source
/// community in accordance with the GPL Version 2 when your application is
/// distributed. See http://www.gnu.org/copyleft/gpl.html
/// 
/// \par Commercial Licensing
///
/// This is the appropriate option if you are creating proprietary applications
/// and you are not prepared to distribute and share the source code of your
/// application. Contact info@open.com.au for details.
///
/// \par Revision History
///
/// \version 1.0 Initial release
/// \version 1.1 Added Linear
/// \version 1.2 Compiles under Arduino 1.0
/// \version 1.3 Fix error in test suite tat prevvented correct tests with latest versions of AccelStepper
///              Added documentation for examples.
///              Added new class MotorControllerSetter, which can be used to control motor controllers with
///              a direction and (PWM) speed pin.
/// \version 2.0 Caution: API Change: existing RCRx sketches will not work with this new version without (minor) 
///              modifications.
///              Separate the WiShield WiFi driver code out into a separate Transceiver object.
///              Rationalise some includes and headers
///              Add support for WiShield and Ethernet transceivers, with examples to suit
/// \version 2.1 Some files were missing from the 2.0 release. Clarified the fact that only Arduino 1.0 and 
///              later is now suported (due to incompatible changes in Ethernet UDP support)
/// \version 2.2 Compiler problems were reported unless SPI.h was include first in sketches (although
///              I could not reproduce this). Changed examples to suit.
/// \version 2.3 Found and documented a problem when you use Arduino digital pin D4 as an output with
///              WiFi-Bee, which uses that pin as HIBERNATE. Dont use D4 as output with WiFi-Bee
/// \version 2.4 Fixed incorrect link to RCTx on App Store.

#ifndef RCRx_h
#define RCRx_h

#if (ARDUINO < 100)
#include "WProgram.h"
#else
#include "Arduino.h"
#endif

class Setter;
class Transceiver;

/////////////////////////////////////////////////////////////////////
/// \class RCRx RCRx.h <RCRx.h>
/// \brief Remote Control Receiver module for RCOIP protocol on Arduino.
///
/// \par Overview
/// This class implements a receiver for RCOIP (Remote Control Over IP). It starts and manages a 
/// WiFi receiver, which receives UDP messages containing RCOIP commands such as remote control channel 
/// values. When channel setting commands are received they are translated into output values which are sent 
/// to Setter objects to control the phycical output devices and pins on the Arduino. 
/// Supports WiShield 1.0 etc.
///
/// \par Outputs
/// RCRx maps RCOIP channels to physical output devices through the analogOutputs array. This is an array 
/// of Setter objects, one for each physical output to be controlled by RCRx. Whenever a RCOIP message 
/// is received with new channel settings, the input() function of each Setter with new data will be 
/// called. This will cause each Setter to set its physical output in response to the remote control
/// data received by an RCOIP. 
///
/// \par Failsafe
/// RCRx supports failsafe behaviour if a connection to the transmitter is lost.
/// RCRx monitors the time of each received RCOIP request. If no request is received for more than 
/// failInterval milliseconds, it will be considered as disconnected, and the failsafe() function of 
/// every Setter will be called, allowing each Setter to adopt its failsafe configuration 
/// (eg throttle to 0 etc). This allows remote control vehicles to fail safe if the transmitter 
/// fails or goes out of range.
class RCRx
{
public:
    /// Constructor. 
    /// After contruction and initialisation, call the init() and run() functions.
    RCRx();

    /// Tells this object where to find the transceiver object.
    /// RCRx requires an instance of a Transceiver object for the device that you are using to
    /// Received RCOIP requests from the transmitter.
    /// A number of Transceivers are provided with RCRx:
    /// - WiShieldTransceiver for WiFi transport with WiSheild
    /// - EthernetTransceiver for Ethernet transport with Ethernet shield
    /// or you can define your own.
    void setTransceiver(Transceiver* transceiver);

    /// Specifies the Setters that will be used by this receiver to set its output values
    /// Whenever a RCOIP message is received with a new value for channel n, it will be passed
    /// to the Setter at index n by calling the Setters input() function.
    /// \param[in] analogOutputs Pointer to an array pointers to Setter objects.
    /// \param[in] numAnalogOutputs Number of elements in analogOutputs
    void setOutputs(Setter** analogOutputs, uint8_t numAnalogOutputs);

    /// Set the output for channel n. Calls the Setter at index n of the analogOutputs
    /// array. Not usuallly called exernally, this is usually only called
    /// from within RCRx. Subclasses can override this to get control
    /// when new analog output values become available
    /// \param[in] channel The analog channel number output to set
    /// \param[in] value The new value to set
    virtual void setAnalogOutput(uint8_t channel, int value);

    /// Initialises the wireless WiFi receiver
    /// Call once at startup time after addresses etc have been configured.
    void init();

    /// Call this to process pending Wireless events. Call this as often as possible in your
    /// main loop. Runs the wireless driver stack or whatever in the Transceiver, 
    /// and does internal housekeeping.
    void run();

    /// Call to handle an incoming UDP message containing an RCOIP command message.
    /// This is usually only called from the Transceiver, but could be called externally 
    /// for testing purposes etc.
    /// \param[in] msg Pointer to the RCOIP message
    /// \param[in] len Length of the PCOIP mesage in bytes
    /// \param[in] rssi Receiver Signal Strength as reported by the WiFi receiver (if any)
    /// when the message was received.
    void handleRequest(uint8_t *msg, uint16_t len, uint16_t rssi);

    /// Called by RCRx when no RCOIP message has been received for more than failInterval milliseconds.
    /// Calls the failsafe function for all configured output Setters.
    void failsafe();

    /// Called by RCRx periodically (typically twice per second) to do period processing such as 
    /// detecting loss of incoming messages
    void periodicTask();

    /// Returns whether the RCRx considers itself to be connected to the transmitter.
    /// Initialsed to false. Whenever an RCOIP request is receved, set to true. If no  RCOIP request 
    /// is receved for more than  failInterval miliseconds, set to false.
    /// \return true if the RCRx is still receiving messages from the transmitter.
    boolean connected();

    /// Sends an RCOIP reply message
    /// Usually called internally at most once every _replyInterval milliseconds.
    void sendReply();

protected:

private:
    /// The transceiver
    Transceiver*  _transceiver;

    /// Array of output Setters
    Setter**      _analogOutputs;

    /// Number of Setters in _analogOutputs
    uint8_t       _numAnalogOutputs;

    /// Arduino analog input pin which yields the arduino battery voltage
    uint8_t       _batteryVoltageAnalogPin;

    /// Max time in milliseconds between RCOIP replies
    unsigned int  _replyInterval; 

    /// Max time in milliseconds between received request before RCRx is considered to be disconnected
    unsigned int  _failInterval; 

    /// The time we last got a RCOIP request from the transmitter
    unsigned long _lastRequestTime;

    /// The last time we sent a RCOIP reply to the transmitter
    unsigned long _lastReplyTime;

    /// Whether RCRx is considered to be connected to the transmitter
    boolean       _connected;

    /// The value of the RSSI (receiver signal strength indicator)
    /// in the last request received
    uint16_t      _rssi;
};

/// @example DifferentialRCRx.pde
/// This simple example handles 3 RCOIP receiver channels. Its configured like this:
/// 1 Differential motor driver (receiver channels 0 and 1) driving 4 analog outputs configured as 2 HBridges
/// 1 Digital output (horn) (receiver channel 4)
/// This is the program used for the tank shown in http://www.open.com.au/mikem/arduino/RCKit/tank.mp4

/// @example HBridge2RCRx.pde
/// This simple example handles 3 RCOIP receiver channels. Its configured like this:
/// This is the program used for the car shown in http://www.open.com.au/mikem/arduino/RCKit/car1.mp4

/// @example HBridgeRCRx.pde
/// This simple example handles 4 RCOIP receiver channels. Its configured like this:
/// 2 Servos (receiver channels 0, 1) (left joystick on RCTx)
/// 1 HBridge (receiver channel 3) driving 2 analog outputs (right joystick on RCTx)
/// 1 Digital output (horn) (receiver channel 4)

/// @example RCRxWiShield.pde
/// Receives RCOIP commmands from a WiShield and uses them to set servo
/// and digital outputs.
/// This simple example handles 5 RCOIP receiver channels. Its configured like this:
/// 4 Servos (receiver channels 0, 1, 2, 3)
/// 1 Digital output (horn) (receiver channel 4)

/// @example RCRxEthernet.pde
/// Receives RCOIP commmands on Ethernet and uses them to set servo
/// and digital outputs.
/// This simple example handles 5 RCOIP receiver channels. Its configured like this:
/// 4 Servos (receiver channels 0, 1, 2, 3)
/// 1 Digital output (horn) (receiver channel 4)

/// @example TestSuite.pde
/// Self test suite for RCKit classes


#endif 
