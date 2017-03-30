// Copyright (c) FRC Team 3512, Spartatroniks 2011-2017. All Rights Reserved.

#include "Robot.hpp"

#include <cmath>

#include <Timer.h>

double ScaleZ(Joystick& stick) {
    return std::floor(500.0 * (1.0 - stick.GetZ()) / 2.0) /
           500.0;  // CONSTANT^-1 is step value (now 1/500)
}

void Robot::Disabled() {
    while (IsDisabled()) {
        Wait(0.01);
    }
}

void Robot::OperatorControl() {
    Timer trayTime;
    trayTime.Start();

    while (IsEnabled() && IsOperatorControl()) {
        mainDrive.ArcadeDrive(ScaleZ(driveStick1) * driveStick1.GetY(),
                              ScaleZ(driveStick2) * driveStick2.GetX());

        // Raises/lowers arm
        armMotorLeft.Set(-armStick.GetY());
        armMotorRight.Set(armStick.GetY());

        // Opens/closes claw
        if (armStick.GetTrigger()) {
            claw.Set(!claw.Get());

            while (armStick.GetTrigger()) {
                Wait(0.01);
            }
        }

        // Extends/retracts elbow joint
        if (armStick.GetRawButton(2)) {
            elbow.Set(!elbow.Get());

            while (armStick.GetRawButton(2)) {
                Wait(0.01);
            }
        }

        // Deploys/resets minibot tray
        if (armStick.GetRawButton(6)) {
            tray.Set(!tray.Get());
            trayTime.Reset();

            while (armStick.GetRawButton(6)) {
                Wait(0.01);
            }
        }

        // If tray is deployed and user wants to deploy minibot
        if (tray.Get() && driveStick1.GetRawButton(5)) {
            pins.Set(true);
        }

        // If minibot tray is deployed
        if (tray.Get() && poleLimit.Get() && trayTime.Get() > 1.0) {
            /* If robot is contacting pole and time has passed since tray
             * has been out, release minibot
             */
            pins.Set(true);
        }

        // If tray is in and pins are in, reset them to out state
        if (!tray.Get() && pins.Get()) {
            // Reset pins so they can hold minibot again
            pins.Set(false);
        }

        driveStick1Tracker.Update();
        driveStick2Tracker.Update();
        armStickTracker.Update();
    }
}

START_ROBOT_CLASS(Robot)
