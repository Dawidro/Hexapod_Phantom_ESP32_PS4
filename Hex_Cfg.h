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
// #define PS4_MAC_ADDRESS "1a:2b:3c:01:01:01"  // <-- CHANGE THIS TO YOUR PS4 CONTROLLER MAC

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

// Allow sketch to add custom setup code
// #define OPT_SKETCHSETUP      // If defined, calls SketchSetup() from your .ino

// Background Process - Allow background tasks during servo moves
// #define OPT_BACKGROUND_PROCESS  // If defined, calls BackgroundProcess()

// GP Player - Sequence playback support
// #define OPT_GPPLAYER         // Enable if you want to play sequences

//=============================================================================
//[Botboarduino Pin Numbers]
// ESP32 doesn't use the same pin mapping, but keeping for reference
//=============================================================================
// #define SOUND_PIN    0xFF   // Tell system we have no sound

//=============================================================================
//[SSC32 Pin Numbers]
//=============================================================================
#define cCoxaPin     pgm_read_byte(&cCoxaPin[LegIndex])
#define cFemurPin    pgm_read_byte(&cFemurPin[LegIndex])
#define cTibiaPin    pgm_read_byte(&cTibiaPin[LegIndex])

#ifdef c4DOF
#define cTarsPin     pgm_read_byte(&cTarsPin[LegIndex])
#endif

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
//[REMOTE]
//=============================================================================
#define WALKMODE          0
#define TRANSLATEMODE     1
#define ROTATEMODE        2
#define SINGLELEGMODE     3
#define GPPLAYERMODE      4

//=============================================================================
//[Hex Configuration]
//=============================================================================

// Leg dimensions - MEASURE YOUR HEXAPOD AND UPDATE THESE!
// All measurements in millimeters
#define cXXTibiaInv 0     // 0 = Normal, 1 = Inverted (depends on servo orientation)
#define cRRTibiaInv 0
#define cRMTibiaInv 0
#define cRFTibiaInv 0
#define cLRTibiaInv 0
#define cLMTibiaInv 0
#define cLFTibiaInv 0

#define cRRCoxaLength     29    // Right Rear leg
#define cRRFemurLength    76
#define cRRTibiaLength    106

#define cRMCoxaLength     29    // Right Middle leg
#define cRMFemurLength    76
#define cRMTibiaLength    106

#define cRFCoxaLength     29    // Right Front leg
#define cRFFemurLength    76
#define cRFTibiaLength    106

#define cLRCoxaLength     29    // Left Rear leg
#define cLRFemurLength    76
#define cLRTibiaLength    106

#define cLMCoxaLength     29    // Left Middle leg
#define cLMFemurLength    76
#define cLMTibiaLength    106

#define cLFCoxaLength     29    // Left Front leg
#define cLFFemurLength    76
#define cLFTibiaLength    106

//=============================================================================
// Body Dimensions
//=============================================================================
#define cRRCoxaAngle1   -450   // Default Coxa setup angle, decimals = 1
#define cRMCoxaAngle1    0     // 0 degrees = straight out
#define cRFCoxaAngle1    450   // 45 degrees forward
#define cLRCoxaAngle1   -450   // decimals = 1
#define cLMCoxaAngle1    0
#define cLFCoxaAngle1    450

#define cRROffsetX      -43    // Distance X from center of the body to the Right Rear coxa
#define cRROffsetZ      -82    // Distance Z from center of the body to the Right Rear coxa
#define cRMOffsetX      -63    // Distance X from center of the body to the Right Middle coxa
#define cRMOffsetZ      0      // Distance Z from center of the body to the Right Middle coxa
#define cRFOffsetX      -43    // Distance X from center of the body to the Right Front coxa
#define cRFOffsetZ      82     // Distance Z from center of the body to the Right Front coxa

