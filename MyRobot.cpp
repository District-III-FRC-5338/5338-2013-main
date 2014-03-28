#include <WPILib.h>
#include <Utility.h>
#include <Relay.h>  
/**
 * Code for Team 5338 RoboLoCos robotics
 */

//Defines to allow easy changing of ports
//Defines for each controller
#define LEFTJ 1
#define RIGHTJ 2
#define FUNCJ 3

//Joystick Buttons
#define BALLCHARGE 4
#define BALLLAUNCH 1
#define PICKUPPUSH 5
#define PICKUPPULL 3
#define ALTLAUNCH 8
#define SPINBALL 2
#define TURBO 1
#define STRAIGHT 1
#define CCLIMIT 2
#define TOGGLEAUTO 11
#define OVERRIDE 12

//Defines for each motor
#define DRIVEMOTORL 1
#define DRIVEMOTORR 2
#define BALLMOTOR 6
#define CCMOTOR 7

//Pneumatic defines
#define COMP_RELAY 1 // The compressor's spike relay (plugged into the relay)
#define COMP_SWITCH 1 // The compressor's pressure switch input (plugged into ground and input)
#define PICKUPARM 2 // The port the dual solenoid for the compressor it plugged into
class RobotDemo: public SimpleRobot {
    RobotDrive myRobot; // robot drive system
    Joystick left, right, func; // only joystick
    Victor ballMotor, ccMotor;
    Relay pickupArm;
    Compressor compress;
    DigitalInput ccLimit, compressSwitch; // limit switches for the Choo Choo
    bool autoRecharge;
  public:
    // These Methods can be accesed by other code

    //The constructor for the class, it is run before any other code
    //it uses an initializer list to initalize variables used by this class

    RobotDemo() :
          myRobot(DRIVEMOTORL, DRIVEMOTORR), // init drive system with both motors
          left(LEFTJ), // init joysticks, left drive,
          right(RIGHTJ),// right drive,
          func(FUNCJ), // other functions
          ballMotor(BALLMOTOR),
          ccMotor(CCMOTOR), // Motor used to bring in the ball fire it
          pickupArm(PICKUPARM),
          compress(COMP_SWITCH, COMP_RELAY), // The compressor 
          ccLimit(CCLIMIT), 
          compressSwitch(COMP_SWITCH) { // limit switches
      compress.Start();
      myRobot.SetExpiration(0.1);
      
    }
    
    // This code runs during autonomous
    // It does nothing right now

    void Autonomous() {
      //We haven't programmed autonomous yet
      //Quick Autonomous code :D 
      //Lets just move forward... 
      /*
      myRobot.TankDrive(.5, .5);
      Wait(.5);
      myRobot.TankDrive(0.0, 0.0); //Stop it after three seconds 
      if (compress.Enabled() && compressSwitch.Get())
        compress.Stop();
      myRobot.SetSafetyEnabled(false);
    */ /*
      float forwardtime = 0;
      float settime = 0; 
      ccMotor.Set(0.5);
      Wait(settime);
      ccMotor.Set(0.0);
      myRobot.TankDrive(.5,.5); //Move Forwards
      pickupArm.Set(Relay::kForward);
      ballMotor.Set(0.8);
      Wait(forwardtime);
      myRobot.TankDrive(0.0,0.0);
      ballMotor.Set(0.0);
      ccMotor.Set(0.9);
      Wait(1); 
      ccMotor.Set(0.0);
      *//*
      myRobot.TankDrive(.5,.5); 
      Wait(2);
      myRobot.TankDrive(0.0,0,0); 
      
      
  */ 
      /*pickupArm.Set(Relay::kForward); 
      while(!ccLimit.Get()){
        ccMotor.Set(.25); 
      }
      ccMotor.Set(0.0);
      ballMotor.Set(.5); 
      Wait(2); 
      ballMotor.Set(0.0); 
      myRobot.TankDrive(-.5,-.5); 
      Wait(2); 
      myRobot.TankDrive(0.0,0.0); 
      ccMotor.Set(.25); 
      Wait(1); 
      */
      myRobot.TankDrive(-.5,-.5);
      Wait(3);
      myRobot.TankDrive(0.0,0.0); 
      
      
      
      
      /*int state = 0;
      Timer timer;
      timer.Start()
      
      while (IsAutonomous())
      {
        switch (state)
        {
        case 0:
          
          if (timer.HasPeriodPassed(2.0))
            state = 1;
        case 1:
          ballMotor.Set(0)
          state = 2;
          break;
        }
        
        Wait(0.04);
      }*/
      
    }
    
