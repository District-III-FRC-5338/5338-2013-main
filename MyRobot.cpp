#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot {
	RobotDrive myRobot; // robot drive system
	Joystick left, right, func; //only joystick
	Victor ballMotor;

public:
	RobotDemo():
		myRobot(1, 2),	// these must be initialized in the same order
		left(1),		// as they are declared above.
		right(2),
		func(2),
		ballMotor(7) 
	{
		myRobot.SetExpiration(0.1);
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous() {
		/*myRobot.SetSafetyEnabled(false);
		myRobot.Drive(-0.5, 0.0); 	// drive forwards half speed
		Wait(2.0); 				//    for 2 seconds
		myRobot.Drive(0.0, 0.0); 	// stop robot*/
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl() {
		myRobot.SetSafetyEnabled(true);
		while (IsOperatorControl()) {
			myRobot.TankDrive(left.GetY(),right.GetY()); // drive with arcade style (use right stick)
			if (func.GetRawButton(1)) {
				ballMotor.Set(0.5);
				//printf("Function: %f",func.GetZ());
			} else {
				ballMotor.Set(0.0);
			}
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

