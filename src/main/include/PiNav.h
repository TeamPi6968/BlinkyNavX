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
    double GetAngle(); //from accelerometer?
    double GetCompassHeading(); //from compas
    double GetFusedHeading(); // from compass and accelerometer
    void Reset();
    void UpdateSmartdashboardVeriables()
    void DriveStraightInit();
    void DriveStraightPeriodic(DifferentialDrive *drivetrain, Joystick *stick);

    // PID value drive straight
    double drivepower = 0.5;
    double kp = 0.06;

private:
    AHRS *ahrs;
    NetworkTable *table;
    LiveWindow *lw;
};
