//=============================================================================
//File Name: OurRobot.hpp
//Description: Holds declaration of OurRobot class
//Author: FRC Team 3512, Spartatroniks
//=============================================================================

#ifndef OUR_ROBOT_HPP
#define OUR_ROBOT_HPP

#include <SimpleRobot.h>
#include <Timer.h>

#include <Compressor.h>
#include <RobotDrive.h>
#include <Joystick.h>
#include <Victor.h>
#include <Solenoid.h>
#include <DigitalInput.h>

class OurRobot : public SimpleRobot {
	Compressor mainCompressor;

	RobotDrive mainDrive;

	Joystick driveStick1;
	Joystick driveStick2;
	Joystick armStick;

	Victor armMotorLeft;
	Victor armMotorRight;

	Solenoid claw;
	Solenoid elbow;
	Solenoid tray;
	Solenoid pins;

	DigitalInput poleLimit;

public:
	OurRobot() :
		mainCompressor( 4 , 4 ),

		mainDrive( 3 , 1 , 2 , 4 ),
		driveStick1( 1 ),
		driveStick2( 2 ),
		armStick( 3 ),

		armMotorLeft( 5 ),
		armMotorRight( 8 ),

		claw( 6 ),
		elbow( 3 ),
		tray(  4 ),
		pins( 7 ),

		poleLimit( 2 )
	{
	}

	void Autonomous();
	void OperatorControl();
	void Disabled();
};

#endif // OUR_ROBOT_HPP
