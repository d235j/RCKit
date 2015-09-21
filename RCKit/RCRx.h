// RCRx.h
//
// Remote Control Receiver module for RCOIP protocol
///
/// \mainpage RCKit library for Arduino
///
/// This is the Arduino RCKit 1.2 library.
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
/// from http://www.open.com.au/mikem/arduino/RCKit/RCKit-1.2.zip
/// You can find the latest version at http://www.open.com.au/mikem/arduino/RCKit
///
/// Tested on Arduino Duemilanove, Diecimila, Mega and Asynclabs Yellowjacket
/// with arduino-0018 on OpenSuSE 11.1 
/// and avr-libc-1.6.2-5.11,
/// cross-avr-binutils-2.19-9.1 and cross-avr-gcc43-4.3.3_20081022-9.3
///
/// \par Setters
///
/// Setter are object that receive a value, maybe transform it and then do something with it. Typically
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
/// \par RCRx
///
/// RCRx class is a Wi-Fi RCOIP receiver. It works with Arduino and WiShield and any 
/// RCOIP compliant Wi-Fi Transmitter (such as the RCTx iPhone app available on the Apple App Store).
///
/// By default, RCRx is configured as an Ad-Hoc Wi-Fi network with SSID of 'RCArduino' 
/// By default, the network is Open (ie no encryption) and
/// It is configured with a static IP address of 169.254.1.100.
/// These setting can be changed by editing RCRx.cpp in the RCKit distribution.
///
/// When the RCRx object is constructed, it must be given an array of Setter objects. 
/// When a RCOIPv1CmdSetAnalogChannels is received by RCRx, The Setter corresponding to each 
/// Channel value in the RCOIPv1CmdSetAnalogChannels command will be passed to the 
/// respective Setter in the analogOutputs array. 
/// The Arduino software is expected to be configured so that each analogOutput is connected to a Setter that
/// will implement the received value, perhaps by setting an analog or digital output on an Arduino pin. 
/// Setter objects are provided to achieve this.
///
/// RCRx will automatically respond to received commands with RCOIPv1ReplyReceiverStatus messages 
/// as appropriate to the configured timeouts etc. See the RCOIP protocol document for more details.
/// 
/// \par Example Sketches
///
/// Several example Arduino sketches are included, including a regression 
/// test suite and a sample complete 5 channel receiver with Servo outputs.
///
/// The following example sketches are provided:
/// \li TestSuite
/// \li RCRx 
/// \li HBridgeRCRx
/// \li HBridge2RCRx
/// \li DifferentialRCRx
///
///
/// \par RCTx iPhone App
///
/// RCTx is an RCOIP compliant transmitter for iPhone available on the Apple App Store 
/// at http://itunes.apple.com/app/rctx/id377833472?mt=8
///
/// It presents a simulated RC transmitter with 2 joysticks and a number of switches. 
/// The left josystick sets channels 0 and 1 and the right joystick channels 2 and 3. 
/// The switches set channels 4 through 9 inclusive. The one connected to channel 4 is momentary contact.
/// The install and configure RCTx:
/// \li install the RCTx app on your iPhone.
/// \li Build and upload your RCRx program you your Arduino+WiShield hardware
/// \li Power up the Arduino
/// \li Turn on your iphone, go to Settings, Wi-Fi. Enable Wi-Fi
/// \li After about 30 seconds, you should see the RCArduino network appear as an available 
/// network on the iPhone. Tap on it.
/// Now tap on the RCArduino network details arrow to the right of the RCArduino line. Select 'Static'. 
/// Enter an IP Address of 169.254.1.1. Enter a Subnet Mask of 255.255.0.0
/// \li After about 10 seconds, the iPhone should be successfully connected to the RCArduino network. 
/// You now have an ad-hoc connection to the Arduino. The Arduino will have the address  169.254.1.100 
/// and the iPhone wil have address 169.254.1.1
/// \li Start the RCTx app on the iPhone.
/// \li After about 5 seconds, you should see the NO CONNECT in the bottom left corner change to 
/// show RSSI and the correct battery voltage (if the Arduino is so equipped).
/// \li Move the josticks and buttons. This will send RCOIP commands to the Arduino. 
/// RCRx in the arduino will convert them to analog output signals to drive your hardware. Have fun.
///
/// \par Prerequisites
///
/// Requires:
/// \li WiShield (http://asynclabs.com) 
/// \li AccelStepper (http://www.open.com.au/mikem/arduino/AccelStepper) 
/// libraries to also be installed.
/// 
/// \par Installation
///
/// Install in the usual way: unzip the distribution zip file to the libraries
/// sub-folder of your sketchbook. 
///
/// \author  Mike McCauley (mikem@open.com.au)
///
/// This software and the RCOIP protocol is Copyright (C) 2010 Mike McCauley. Use is subject to license
/// conditions. The main licensing options available are GPL V2 or Commercial:
/// 
/// \par Open Source Licensing GPL V2
/// This is the appropriate option if you want to share the source code of your
/// application with everyone you distribute it to, and you also want to give them
/// the right to share who uses it. If you wish to use this software under Open
/// Source Licensing, you must contribute all your source code to the open source
/// community in accordance with the GPL Version 2 when your application is
/// distributed. See http://www.gnu.org/copyleft/gpl.html
/// 
/// \par Commercial Licensing
/// This is the appropriate option if you are creating proprietary applications
/// and you are not prepared to distribute and share the source code of your
/// application. Contact info@open.com.au for details.
///
/// \par Revision History
/// \version 1.0 Initial release
/// \version 1.1 Added Linear
/// \version 1.2 Compiles under Arduino 1.0

