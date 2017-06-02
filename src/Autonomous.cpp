// Copyright (c) 2011-2017 FRC Team 3512. All Rights Reserved.

#include <Timer.h>

#include "Robot.hpp"

void Robot::Autonomous() {
    while (IsEnabled() && IsAutonomous()) {
        Wait(0.01);
    }
}
