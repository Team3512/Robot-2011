//=============================================================================
//File Name: OperatorControl.cpp
//Description: Handles driver controls for robot
//Author: Tyler Veness
//Date/Version: $Id: OperatorControl.cpp,v 1.2 2012/04/17 23:49:03 tav Exp $
//=============================================================================

#include "OurRobot.h"
#include <Timer.h>
#include <math.h>

#define XBOX

float ScaleZ( Joystick& stick) {
	return floorf( 500.f * ( 1.f - stick.GetZ() ) / 2.f ) / 500.f; //CONSTANT^-1 is step value (now 1/500)
}

void OurRobot::OperatorControl() {
	mainCompressor.Start();
	Timer trayTime;
	trayTime.Start();

	while ( IsEnabled() && IsOperatorControl() ) {

#ifndef XBOX
		/* ===== Dual Controller ===== */
		mainDrive.ArcadeDrive( ScaleZ( driveStick1 ) * driveStick1.GetY() , ScaleZ( driveStick2 ) * driveStick2.GetX() , false );

		// raises/lowers arm
		armMotorLeft.Set( -armStick.GetY() );
		armMotorRight.Set( armStick.GetY() );

		// opens/closes claw
		if ( armStick.GetTrigger() ) {
			claw.Set( !claw.Get() );

			while ( armStick.GetTrigger() )
				Wait( 0.01 );
		}

		// extends/retracts elbow joint
		if ( armStick.GetRawButton(2) ) {
			elbow.Set( !elbow.Get() );

			while ( armStick.GetRawButton(2) )
				Wait( 0.01 );
		}

		// deploys/resets minibot tray
		if ( armStick.GetRawButton(6) ) {
			tray.Set( !tray.Get() );
			trayTime.Reset();

			while ( armStick.GetRawButton(6) )
				Wait( 0.01 );
		}

		// minibot release/reset checks
		if ( tray.Get() ) { // if minibot tray is deployed
			if ( poleLimit.Get() && trayTime.Get() > 1.5 ) // if robot is contacting pole and time has passed since tray has been out
				pins.Set( true ); // release minibot
		}

		if ( tray.Get() && armStick.GetRawButton(11) ) // if tray is deployed and user wants to deploy minibot
			pins.Set( true );

		if ( !tray.Get() && pins.Get() ) // if tray is in and pins are in, reset them to out state
			pins.Set( false ); // false ; reset pins so they can hold minibot again
#else
		/* ===== X-Box Controller ===== */
		mainDrive.ArcadeDrive( driveStick1.GetY() , driveStick1.GetX() , false );

		// raises/lowers arm
		if ( driveStick1.GetRawButton( 1 ) ) { // arm down
			armMotorLeft.Set( 0.4 );
			armMotorRight.Set( -0.4 );
		}
		else if ( driveStick1.GetRawButton( 4 ) ) { // arm up
			armMotorLeft.Set( -0.75 );
			armMotorRight.Set( 0.75 );
		}
		else {
			armMotorLeft.Set( 0 );
			armMotorRight.Set( 0 );
		}

		// opens/closes claw
		if ( driveStick1.GetZ() < -0.5 ) {
			claw.Set( !claw.Get() );

			while ( driveStick1.GetZ() < -0.5 )
				Wait( 0.01 );
		}

		// extends/retracts elbow joint
		if ( driveStick1.GetRawButton(6) ) {
			elbow.Set( !elbow.Get() );

			while ( driveStick1.GetRawButton(6) )
				Wait( 0.01 );
		}

		// deploys/resets minibot tray
		if ( driveStick1.GetZ() > 0.5 ) {
			tray.Set( !tray.Get() );
			trayTime.Reset();

			while ( driveStick1.GetZ() > 0.5 )
				Wait( 0.01 );
		}

		// minibot release/reset checks
		if ( tray.Get() ) { // if minibot tray is deployed
			if ( poleLimit.Get() && trayTime.Get() > 1.f ) // if robot is contacting pole and time has passed since tray has been out
				pins.Set( true ); // release minibot
		}

		if ( tray.Get() && driveStick1.GetRawButton(5) ) // if tray is deployed and user wants to deploy minibot
			pins.Set( true );

		if ( !tray.Get() && pins.Get() ) // if tray is in and pins are in, reset them to out state
			pins.Set( false ); // false ; reset pins so they can hold minibot again
#endif // !defined(XBOX)
	}
}