// Copyright (C) 2010 Mike McCauley
// $Id: RCRx.h,v 1.4 2010/06/30 02:48:59 mikem Exp mikem $

#ifndef RCRx_h
#define RCRx_h

#include <WiShield.h>
#include <inttypes.h>

class Setter;

/////////////////////////////////////////////////////////////////////
/// \class RCRx RCRx.h <RCRx.h>
/// \brief Remote Control Receiver module for RCOIP protocol on Arduino
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
///
/// \par WiShield Library Configuration
/// Requires the Asynclabs WiShield library. See http://asynclabs.com/wiki/index.php?title=WiShield_library
/// Install the  WiShield library in the libraries directory of your arduino IDE installation, 
/// then follow the configuration steps below:
///
/// Support of RSSI (receiver signal strength indicator) requires mods to WiShield library g2100.c as per 
/// http://asynclabs.com/forums/viewtopic.php?f=10&t=385&start=0. You dont have to add this but its a 
/// good feature.
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
/// For YellowJacket (which has no jumper), leave it as USE_DIG0_INTR.
///
/// In order for WiShield library to support UDP (as needed by this module), 
/// you MUST set UIP_CONF_UDP to 1 in uip-conf.h. This is an unfortunate but necessary requirement, 
/// otherwise UDP support will not be compiled into the WiShield library. 
/// Further, you must edit apps-conf.h and make sure the only APP_* defined is APP_UDPAPP. 
/// Failure to do this will cause compile errors. A modified version of the WiShield library already 
/// edited for use with RCKit is available at 
/// http://www.open.com.au/mikem/arduino/WiShield-v1.3.0-0-mikem-RCKit.zip
///
/// WiShield will work with Arduino Mega, but with difficulty. The problem is that with the Mega, the SPI 
/// pins that are required for interface with WiShield come out on different pins to the smaller form 
/// factor arduinos like Diecimila and Duemilanove. So, to make the Mega work with the WiShield, you 
/// have to reroute the SPI pin to different Arduino pins, as per 
/// http://asynclabs.com/forums/viewtopic.php?f=13&t=19&hilit=mega&start=10
///
/// This library has been tested with Duemilanove and WiShield 1.0 and iPhone 3.0
///
/// \par Installation
///
/// Install in the usual way: unzip the distribution zip file to the libraries
/// sub-folder of your sketchbook. Dont foget the prerequisites too.
class RCRx
{
public:
    /// Constructor. After contruction and initialisation, call the init() and run() functions.
    RCRx();

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
    /// main loop. Runs the wireless driver stack.
    void run();

    /// Call to handle an incoming UDP message containing an RCOIP command message.
    /// This is usually only called from within RCRx, but could be called externally 
    /// for testing purposes etc.
    /// \param[in] msg Pointer to the UDP message
    /// \param[in] len Length of the UDP mesage in bytes
    /// \param[in] rssi Receiver Signal Strength as reported by the WiFi receiver 
    /// when the message was received.
    void handleRequest(uint8_t *msg, uint16_t len, uint16_t rssi);

    /// Called by RCRx when no RCOIP message has been received for more than failInterval miliseconds.
    /// Calls the failsafe function for all configured output Setters.
    void failsafe();

    /// Called by RCRx periodically (typically twice per second) to do period processing such as 
    /// detecting loss of messages
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

#endif 