#define cLROffsetX      43     // Distance X from center of the body to the Left Rear coxa
#define cLROffsetZ      -82    // Distance Z from center of the body to the Left Rear coxa
#define cLMOffsetX      63     // Distance X from center of the body to the Left Middle coxa
#define cLMOffsetZ      0      // Distance Z from center of the body to the Left Middle coxa
#define cLFOffsetX      43     // Distance X from center of the body to the Left Front coxa
#define cLFOffsetZ      82     // Distance Z from center of the body to the Left Front coxa

//=============================================================================
// Start Position of Legs
//=============================================================================
#define cHexInitXZ      105    // Default distance from center to foot in X/Z plane
#define cHexInitXZCos   74     // Default distance X - From center of body to foot (cos(45) * cHexInitXZ)
#define cHexInitXZSin   74     // Default distance Z - From center of body to foot (sin(45) * cHexInitXZ)
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
// Adjust these based on your servo range
//=============================================================================
// Universal Min/Max (if all servos use same range)
#define CSERVOMIN       500
#define CSERVOMAX       2500

// Individual Servo Ranges (if needed for fine-tuning)
// Right Rear leg
#define cRRCoxaMin1     500
#define cRRCoxaMax1     2500
#define cRRFemurMin1    500
#define cRRFemurMax1    2500
#define cRRTibiaMin1    500
#define cRRTibiaMax1    2500

// Right Middle leg
#define cRMCoxaMin1     500
#define cRMCoxaMax1     2500
#define cRMFemurMin1    500
#define cRMFemurMax1    2500
#define cRMTibiaMin1    500
#define cRMTibiaMax1    2500

// Right Front leg
#define cRFCoxaMin1     500
#define cRFCoxaMax1     2500
#define cRFFemurMin1    500
#define cRFFemurMax1    2500
#define cRFTibiaMin1    500
#define cRFTibiaMax1    2500

// Left Rear leg
#define cLRCoxaMin1     500
#define cLRCoxaMax1     2500
#define cLRFemurMin1    500
#define cLRFemurMax1    2500
#define cLRTibiaMin1    500
#define cLRTibiaMax1    2500

// Left Middle leg
#define cLMCoxaMin1     500
#define cLMCoxaMax1     2500
#define cLMFemurMin1    500
#define cLMFemurMax1    2500
#define cLMTibiaMin1    500
#define cLMTibiaMax1    2500

// Left Front leg
#define cLFCoxaMin1     500
#define cLFCoxaMax1     2500
#define cLFFemurMin1    500
#define cLFFemurMax1    2500
#define cLFTibiaMin1    500
#define cLFTibiaMax1    2500

//=============================================================================
//[SERVO OFFSETS]
// Servo offsets for calibration - adjust these to align your servos
// Positive values rotate clockwise, negative counter-clockwise
// Values are in microseconds added to the calculated pulse width
//=============================================================================
// Right Rear leg
#define cRRCoxaOffset    0
#define cRRFemurOffset   0
#define cRRTibiaOffset   0

// Right Middle leg
#define cRMCoxaOffset    0
#define cRMFemurOffset   0
#define cRMTibiaOffset   0

// Right Front leg
#define cRFCoxaOffset    0
#define cRFFemurOffset   0
#define cRFTibiaOffset   0

// Left Rear leg
#define cLRCoxaOffset    0
#define cLRFemurOffset   0
#define cLRTibiaOffset   0

// Left Middle leg
#define cLMCoxaOffset    0
#define cLMFemurOffset   0
#define cLMTibiaOffset   0

// Left Front leg
#define cLFCoxaOffset    0
#define cLFFemurOffset   0
#define cLFTibiaOffset   0

//=============================================================================
// Debug Options
//=============================================================================
#ifdef OPT_TERMINAL_MONITOR
// Allow terminal monitor to output extra debug information
// #define DEBUG_IOPINS
#endif

//=============================================================================
// Calculate some useful values
//=============================================================================
#define CNT_LEGS 6
#define CNT_SERVOS_PER_LEG 3
#define NUMSERVOS (CNT_LEGS * CNT_SERVOS_PER_LEG)

#endif // HEX_CFG_H