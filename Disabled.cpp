//=============================================================================
//File Name: Disabled.cpp
//Description: This function runs when robot is in disabled state
//Author: FRC Team 3512, Spartatroniks
//=============================================================================

#include "OurRobot.hpp"

void OurRobot::Disabled() {
	mainCompressor.Stop();

	while ( IsDisabled() )
		Wait( 0.01 );
}
