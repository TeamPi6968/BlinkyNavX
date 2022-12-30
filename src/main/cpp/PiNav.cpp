#include "PiNav.h"
#include <iostream>

PiNav::PiNav()
{
    // try connecting to the navx
    try
    {
        /***********************************************************************
         * navX-MXP:
         * - Communication via RoboRIO MXP (SPI, I2C) and USB.
         * - See http://navx-mxp.kauailabs.com/guidance/selecting-an-interface.
         *
         * navX-Micro:
         * - Communication via I2C (RoboRIO MXP or Onboard) and USB.
         * - See http://navx-micro.kauailabs.com/guidance/selecting-an-interface.
         *
         * VMX-pi:
         * - Communication via USB.
         * - See https://vmx-pi.kauailabs.com/installation/roborio-installation/
         *
         * Multiple navX-model devices on a single robot are supported.
         ************************************************************************/
        ahrs = new AHRS(SPI::Port::kMXP);
    }
    catch (std::exception &ex)
    {
        std::string what_string = ex.what();
        std::string err_msg("Error instantiating navX MXP:  " + what_string);
        const char *p_err_msg = err_msg.c_str();
        std::cout << p_err_msg << "\n";
    }
}

double PiNav::GetAngle()
{
    try
    {
        return ahrs->GetAngle();
    }
    catch (std::exception &ex)
    {
        std::string err_string = "Error communicating with Drive System:  ";
        err_string += ex.what();
        std::cout << err_string.c_str() << "\n";
    }
}

void PiNav::Reset()
{
    ahrs->ZeroYaw();
}

void PiNav::DriveStraightInit()
{
    Reset();
}

void PiNav::DriveStraightPeriodic(DifferentialDrive *drivetrain, Joystick *stick)
{
    double error = ahrs->GetAngle();
    double turnpower = kp * error;
    drivetrain->ArcadeDrive(-drivepower, turnpower);

    bool reset_yaw_button_pressed = stick->GetRawButton(1);
    if (reset_yaw_button_pressed)
    {
        Reset();
    }
}