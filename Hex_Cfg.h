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
//#ifdef USEPS4
// PS4 Controller Bluetooth MAC Address
// Replace with your controller's actual MAC address
// Find it using: Bluetooth settings on your PC/Mac, or SixaxisPairTool on Windows
//#define PS4_MAC_ADDRESS "1a:2b:3c:01:01:01"  // <-- CHANGE THIS TO YOUR PS4 CONTROLLER MAC

// Optional: If you want PS4 library to auto-pair (leave undefined for default pairing)
// #define PS4_AUTO_PAIR
//#endif

//=============================================================================
// Define which Servo Driver we are using
//=============================================================================
#define USESSC32            // Using SSC-32 servo controller
//#define	cSSC_BINARYMODE	1			// Define if your SSC-32 card supports binary mode.

//[SERIAL CONNECTIONS]
//=============================================================================
// ESP32 Serial Configuration
//=============================================================================
// Debug Serial Port (USB)
#define DBGSerial Serial
#define DBG_SERIAL_BAUD 115200

// SSC-32 Serial Port (Hardware Serial)
#define SSCSerial Serial2
#define cSSC_BAUD 115200
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
//#define SOUND_PIN    0xFF   // Tell system we have no sound (or define actual pin if you have buzzer)

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
//[Hex Configuration]
//=============================================================================

// Leg dimensions - MEASURE YOUR HEXAPOD AND UPDATE THESE!
// All measurements in millimeters
#define cXXCoxaLength     29    
#define cXXFemurLength    85
#define cXXTibiaLength    125

//  Right Rear (RR) leg
#define cRRCoxaLength     cXXCoxaLength     
#define cRRFemurLength    cXXFemurLength
#define cRRTibiaLength    cXXTibiaLength

//  Right middle (RM) leg
#define cRMCoxaLength     cXXCoxaLength     
#define cRMFemurLength    cXXFemurLength
#define cRMTibiaLength    cXXTibiaLength

//  Rigth front (RF) leg
#define cRFCoxaLength     cXXCoxaLength     
#define cRFFemurLength    cXXFemurLength
#define cRFTibiaLength    cXXTibiaLength
  
//  Left Rear (LR) leg
#define cLRCoxaLength     cXXCoxaLength     
#define cLRFemurLength    cXXFemurLength
#define cLRTibiaLength    cXXTibiaLength

//  Left middle (LM) leg
#define cLMCoxaLength     cXXCoxaLength     
#define cLMFemurLength    cXXFemurLength
#define cLMTibiaLength    cXXTibiaLength

//  Left front (LF) leg
#define cLFCoxaLength     cXXCoxaLength     
#define cLFFemurLength    cXXFemurLength
#define cLFTibiaLength    cXXTibiaLength
//=============================================================================
// Body Dimensions
//=============================================================================
#define cRRCoxaAngle1   -600        //  Default Coxa setup angle, decimals = 1
#define cRMCoxaAngle1    0          //  Default Coxa setup angle, decimals = 1
#define cRFCoxaAngle1    600        //  Default Coxa setup angle, decimals = 1
#define cLRCoxaAngle1    -600       //  Default Coxa setup angle, decimals = 1
#define cLMCoxaAngle1    0          //  Default Coxa setup angle, decimals = 1
#define cLFCoxaAngle1    600        //  Default Coxa setup angle, decimals = 1

#define cRROffsetX  -39     //  Distance X from center of the body to the Right Rear coxa
#define cRROffsetZ  75      //  Distance Z from center of the body to the Right Rear coxa
#define cRMOffsetX  -64     //  Distance X from center of the body to the Right Middle coxa
#define cRMOffsetZ  0       //  Distance Z from center of the body to the Right Middle coxa
#define cRFOffsetX  -39     //  Distance X from center of the body to the Right Front coxa
#define cRFOffsetZ  -75     //  Distance Z from center of the body to the Right Front coxa

#define cLROffsetX  39      //  Distance X from center of the body to the Left Rear coxa
#define cLROffsetZ  75      //  Distance Z from center of the body to the Left Rear coxa
#define cLMOffsetX  64      //  Distance X from center of the body to the Left Middle coxa
#define cLMOffsetZ  0       //  Distance Z from center of the body to the Left Middle coxa
#define cLFOffsetX  39      //  Distance X from center of the body to the Left Front coxa
#define cLFOffsetZ  -75     //  Distance Z from center of the body to the Left Front coxa

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
#define MAX_BODY_Y      100    // Maximum body height

#define cRRInitPosX     cHexInitXZCos      // Right Rear
#define cRRInitPosY     cHexInitY
#define cRRInitPosZ     -cHexInitXZSin

#define cRMInitPosX     cHexInitXZ         // Right Middle
#define cRMInitPosY     cHexInitY
#define cRMInitPosZ     0

#define cRFInitPosX     cHexInitXZCos      // Right Front
#define cRFInitPosY     cHexInitY
#define cRFInitPosZ     cHexInitXZSin

#define cLRInitPosX     cHexInitXZCos      // Left Rear
#define cLRInitPosY     cHexInitY
#define cLRInitPosZ     -cHexInitXZSin

#define cLMInitPosX     cHexInitXZ         // Left Middle
#define cLMInitPosY     cHexInitY
#define cLMInitPosZ     0

#define cLFInitPosX     cHexInitXZCos      // Left Front
#define cLFInitPosY     cHexInitY
#define cLFInitPosZ     cHexInitXZSin

//=============================================================================
//[SERVO PULSE WIDTHS]
// Servo pulses in microseconds (typically 500-2500)
// These define the physical limits of your servos
// Adjust based on your specific servo model and mechanical constraints
//=============================================================================
// Universal Min/Max (if all servos use same range)
//#define CSERVOMIN       500
//#define CSERVOMAX       2500

// Individual Servo Ranges (optional - uncomment and adjust if needed)
// Use these if specific servos have different physical limits
// Right Rear leg
/*
#define cRRCoxaMin1     500
#define cRRCoxaMax1     2500
#define cRRFemurMin1    500
#define cRRFemurMax1    2500
#define cRRTibiaMin1    500
#define cRRTibiaMax1    2500
*/

// Repeat for other legs as needed...

//=============================================================================
// Debug Options
//=============================================================================
#ifdef OPT_TERMINAL_MONITOR
// Allow terminal monitor to output extra debug information
// #define DEBUG_IOPINS
#endif

#endif // HEX_CFG_H