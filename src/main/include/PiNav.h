#pragma once


//NavX code explained
//Made by Nick
//Frc Team Pi


// navx include
#include "AHRS.h"

// other libraries
#include <frc/drive/DifferentialDrive.h>
#include <frc/Joystick.h.>

#include <frc/smartdashboard/SmartDashboard.h>

using namespace frc;

//for networktables
using namespace nt;

class PiNav
{
    // Variables and methods go here
public:
    PiNav();

    //gives the angle measured from the gyro. Can get bigger than 360 degrees
    double GetAngle(); 

    //Returns the current tilt-compensated compass heading value (in degrees, from 0 to 360) reported by the sensor.
    //Note that this value is sensed by a magnetometer, which can be affected by nearby magnetic fields (e.g., the magnetic fields generated by nearby motors).
    double GetCompassHeading(); //from compas

    //check the angle to see if the robot is standing level
    //can get used for the chargestation in the game of 2023
    double GetAngleYaw();

    //resets the heading
    void Reset();

    //sends all the values to the driver station dashboard
    void UpdateSmartdashboardVeriables();

    //2 functions to demonstartes autonomous driving straight
    void DriveStraightInit();
    void DriveStraightPeriodic(DifferentialDrive *drivetrain, Joystick *stick);


    // PID value drive straight
    double kp = 0.1;

private:
    AHRS *ahrs;
    // NetworkTable *table;
    // LiveWindow *lw;
};
