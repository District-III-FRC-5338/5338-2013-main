#include "WPILib.h"

/**
 * Code for Team 5338 District III robotics
 */ 

//Defines to allow easy changing of ports
//Defines for each controller
#DEFINE LEFTJ 1
#DEFINE RIGHTJ 2
#DEFINE FUNCJ 2
//Defines for each motor
#DEFINE DRIVEMOTORL 1
#DEFINE DRIVEMOTORR 2
#DEFINE BALLMOTOR 7

class RobotDemo : public SimpleRobot {
	RobotDrive myRobot; // robot drive system
	Joystick left, right, func; // only joystick
	Victor ballMotor;
	
public: // These Methods can be accesed by other code
	
	//The constructor for the class, it is run before any other code
	//it uses an initializer list to initalize variables used by this class
	
	RobotDemo(): 
		myRobot(DRIVEMOTORL, DRIVEMOTORR),  // init drive system with both motors
		left(LEFTJ),  // init joysticks, left drive,
		right(RIGHTJ),// right drive,
		func(FUNCJ),  // other functions
		ballMotor(BALLMOTOR) { // Motor used to bring in the ball
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
		
		myRobot.SetSafetyEnabled(true);
		
		float scaleFactor; // Factor to scale the joystick values by
		float leftpow,rightpow; // Power for the left and right motors
		
		while (IsOperatorControl()) {
		  
		  if (left.GetRawButton(1)) // if the left trigger is held
		    scaleFactor = 0.5; // scale the speed by half, allows for precision movement
		  else
		    scaleFactor = 1.0; // else don't scale, allows for speed
		  
		  //set the power for the to the Y-axes of the Joystick multiplied by the scale factor
		  leftpow = left.getY()*scaleFactor;
		  rightpow = right.getY()*scaleFactor;
		  
			myRobot.TankDrive(leftpow,rightpow); // drive tank style
			
			if (func.GetRawButton(1)) // if the trigger on the function joystick is pressed
				ballMotor.Set(0.5); // run the ball pickup motor
			else
				ballMotor.Set(0.0); // else don't run the motor
			
			Wait(0.005);				// wait for a motor update time
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);
