//====================================================================
//Project Lynxmotion Phoenix
//Description: Phoenix software for ESP32 with SSC-32 and PS4 Controller
//    This version is specific for ESP32 using the SSC-32 servo
//    controller and PS4 controller via Bluetooth
//
//Programmer: [Your Name]
//            Based on Phoenix code by Jeroen Janssen (aka Xan)
//            and Kurt Eckhardt (KurtE)
//
//Date: January 2025
//
//KNOWN BUGS:
//    - None so far...
//
//====================================================================
//
// IMPORTANT: BEFORE UPLOADING
// 1. Install PS4Controller library from: https://github.com/aed3/PS4-esp32
// 2. Set your PS4 controller MAC address in Hex_Cfg.h
// 3. Configure your hexapod dimensions in Hex_Cfg.h
// 4. Calibrate servo offsets in Hex_Cfg.h
//
//====================================================================

//=============================================================================
// Define CONFIG Options
//=============================================================================
// You can enable/disable features here or in Hex_Cfg.h

// #define DEBUG           // Enable debug output
// #define DEBUG_IOPINS    // Enable I/O pin debug

//=============================================================================
// Include Files
//=============================================================================

#include "Hex_Cfg.h"             // Hardware configuration
#include <PS4Controller.h>        // PS4 Controller library

//=============================================================================
// Include Phoenix Core and Driver Files
//=============================================================================
#include "Phoenix.h"              // Main Phoenix code (includes setup/loop)
#include "Phoenix_Input_PS4.h"    // PS4 Controller input handler
#include "Phoenix_Driver_SSC32.h" // SSC-32 servo driver

//=============================================================================
// OPTIONAL Hook Functions
// These are only called if you enable them in Hex_Cfg.h with #define
//=============================================================================

//=============================================================================
// SketchSetup - OPTIONAL
// Only called if OPT_SKETCHSETUP is defined in Hex_Cfg.h
// Called from Phoenix setup() before main initialization
//=============================================================================
#ifdef OPT_SKETCHSETUP
void SketchSetup(void) {
#ifdef DBGSerial
  DBGSerial.begin(DBG_SERIAL_BAUD);
  delay(500);
  
  DBGSerial.println(F("===================================="));
  DBGSerial.println(F("Phoenix Hexapod Robot - ESP32"));
  DBGSerial.println(F("SSC-32 Servo Controller"));
  DBGSerial.println(F("PS4 Controller Input"));
  DBGSerial.println(F("===================================="));
  DBGSerial.println();
  
  DBGSerial.println(F("Initializing PS4 Controller..."));
  #ifdef PS4_MAC_ADDRESS
    DBGSerial.print(F("MAC Address: "));
    DBGSerial.println(PS4_MAC_ADDRESS);
  #endif
#endif

  // Initialize PS4 Controller
#ifdef PS4_MAC_ADDRESS
  PS4.begin(PS4_MAC_ADDRESS);
#else
  PS4.begin();  // Use default pairing
#endif

#ifdef DBGSerial
  DBGSerial.println(F("Press PS button to connect controller"));
  DBGSerial.println();
#endif

  // Small startup beep
  MSound(3, 50, 2000, 50, 2500, 50, 3000);
}
#endif

//=============================================================================
// BackgroundProcess - OPTIONAL
// Only called if OPT_BACKGROUND_PROCESS is defined in Hex_Cfg.h
// Called frequently during servo moves - keep it fast!
//=============================================================================
#ifdef OPT_BACKGROUND_PROCESS
void BackgroundProcess(void) {
  // Can add battery monitoring, LED updates, etc. here
  // Example: Simple battery voltage monitoring
  // static unsigned long lastBatteryCheck = 0;
  // if(millis() - lastBatteryCheck > 5000) {
  //   checkBatteryVoltage();
  //   lastBatteryCheck = millis();
  // }
}
#endif

//=============================================================================
// GPPlayer - OPTIONAL
// Only called if OPT_GPPLAYER is defined in Hex_Cfg.h
// Used for playing sequences
//=============================================================================
#ifdef OPT_GPPLAYER
void GPPlayer(void) {
  // GP Player mode not implemented yet
  // This would play pre-recorded movement sequences
}

// CheckVoltage - OPTIONAL voltage monitoring for OPT_GPPLAYER
word CheckVoltage(void) {
  // Implement battery voltage monitoring here if you have a voltage divider
  // connected to an ADC pin
  
  // Example:
  // int rawValue = analogRead(VOLTAGE_PIN);
  // return map(rawValue, 0, 4095, 0, 1650); // Adjust for your voltage divider
  
  return 1200;  // Return dummy value for now (12.00V)
}
#endif

//=============================================================================
// Terminal Monitor Support Functions
// These are handled by the main Phoenix code, not called directly
// The InputController class already has these defined
//=============================================================================
#ifdef OPT_TERMINAL_MONITOR

// The terminal monitor is built into Phoenix_Code.h
// It automatically calls g_InputController.ShowTerminalCommandList()
// and g_InputController.ProcessTerminalCommand()
// which we already defined in Phoenix_Input_PS4.h

#endif // OPT_TERMINAL_MONITOR