    // This code runs during the tele-operated period
    // Runs the motors with tank steering
    // Also runs the ball pickup motor when the tigger is pressed

    void OperatorControl() {
      
      myRobot.SetSafetyEnabled(false);
      int loopcount = 0;
      float scaleFactor; // Factor to scale the joystick values by
      float leftpow, rightpow; // Power for the left and right motors

      while (IsOperatorControl()) {
        SetRIOUserLED(((loopcount++) % 2)); //This is just to turn on the cRIO LED
        /* Launch Codes,  activated yet */
       /* if (func.GetRawButton(BALLLAUNCH)){
          ccMotor.Set(.75); // ACTUALLY THE PICKUP MOTOR
        }
        else if (func.GetRawButton(ALTLAUNCH)){
          ccMotor.Set(.9);
        
        } else {
          ccMotor.Set(0.0);
        }
        else if (ccLimitA.Get() || ccLimitB.Get()){
        }
          ccMotor.Set(0.0); 
        } else{
          ccMotor.Set(.75);
        }*/ 
      
        if (func.GetRawButton(BALLCHARGE) && ! ccLimit.Get()){
            ccMotor.Set(.75); 
        } else if (func.GetRawButton(BALLLAUNCH)){
            ccMotor.Set(0.75); 
        } else {
            ccMotor.Set(0.0); 
        }
        //Control the compressor automatically to maintain pressure. 
        if (!(compressSwitch.Get() && !(compress.Enabled()))) {
          compress.Start();
        } else if (compressSwitch.Get() && compress.Enabled()) {
          compress.Stop();
        }

        if (left.GetRawButton(TURBO) && !func.GetRawButton(OVERRIDE)) // if the left trigger is held
          scaleFactor = 1; // TURBO MODE
        else if (func.GetRawButton(OVERRIDE))
          scaleFactor = 0; 
        else
          scaleFactor = 0.5; // else let us drive precisely
         
        //set the power for the to the Y-axes of the Joystick multiplied by the scale factor
        leftpow = left.GetY() * scaleFactor;
        rightpow = right.GetY() * scaleFactor;
        
        if (right.GetRawButton(STRAIGHT))
          leftpow = rightpow; // If right trigger is held, let us drive straight
        if(!func.GetRawButton(OVERRIDE))
          myRobot.TankDrive(leftpow, rightpow); // drive tank style
        else
          myRobot.TankDrive(0.0,0.0);
        // safety override for secondary driver
        if (func.GetRawButton(OVERRIDE)) // if button 5 on the control joystick is pressed
          myRobot.TankDrive(0.0, 0.0); // stop the motors
        
        if (func.GetRawButton(SPINBALL)) // if the trigger on the function joystick is pressed
          ballMotor.Set(0.75); // run the ball pickup motor
        else if (func.GetRawButton(ALTLAUNCH))
          ballMotor.Set(-0.75);
        else
          ballMotor.Set(0.0); // else don't run the motor

        /* This code is for when we add the feeder to the robot
         * However it is not ready yet so I have disabled it. */
        if (func.GetRawButton(PICKUPPUSH)) { // if button 2 is pressed
          pickupArm.Set(Relay::kForward);
        } else if (func.GetRawButton(PICKUPPULL)) { // else if button 3 is pressed
          pickupArm.Set(Relay::kReverse);
        } else {
          // don't mo ve feeder
        }
        
        Wait(0.005); // wait for a motor update time
      }
    }
    
    /**
     * Runs during test mode
     */
    void Test() {
      
    }
};

START_ROBOT_CLASS(RobotDemo);
