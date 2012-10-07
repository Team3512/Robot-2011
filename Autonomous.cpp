//=============================================================================
//File Name: Autonomous.cpp
//Description: Holds autonomous code for robot
//Author: FRC Team 3512, Spartatroniks
//=============================================================================

#include "OurRobot.hpp"

void OurRobot::Autonomous() {
	mainCompressor.Start();

	while ( IsEnabled() && IsAutonomous() )
		Wait( 0.01 );
}
