// Copyright (c) FRC Team 3512, Spartatroniks 2011-2017. All Rights Reserved.

#pragma once

#include <Compressor.h>
#include <DigitalInput.h>
#include <Joystick.h>
#include <RobotDrive.h>
#include <SimpleRobot.h>
#include <Solenoid.h>
#include <Victor.h>

#include "ButtonTracker.hpp"

// If defined, uses Xbox controller instead of dual joysticks
#define XBOX

/**
 * Holds declaration of OurRobot class
 */
class Robot : public SimpleRobot {
public:
    void Disabled();
    void Autonomous();
    void OperatorControl();

private:
    Compressor mainCompressor{4, 4};

    RobotDrive mainDrive{3, 1, 2, 4};

    Joystick driveStick1{0};
    ButtonTracker driveStick1Tracker{0};

    Joystick driveStick2{1};
    ButtonTracker driveStick2Tracker{1};

    Joystick armStick{2};
    ButtonTracker armStickTracker{2};

    Victor armMotorLeft{5};
    Victor armMotorRight{8};

    Solenoid claw{6};
    Solenoid elbow{3};
    Solenoid tray{4};
    Solenoid pins{7};

    DigitalInput poleLimit{2};
};
