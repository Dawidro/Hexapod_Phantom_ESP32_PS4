//====================================================================
//Project Lynxmotion Phoenix
//Description: 
//    This is the hardware configuration file for the 
//    Hex Robot with ESP32, SSC-32 servo controller and PS4 controller
//  
//Date: January 2025
//Programmer: [Your Name] (Based on KurtE's Hex_Cfg.h)
//
//NEW IN V1.0
//   - Initial Release for ESP32 + SSC-32U + PS4
//
//====================================================================
#ifndef HEX_CFG_H
#define HEX_CFG_H

//=============================================================================
// Define which input method we are using
//=============================================================================
#define USEPS4              // Use PS4 Controller

//=============================================================================
// PS4 Controller Configuration
//=============================================================================
#ifdef USEPS4
// PS4 Controller Bluetooth MAC Address
// Replace with your controller's actual MAC address
// Find it using: Bluetooth settings on your PC/Mac, or SixaxisPairTool on Windows
#define PS4_MAC_ADDRESS "1a:2b:3c:01:01:01"  // <-- CHANGE THIS TO YOUR PS4 CONTROLLER MAC

// Optional: If you want PS4 library to auto-pair (leave undefined for default pairing)
// #define PS4_AUTO_PAIR
#endif

//=============================================================================
// Define which Servo Driver we are using
//=============================================================================
#define USESSC32            // Using SSC-32 servo controller

//=============================================================================
// ESP32 Serial Configuration
//=============================================================================
// Debug Serial Port (USB)
#define DBGSerial Serial
#define DBG_SERIAL_BAUD 115200

// SSC-32 Serial Port (Hardware Serial)
#define SSCSerial Serial2
#define SSC_BAUD 115200
#define SSC_RX_PIN 16       // ESP32 RX pin connected to SSC-32 TX
#define SSC_TX_PIN 17       // ESP32 TX pin connected to SSC-32 RX

//=============================================================================
// Sound Configuration
//=============================================================================
// If you have a buzzer connected, define the pin here
// #define SOUND_PIN 25      // GPIO pin for piezo buzzer
// If undefined, MSound will do nothing

//=============================================================================
// Optional Features
//=============================================================================
// Terminal Monitor for debug commands via serial
#define OPT_TERMINAL_MONITOR
#define OPT_TERMINAL_MONITOR_IC  // Allow input controller terminal commands

// Servo offset calibration mode - use 'O' command in terminal
#define OPT_FIND_SERVO_OFFSETS   // Enables interactive servo offset adjustment

// Allow sketch to add custom setup code
// #define OPT_SKETCHSETUP      // If defined, calls SketchSetup() from your .ino

// Background Process - Allow background tasks during servo moves
// #define OPT_BACKGROUND_PROCESS  // If defined, calls BackgroundProcess()

// GP Player - Sequence playback support
// #define OPT_GPPLAYER         // Enable if you want to play sequences

//=============================================================================
//[Botboarduino Pin Numbers]
// Not used on ESP32, but kept for compatibility
//=============================================================================
#define SOUND_PIN    0xFF   // Tell system we have no sound (or define actual pin if you have buzzer)

//=============================================================================
//[SSC32 Pin Numbers]
// SSC-32 Channel assignments are defined directly below in the pin mapping
//=============================================================================

//=============================================================================
// Define Leg/Servo Mapping
//=============================================================================
// SSC-32 Channel assignments for each leg
// Leg 0 = Right Rear, Leg 1 = Right Middle, Leg 2 = Right Front
// Leg 3 = Left Rear,  Leg 4 = Left Middle,  Leg 5 = Left Front

#define cRRCoxaPin      0   // Right Rear Coxa
#define cRRFemurPin     1   // Right Rear Femur  
#define cRRTibiaPin     2   // Right Rear Tibia

#define cRMCoxaPin      4   // Right Middle Coxa
#define cRMFemurPin     5   // Right Middle Femur
#define cRMTibiaPin     6   // Right Middle Tibia

#define cRFCoxaPin      8   // Right Front Coxa
#define cRFFemurPin     9   // Right Front Femur
#define cRFTibiaPin     10  // Right Front Tibia

#define cLRCoxaPin      16  // Left Rear Coxa
#define cLRFemurPin     17  // Left Rear Femur
#define cLRTibiaPin     18  // Left Rear Tibia

