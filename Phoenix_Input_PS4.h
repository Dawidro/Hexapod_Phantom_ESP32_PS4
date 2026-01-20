//====================================================================
//Project Lynxmotion Phoenix
//Description: Phoenix, control file for ESP32 with PS4 controller
//Software version: V2.0
//Date: January 2025
//Programmer: [Your Name] (Based on KurtE's Phoenix_Input_PS2)
//
//Hardware setup: PS4 Controller via ESP32 Bluetooth
// Using PS4-esp32 library from https://github.com/aed3/PS4-esp32
//
//NEW IN V1.0
//- Initial Release for PS4 Controller
//
//Walk method 1:
//- Left Stick: Walk/Strafe
//- Right Stick: Rotate
//
//PS4 CONTROLS:
//[Common Controls]
//- Options (Start): Turn on/off the bot
//- L1: Toggle Shift mode
//- L2: Toggle Rotate mode
//- Circle: Toggle Single leg mode
//- Square: Toggle Balance mode
//- Triangle: Move body to 35 mm from the ground (walk pos) and back to the ground
//- D-Pad up: Body up 10 mm
//- D-Pad down: Body down 10 mm
//- D-Pad left: Decrease speed with 50mS
//- D-Pad right: Increase speed with 50mS
//
//[Walk Controls]
//- Left Stick (Walk mode): (Walk mode)
//- Left Stick X: Strafe
//- Left Stick Y: Forward/Backward
//- Right Stick X: Rotate
//
//[Shift Controls]
//- Left Stick (Shift mode):
//- Left Stick X: Shift body X
//- Left Stick Y: Shift body Z
//- Right Stick X: Shift body Y (height)
//- Right Stick Y: Body rotate Y
//
//[Rotate Controls]
//- Right Stick X: Body rotate X
//- Right Stick Y: Body rotate Y
//- Right Stick Z: Body rotate Z
//
//[Single Leg Controls]
//- Cross/Triangle: Select leg
//- Right Stick: Single leg X/Z Position
//- R2/L2: Single leg Y Position (height)
//
//====================================================================

#ifndef PHOENIX_INPUT_PS4_H
#define PHOENIX_INPUT_PS4_H

#if ARDUINO>99
#include <Arduino.h> // Arduino 1.0
#else
#include <Wprogram.h> // Arduino 0022
#endif

#include <PS4Controller.h>

//[CONSTANTS]
#define WALKMODE          0
#define TRANSLATEMODE     1
#define ROTATEMODE        2
#define SINGLELEGMODE     3
#define GPPLAYERMODE      4

#define cTravelDeadZone   4  //The deadzone for the analog input from the remote

#ifndef MAX_BODY_Y
#define MAX_BODY_Y 100
#endif

//=============================================================================
// Global - Local to this file only...
//=============================================================================

// Define an instance of the Input Controller...
InputController  g_InputController;       // Our Input controller 

static short      g_BodyYOffset; 
static short      g_BodyYShift;
static byte       ControlMode;
static bool       DoubleHeightOn;
static bool       DoubleTravelOn;

// PS4 specific variables
static boolean    g_fPS4Connected = false;

// Button states for edge detection
static boolean    g_buttonsPrev[16];

// Analog values
static byte       g_lx, g_ly, g_rx, g_ry;
static byte       g_l2Val, g_r2Val;

// Speed control
static short      g_sGPSMController = 32767;  // What GPSM value have we calculated

// Forward function references
extern void PS2TurnRobotOff(void);

//=============================================================================
// Helper Functions
//=============================================================================

//-----------------------------------------------------------------------------
// ButtonPressed: Check if button was just pressed (rising edge)
//-----------------------------------------------------------------------------
boolean ButtonPressed(byte button) {
  boolean current = false;
  
  switch(button) {
    case 0: current = PS4.data.button.cross; break;
    case 1: current = PS4.data.button.circle; break;
    case 2: current = PS4.data.button.square; break;
    case 3: current = PS4.data.button.triangle; break;
    case 4: current = PS4.data.button.l1; break;
    case 5: current = PS4.data.button.r1; break;
    case 6: current = PS4.data.button.l2; break;
    case 7: current = PS4.data.button.r2; break;
    case 8: current = PS4.data.button.options; break;
    case 9: current = PS4.data.button.share; break;
    case 10: current = PS4.data.button.up; break;
    case 11: current = PS4.data.button.down; break;
    case 12: current = PS4.data.button.left; break;
    case 13: current = PS4.data.button.right; break;
    case 14: current = PS4.data.button.ps; break;
    case 15: current = PS4.data.button.touchpad; break;
  }
  
  boolean pressed = current && !g_buttonsPrev[button];
  g_buttonsPrev[button] = current;
  return pressed;
}

