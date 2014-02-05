#include "WPILib.h"

/**
 * Code for Team 5338 District III robotics
 */ 

//Defines to allow easy changing of ports
//Defines for each controller
#define LEFTJ 1
#define RIGHTJ 2
#define FUNCJ 3

//Joystick Buttons
#define BALLCHARGE 6
#define BALLLAUNCH 7

#define CCLIMITA 1
#define CCLIMITB 2

//Defines for each motor
#define DRIVEMOTORL 1
#define DRIVEMOTORR 2
#define BALLMOTOR 7
#define CCMOTOR 6

//Pneumatic defines
#define COMP_RELAY 5 // The compressor's spike relay
#define COMP_SWITCH 1 // The compressor's pressure switch
#define PICKUPARM 2

class RobotDemo : public SimpleRobot {

  RobotDrive myRobot; // robot drive system
  Joystick left, right, func; // only joystick
  Victor ballMotor, ccMotor;
  Relay pickupArm;
  Compressor compress;
  DigitalInput ccLimitA,ccLimitB; // limit switches for the Choo Choo
  
public: // These Methods can be accesed by other code
  
  //The constructor for the class, it is run before any other code
  //it uses an initializer list to initalize variables used by this class
  
  RobotDemo(): 
    myRobot(DRIVEMOTORL, DRIVEMOTORR),  // init drive system with both motors
    left(LEFTJ),  // init joysticks, left drive,
    right(RIGHTJ),// right drive,
    func(FUNCJ),  // other functions
    ballMotor(BALLMOTOR), ccMotor(CCMOTOR), // Motor used to bring in the ball fire it
    pickupArm(PICKUPARM), // Pnuematic relay for the pickup armature
    compress(COMP_SWITCH, COMP_RELAY), // The compressor 
    ccLimitA(CCLIMITA),ccLimitB(CCLIMITB) { // limit switches
    compress.Start();
    myRobot.SetExpiration(0.1);
  }
  
  // This code runs during autonomous
  // It does nothing right now
  
  void Autonomous() {
    //We haven't programmed autonomous yet
    
    myRobot.SetSafetyEnabled(false);
  }
  
  // This code runs during the tele-operated period
  // Runs the motors with tank steering
  // Also runs the ball pickup motor when the tigger is pressed
  
  void OperatorControl() {
    
    myRobot.SetSafetyEnabled(false);
    
    float scaleFactor; // Factor to scale the joystick values by
    float leftpow,rightpow; // Power for the left and right motors
    
    while (IsOperatorControl()) {
      
      /* Launch Codes, not activated yet
      if (func.GetRawButton(BALLCHARGE) && !(ccLimitA.Get()||ccLimitB.Get())) {
        ccMotor.Set(0.75);
      } else if (func.GetRawButton(BALLLAUNCH) && (ccLimitA.Get()||ccLimitB.Get())) {
        ccMotor.Set(0.75);
      } else {
        ccMotor.Set(0);
      }
      */
      
      if (left.GetRawButton(1)) // if the left trigger is held
        scaleFactor = 1.0; // TURBO MODE
      else
        scaleFactor = 0.5; // else let us drive precisely
      
      //set the power for the to the Y-axes of the Joystick multiplied by the scale factor
      leftpow = left.GetY()*scaleFactor;
      rightpow = right.GetY()*scaleFactor;
      
      if (right.GetRawButton(1))
        leftpow = rightpow; // If right trigger is held, let us drive straight
      
      myRobot.TankDrive(leftpow,rightpow); // drive tank style
      
      // safety override for secondary driver
      if (func.GetRawButton(5)) // if button 5 on the control joystick is pressed
        myRobot.TankDrive(0.0,0.0); // stop the motors
      if (func.GetRawButton(1)) // if the trigger on the function joystick is pressed
        ballMotor.Set(0.5); // run the ball pickup motor
      else
        ballMotor.Set(0.0); // else don't run the motor
      
      /* This code is for when we add the feeder to the robot
       * However it is not ready yet so I have disabled it.
      if (func.GetRawButton(2)) { // if button 2 is pressed
        pickupArm
      } else if (func.GetRawButton(3)) { // else if button 3 is pressed
        // move ball feeder down
      } else {
        // don't move feeder
      } */
      
      Wait(0.005);        // wait for a motor update time
    }
  }
  
  /**
   * Runs during test mode
   */
  void Test() {

  }
};

START_ROBOT_CLASS(RobotDemo);