#define cLMCoxaPin      20  // Left Middle Coxa
#define cLMFemurPin     21  // Left Middle Femur
#define cLMTibiaPin     22  // Left Middle Tibia

#define cLFCoxaPin      24  // Left Front Coxa
#define cLFFemurPin     25  // Left Front Femur
#define cLFTibiaPin     26  // Left Front Tibia

// Note: Skipped channels (3, 7, 11, 19, 23, 27) can be used for other purposes
// or kept open for future expansion

//=============================================================================
// Servo Mapping Arrays
//=============================================================================
// Create arrays in program memory to save RAM
static const byte PROGMEM cCoxaPin[] = {
  cRRCoxaPin,  cRMCoxaPin,  cRFCoxaPin,  cLRCoxaPin,  cLMCoxaPin,  cLFCoxaPin};
static const byte PROGMEM cFemurPin[] = {
  cRRFemurPin, cRMFemurPin, cRFFemurPin, cLRFemurPin, cLMFemurPin, cLFFemurPin};
static const byte PROGMEM cTibiaPin[] = {
  cRRTibiaPin, cRMTibiaPin, cRFTibiaPin, cLRTibiaPin, cLMTibiaPin, cLFTibiaPin};

#ifdef c4DOF
static const byte PROGMEM cTarsPin[] = {
  cRRTarsPin,  cRMTarsPin,  cRFTarsPin,  cLRTarsPin,  cLMTarsPin,  cLFTarsPin};
#endif

//=============================================================================
//[Hex Configuration]
//=============================================================================

//=============================================================================
// Individual Servo Ranges
//=============================================================================
#define cRRCoxaMax1	740
#define cRRFemurMin1	-1010
#define cRRFemurMax1	950
#define cRRTibiaMin1	-1060
#define cRRTibiaMax1	770

#define cRMCoxaMin1	-530	//Mechanical limits of the Right Middle Leg, decimals = 1
#define cRMCoxaMax1	530
#define cRMFemurMin1	-1010
#define cRMFemurMax1	950
#define cRMTibiaMin1	-1060
#define cRMTibiaMax1	770

#define cRFCoxaMin1	-580	//Mechanical limits of the Right Front Leg, decimals = 1
#define cRFCoxaMax1	740
#define cRFFemurMin1	-1010
#define cRFFemurMax1	950
#define cRFTibiaMin1	-1060
#define cRFTibiaMax1	770

#define cLRCoxaMin1	-740	//Mechanical limits of the Left Rear Leg, decimals = 1
#define cLRCoxaMax1	260
#define cLRFemurMin1	-950
#define cLRFemurMax1	1010
#define cLRTibiaMin1	-770
#define cLRTibiaMax1	1060

#define cLMCoxaMin1	-530	//Mechanical limits of the Left Middle Leg, decimals = 1
#define cLMCoxaMax1	530
#define cLMFemurMin1	-950
#define cLMFemurMax1	1010
#define cLMTibiaMin1	-770
#define cLMTibiaMax1	1060

#define cLFCoxaMin1	-740	//Mechanical limits of the Left Front Leg, decimals = 1
#define cLFCoxaMax1	580
#define cLFFemurMin1	-950
#define cLFFemurMax1	1010
#define cLFTibiaMin1	-770
#define cLFTibiaMax1	1060

//--------------------------------------------------------------------
//[LEG DIMENSIONS]
//--------------------------------------------------------------------
#define cXXCoxaLength     29    // This is for TH3-R legs
#define cXXFemurLength    76
#define cXXTibiaLength    106
#define cXXTarsLength     85    // 4DOF only...

#define cRRCoxaLength     cXXCoxaLength	    //Right Rear leg
#define cRRFemurLength    cXXFemurLength
#define cRRTibiaLength    cXXTibiaLength
#define cRRTarsLength	    cXXTarsLength	    //4DOF ONLY

#define cRMCoxaLength     cXXCoxaLength	    //Right middle leg
#define cRMFemurLength    cXXFemurLength
#define cRMTibiaLength    cXXTibiaLength
#define cRMTarsLength	    cXXTarsLength	    //4DOF ONLY

#define cRFCoxaLength     cXXCoxaLength	    //Rigth front leg
#define cRFFemurLength    cXXFemurLength
#define cRFTibiaLength    cXXTibiaLength
#define cRFTarsLength	    cXXTarsLength    //4DOF ONLY