//-----------------------------------------------------------------------------
// ButtonHeld: Check if button is currently held
//-----------------------------------------------------------------------------
boolean ButtonHeld(byte button) {
  switch(button) {
    case 0: return PS4.data.button.cross;
    case 1: return PS4.data.button.circle;
    case 2: return PS4.data.button.square;
    case 3: return PS4.data.button.triangle;
    case 4: return PS4.data.button.l1;
    case 5: return PS4.data.button.r1;
    case 6: return PS4.data.button.l2;
    case 7: return PS4.data.button.r2;
    case 8: return PS4.data.button.options;
    case 10: return PS4.data.button.up;
    case 11: return PS4.data.button.down;
    case 12: return PS4.data.button.left;
    case 13: return PS4.data.button.right;
  }
  return false;
}

//-----------------------------------------------------------------------------
// GetAnalog: Read analog value with proper scaling
//-----------------------------------------------------------------------------
byte GetAnalog(byte value) {
  // PS4 analog sticks are -128 to 127, convert to 0-255
  return (byte)(value + 128);
}

//=============================================================================
// InputController::Init
//=============================================================================
void InputController::Init(void) {
  g_InControlState.SpeedControl = 100;  // Default speed
  
  // Initialize local variables
  g_BodyYOffset = 0;
  g_BodyYShift = 0;
  ControlMode = WALKMODE;
  DoubleHeightOn = false;
  DoubleTravelOn = false;
  g_fPS4Connected = false;
  
  // Initialize button states
  for(int i = 0; i < 16; i++) {
    g_buttonsPrev[i] = false;
  }
  
  g_lx = g_ly = g_rx = g_ry = 128;
  g_l2Val = g_r2Val = 0;
  
  // Initialize PS4 controller
  PS4.begin();
  
  DBGSerial.println("PS4 Controller Input Initialized");
  DBGSerial.println("Press PS button to connect controller");
  
  delay(100);
}

