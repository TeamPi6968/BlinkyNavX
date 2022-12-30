#pragma once

// navx include
#include "AHRS.h"

// other libraries
#include <frc/drive/DifferentialDrive.h>
#include <frc/Joystick.h.>

using namespace frc;

class PiNav
{
    // Variables and methods go here
public:
    PiNav();
    double GetAngle();
    void Reset();
    void DriveStraightInit();
    void DriveStraightPeriodic(DifferentialDrive *drivetrain, Joystick *stick);

    // PID value drive straight
    double drivepower = 0.5;
    double kp = 0.06;

private:
    AHRS *ahrs;
};