#define cLRCoxaLength     cXXCoxaLength	    //Left Rear leg
#define cLRFemurLength    cXXFemurLength
#define cLRTibiaLength    cXXTibiaLength
#define cLRTarsLength	    cXXTarsLength    //4DOF ONLY

#define cLMCoxaLength     cXXCoxaLength	    //Left middle leg
#define cLMFemurLength    cXXFemurLength
#define cLMTibiaLength    cXXTibiaLength
#define cLMTarsLength	    cXXTarsLength	    //4DOF ONLY

#define cLFCoxaLength     cXXCoxaLength	    //Left front leg
#define cLFFemurLength    cXXFemurLength
#define cLFTibiaLength    cXXTibiaLength
#define cLFTarsLength	    cXXTarsLength	    //4DOF ONLY


//=============================================================================
// Body Dimensions
//=============================================================================
#define cRRCoxaAngle1   -600       //Default Coxa setup angle, decimals = 1
#define cRMCoxaAngle1    0          //Default Coxa setup angle, decimals = 1
#define cRFCoxaAngle1    600        //Default Coxa setup angle, decimals = 1
#define cLRCoxaAngle1    -600       //Default Coxa setup angle, decimals = 1
#define cLMCoxaAngle1    0          //Default Coxa setup angle, decimals = 1
#define cLFCoxaAngle1    600        //Default Coxa setup angle, decimals = 1

#define cRROffsetX 	-43	    //Distance X from center of the body to the Right Rear coxa
#define cRROffsetZ 	82	    //Distance Z from center of the body to the Right Rear coxa
#define cRMOffsetX 	-63	    //Distance X from center of the body to the Right Middle coxa
#define cRMOffsetZ 	0	    //Distance Z from center of the body to the Right Middle coxa
#define cRFOffsetX 	-43	    //Distance X from center of the body to the Right Front coxa
#define cRFOffsetZ 	-82	    //Distance Z from center of the body to the Right Front coxa

#define cLROffsetX 	43	    //Distance X from center of the body to the Left Rear coxa
#define cLROffsetZ 	82	    //Distance Z from center of the body to the Left Rear coxa
#define cLMOffsetX 	63	    //Distance X from center of the body to the Left Middle coxa
#define cLMOffsetZ 	0	    //Distance Z from center of the body to the Left Middle coxa
#define cLFOffsetX 	43	    //Distance X from center of the body to the Left Front coxa
#define cLFOffsetZ 	-82	    //Distance Z from center of the body to the Left Front coxa

//---------------------------
//=============================================================================
// Start Position of Legs
//=============================================================================
#define cHexInitXZ      105    // Default distance from center to foot in X/Z plane
#define cHexInitXZCos   53     // Default distance X - From center of body to foot (cos(45) * cHexInitXZ)
#define cHexInitXZSin   91     // Default distance Z - From center of body to foot (sin(45) * cHexInitXZ)
#define cHexInitY       25     // Default height of body from ground

//=============================================================================
// Body and Movement Settings
//=============================================================================
#define cRRInitPosX     CHexInitXZCos60      //Start positions of the Right Rear leg
#define cRRInitPosY     CHexInitY
#define cRRInitPosZ     CHexInitXZSin60

#define cRMInitPosX     cHexInitXZ      //Start positions of the Right Middle leg
#define cRMInitPosY     CHexInitY
#define cRMInitPosZ     0

#define cRFInitPosX     CHexInitXZCos60      //Start positions of the Right Front leg
#define cRFInitPosY     CHexInitY
#define cRFInitPosZ     -CHexInitXZSin60

#define cLRInitPosX     CHexInitXZCos60      //Start positions of the Left Rear leg
#define cLRInitPosY     CHexInitY
#define cLRInitPosZ     CHexInitXZSin60

#define cLMInitPosX     cHexInitXZ      //Start positions of the Left Middle leg
#define cLMInitPosY     CHexInitY
#define cLMInitPosZ     0

#define cLFInitPosX     CHexInitXZCos60      //Start positions of the Left Front leg
#define cLFInitPosY     CHexInitY
#define cLFInitPosZ     -CHexInitXZSin60

//=============================================================================
// Debug Options
//=============================================================================
#ifdef OPT_TERMINAL_MONITOR
// Allow terminal monitor to output extra debug information
// #define DEBUG_IOPINS
#endif

#endif // HEX_CFG_H