//=============================================================================
// InputController::ControlInput
//=============================================================================
void InputController::ControlInput(void) {
  // Check if PS4 controller is connected
  g_fPS4Connected = PS4.isConnected();
  
  if(!g_fPS4Connected) {
    // Controller disconnected
    if(g_InControlState.fRobotOn) {
      PS4TurnRobotOff();
#ifdef DBGSerial      
      DBGSerial.println("PS4 Controller disconnected - Robot OFF");
#endif      
    }
    return;
  }
  
  // Read analog values
  g_lx = GetAnalog(PS4.data.analog.stick.lx);
  g_ly = GetAnalog(PS4.data.analog.stick.ly);
  g_rx = GetAnalog(PS4.data.analog.stick.rx);
  g_ry = GetAnalog(PS4.data.analog.stick.ry);
  g_l2Val = PS4.data.analog.button.l2;
  g_r2Val = PS4.data.analog.button.r2;
  
  //==================================================================
  // [OPTIONS BUTTON] - Turn on/off robot
  //==================================================================
  if(ButtonPressed(8)) {  // Options button
    if(g_InControlState.fRobotOn) {
      PS4TurnRobotOff();
    } else {
      // Turn on
      g_InControlState.fRobotOn = true;
      
      PS4.setRumble(200, 200);
      delay(100);
      PS4.setRumble(0, 0);
      
#ifdef DBGSerial      
      DBGSerial.println("Robot ON");
#endif      
    }
  }
  
  // Only process other inputs if robot is on
  if(!g_InControlState.fRobotOn) {
    return;
  }
  
  //==================================================================
  // [CIRCLE] - Toggle Single Leg mode
  //==================================================================
  if(ButtonPressed(1)) {
    MSound(1, 50, 2000);
    if(ControlMode != SINGLELEGMODE) {
      ControlMode = SINGLELEGMODE;
      g_InControlState.SelectedLeg = 0;
    } else {
      ControlMode = WALKMODE;
    }
  }
  
  //==================================================================
  // [SQUARE] - Toggle Balance mode
  //==================================================================
  if(ButtonPressed(2)) {
    g_InControlState.BalanceMode = !g_InControlState.BalanceMode;
    if(g_InControlState.BalanceMode) {
      MSound(1, 250, 1500);
    } else {
      MSound(2, 100, 2000, 50, 4000);
    }
  }
  
  //==================================================================
  // [TRIANGLE] - Toggle between walk height and ground
  //==================================================================
  if(ButtonPressed(3)) {
    if(!DoubleHeightOn) {
      g_BodyYOffset = 35;
      DoubleHeightOn = true;
    } else {
      g_BodyYOffset = 0;
      DoubleHeightOn = false;
    }
  }
  
  //==================================================================
  // [L1] - Toggle Shift mode
  //==================================================================
  if(ButtonPressed(4)) {
    MSound(1, 50, 2000);
    if(ControlMode != TRANSLATEMODE) {
      ControlMode = TRANSLATEMODE;
    } else {
      ControlMode = WALKMODE;
    }
  }
  
  //==================================================================
  // [L2] - Toggle Rotate mode
  //==================================================================
  if(ButtonPressed(6)) {
    MSound(1, 50, 2000);
    if(ControlMode != ROTATEMODE) {
      ControlMode = ROTATEMODE;
    } else {
      ControlMode = WALKMODE;
    }
  }
  
  //==================================================================
  // [D-PAD UP] - Body up
  //==================================================================
  if(ButtonHeld(10)) {
    g_BodyYOffset = min(g_BodyYOffset + 1, MAX_BODY_Y);
  }
  
  //==================================================================
  // [D-PAD DOWN] - Body down
  //==================================================================
  if(ButtonHeld(11)) {
    g_BodyYOffset = max(g_BodyYOffset - 1, 0);
  }
  
  //==================================================================
  // [D-PAD LEFT] - Decrease speed
  //==================================================================
  if(ButtonPressed(12)) {
    if(g_InControlState.SpeedControl > 0) {
      g_InControlState.SpeedControl = g_InControlState.SpeedControl - 50;
      MSound(1, 50, 2000);
    }
  }
  
  //==================================================================
  // [D-PAD RIGHT] - Increase speed
  //==================================================================
  if(ButtonPressed(13)) {
    if(g_InControlState.SpeedControl < 2000) {
      g_InControlState.SpeedControl = g_InControlState.SpeedControl + 50;
      MSound(1, 50, 2000);
    }
  }
  
  //==================================================================
  // [R1] - Toggle Double travel speed
  //==================================================================
  if(ButtonPressed(5)) {
    DoubleTravelOn = !DoubleTravelOn;
    if(DoubleTravelOn) {
      MSound(1, 50, 2000);
    }
  }
  
  //==================================================================
  // [R2] + [L1] - Gait select
  //==================================================================
  if(ButtonHeld(7) && ButtonHeld(4)) {
    // Cycle through gaits
    if(abs(g_InControlState.TravelLength.x) < cTravelDeadZone && 
       abs(g_InControlState.TravelLength.z) < cTravelDeadZone &&
       abs(g_InControlState.TravelLength.y*2) < cTravelDeadZone) {
      
      g_InControlState.GaitType = g_InControlState.GaitType + 1;
      if(g_InControlState.GaitType < NUM_GAITS) {
        MSound(1, 50, 2000);
      } else {
        MSound(2, 50, 2000, 50, 2250);
        g_InControlState.GaitType = 0;
      }
      g_InControlState.GaitStep = 0;
    }
  }
  
  //==================================================================
  // Single leg mode - select leg
  //==================================================================
  if(ControlMode == SINGLELEGMODE) {
    if(ButtonPressed(0)) {  // Cross - next leg
      if(g_InControlState.SelectedLeg < (CNT_LEGS-1)) {
        g_InControlState.SelectedLeg++;
      }
    }
    if(ButtonPressed(3)) {  // Triangle - previous leg
      if(g_InControlState.SelectedLeg > 0) {
        g_InControlState.SelectedLeg--;
      }
    }
  }
  
  //==================================================================
  // Process Analog Inputs
  //==================================================================
  
  // Calculate InputTimeDelay for gait speed adjustment
  g_InControlState.InputTimeDelay = 128 - max(max(abs(g_lx - 128), abs(g_ly - 128)), abs(g_rx - 128));
  
  // Different control modes
  if(ControlMode == WALKMODE) {
    // Walking mode
    // Left stick Y: Forward/Backward
    g_InControlState.TravelLength.z = (g_ly - 128);  // Invert Y
    
    // Left stick X: Strafe left/right
    g_InControlState.TravelLength.x = -(g_lx - 128);
    
    // Right stick X: Rotation
    g_InControlState.TravelLength.y = -(g_rx - 128) / 4;
    
    // Double travel speed if R1 pressed
    if(DoubleTravelOn) {
      g_InControlState.TravelLength.x = g_InControlState.TravelLength.x * 2;
      g_InControlState.TravelLength.z = g_InControlState.TravelLength.z * 2;
    }
  }
  else if(ControlMode == TRANSLATEMODE) {
    // Body translation mode
    g_InControlState.BodyPosX = (g_lx - 128) / 2;
    g_InControlState.BodyPosZ = -(g_ly - 128) / 3;
    g_InControlState.BodyRotY = (g_rx - 128) * 2;
    g_BodyYShift = (g_ry - 128) / 2;
  }
  else if(ControlMode == ROTATEMODE) {
    // Body rotation mode
    g_InControlState.BodyRotX = (g_ry - 128);
    g_InControlState.BodyRotZ = (g_lx - 128);
    g_InControlState.BodyRotY = (g_rx - 128) * 2;
  }
  else if(ControlMode == SINGLELEGMODE) {
    // Single leg control
    g_InControlState.SLLeg.x = (g_lx - 128) / 2;
    g_InControlState.SLLeg.z = -(g_ly - 128) / 2;
    g_InControlState.SLLeg.y = ((g_r2Val - g_l2Val) / 2);
  }
  
  // Commit our body offset
  g_InControlState.BodyPosY = g_BodyYOffset + g_BodyYShift;
  
  // Hold previous positions
  g_InControlState.lx = g_lx;
  g_InControlState.ly = g_ly;
}

