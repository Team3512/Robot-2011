// Copyright (c) 2011-2020 FRC Team 3512. All Rights Reserved.

#include "Robot.hpp"

#include <cmath>

double ScaleZ(frc::Joystick& stick) {
    return std::floor(500.0 * (1.0 - stick.GetZ()) / 2.0) /
           500.0;  // CONSTANT^-1 is step value (now 1/500)
}

void Robot::TeleopInit() { trayTimer.Start(); }

void Robot::TeleopPeriodic() {
    mainDrive.ArcadeDrive(ScaleZ(driveStick1) * driveStick1.GetY(),
                          ScaleZ(driveStick2) * driveStick2.GetX());

    // Raises/lowers arm
    armMotorLeft.Set(-armStick.GetY());
    armMotorRight.Set(armStick.GetY());

    // Opens/closes claw
    if (armStick.GetRawButtonPressed(1)) {
        claw.Set(!claw.Get());
    }

    // Extends/retracts elbow joint
    if (armStick.GetRawButtonPressed(2)) {
        elbow.Set(!elbow.Get());
    }

    // Deploys/resets minibot tray
    if (armStick.GetRawButtonPressed(6)) {
        tray.Set(!tray.Get());
        trayTimer.Reset();
    }

    // If tray is deployed and user wants to deploy minibot
    if (tray.Get() && driveStick1.GetRawButton(5)) {
        pins.Set(true);
    }

    // If minibot tray is deployed
    if (tray.Get() && poleLimit.Get() && trayTimer.Get() > 1_s) {
        // If robot is contacting pole and time has passed since tray
        // has been out, release minibot
        pins.Set(true);
    }

    // If tray is in and pins are in, reset them to out state
    if (!tray.Get() && pins.Get()) {
        // Reset pins so they can hold minibot again
        pins.Set(false);
    }
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
