// Copyright (c) FRC Team 3512, Spartatroniks 2011-2017. All Rights Reserved.

#include <Timer.h>

#include "Robot.hpp"

void Robot::Autonomous() {
    while (IsEnabled() && IsAutonomous()) {
        Wait(0.01);
    }
}