//=============================================================================
// InputController::AllowControllerInterrupts
//=============================================================================
void InputController::AllowControllerInterrupts(boolean fAllow) {
  // Not needed for PS4-esp32 library (no interrupt-based processing)
}

//=============================================================================
// Terminal Monitor Support
//=============================================================================
#ifdef OPT_TERMINAL_MONITOR_IC
void InputController::ShowTerminalCommandList(void) {
  DBGSerial.println(F("PS4 Controller Commands:"));
  DBGSerial.println(F("  B - Show battery level"));
  DBGSerial.println(F("  S - Show controller status"));
}

boolean InputController::ProcessTerminalCommand(byte *psz, byte bLen) {
  if((bLen == 1) && ((*psz == 'b') || (*psz == 'B'))) {
    // Show battery level
    if(g_fPS4Connected) {
      DBGSerial.print(F("Battery: "));
      DBGSerial.println(PS4.data.status.battery);
    } else {
      DBGSerial.println(F("Controller not connected"));
    }
    return true;
  }
  
  if((bLen == 1) && ((*psz == 's') || (*psz == 'S'))) {
    // Show status
    DBGSerial.print(F("Connected: "));
    DBGSerial.println(g_fPS4Connected ? "YES" : "NO");
    if(g_fPS4Connected) {
      DBGSerial.print(F("LX: "));
      DBGSerial.print(g_lx);
      DBGSerial.print(F(" LY: "));
      DBGSerial.print(g_ly);
      DBGSerial.print(F(" RX: "));
      DBGSerial.print(g_rx);
      DBGSerial.print(F(" RY: "));
      DBGSerial.println(g_ry);
    }
    return true;
  }
  
  return false;
}
#endif

//=============================================================================
// PS4TurnRobotOff - code used couple of places so save a little room...
//=============================================================================
void PS4TurnRobotOff(void)
{
  //Turn off
  g_InControlState.BodyPosX = 0;
  g_InControlState.BodyPosY = 0;
  g_InControlState.BodyPosZ = 0;
  g_InControlState.BodyRotX = 0;
  g_InControlState.BodyRotY = 0;
  g_InControlState.BodyRotZ = 0;
  g_InControlState.TravelLength.x = 0;
  g_InControlState.TravelLength.z = 0;
  g_InControlState.TravelLength.y = 0;
  g_BodyYOffset = 0;
  g_BodyYShift = 0;
  g_InControlState.SelectedLeg = 255;
  g_InControlState.fRobotOn = false;
  
  // Give haptic feedback
  PS4.setRumble(100, 100);
  delay(200);
  PS4.setRumble(0, 0);
}

#endif // PHOENIX_INPUT_PS4_H