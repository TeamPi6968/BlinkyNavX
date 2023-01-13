#pragma once

// Pivision Made by Nick

// libraries
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>


using namespace frc;

// for networktables
using namespace nt;

class PiVision
{
    // Variables and methods go here
public:
    PiVision();
    void Update();

    bool HasTarget;
    double TurnCmd;
    double DriveCmd;

private:
};
