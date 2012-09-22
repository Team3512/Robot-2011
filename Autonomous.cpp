//=============================================================================
//File Name: Autonomous.cpp
//Description: Holds autonomous code for robot
//Author: Tyler Veness
//Date/Version: $Id: Autonomous.cpp,v 1.2 2012/04/17 23:49:03 tav Exp $
//=============================================================================

#include "OurRobot.h"

void OurRobot::Autonomous() {
	mainCompressor.Start();

	while ( IsEnabled() && IsAutonomous() )
		Wait( 0.01 );
}
