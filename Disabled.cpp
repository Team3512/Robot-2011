//=============================================================================
//File Name: Disabled.cpp
//Description: This function runs when robot is in disabled state
//Author: Tyler Veness
//Date/Version: $Id: Disabled.cpp,v 1.2 2012/04/17 23:49:03 tav Exp $
//=============================================================================

#include "OurRobot.h"

void OurRobot::Disabled() {
	mainCompressor.Stop();

	while ( IsDisabled() )
		Wait( 0.01 );
}
