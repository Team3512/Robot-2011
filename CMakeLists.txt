cmake_minimum_required(VERSION 2.8)

project(Thermopylae)

include_directories( "${WIND_BASE}/target/h/WPILib" )

set(SRC
    OurRobot.cpp
    OperatorControl.cpp
    Autonomous.cpp
    Disabled.cpp
)

add_executable(FRC_UserProgram.out ${SRC})
