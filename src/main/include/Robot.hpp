// Copyright (c) 2011-2020 FRC Team 3512. All Rights Reserved.

#pragma once

#include <frc/DigitalInput.h>
#include <frc/Joystick.h>
#include <frc/Solenoid.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/TimedRobot.h>
#include <frc/Victor.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc2/Timer.h>

class Robot : public frc::TimedRobot {
public:
    void TeleopInit() override;
    void TeleopPeriodic() override;

private:
    frc::Victor flMotor{3};
    frc::Victor rlMotor{1};
    frc::Victor frMotor{2};
    frc::Victor rrMotor{4};

    frc::SpeedControllerGroup leftGearbox{flMotor, rlMotor};
    frc::SpeedControllerGroup rightGearbox{frMotor, rrMotor};

    frc::DifferentialDrive mainDrive{leftGearbox, rightGearbox};

    frc::Joystick driveStick1{0};
    frc::Joystick driveStick2{1};
    frc::Joystick armStick{2};

    frc::Victor armMotorLeft{5};
    frc::Victor armMotorRight{8};

    frc::Solenoid claw{6};
    frc::Solenoid elbow{3};
    frc::Solenoid tray{4};
    frc::Solenoid pins{7};

    frc::DigitalInput poleLimit{2};

    frc2::Timer trayTimer;
};
