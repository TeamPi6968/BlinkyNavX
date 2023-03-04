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

    // // add network tables to see the live data
    // table = NetworkTable::GetTable("NAVX");
    // lw = LiveWindow::GetInstance();

    // if (ahrs)
    // {
    //     LiveWindow::GetInstance()->AddSensor("IMU", "Gyro", ahrs);
    // }
}

double PiNav::GetAngle()
{
    // check if sensor is connected
    // if (!ahrs)
    //     return;

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
    return 0;
}

double PiNav::GetAngleYaw()
{
    try
    {
        return ahrs->GetYaw();
    }
    catch (std::exception &ex)
    {
        std::string err_string = "Error communicating with Drive System:  ";
        err_string += ex.what();
        std::cout << err_string.c_str() << "\n";
    }
    return 0;
}

double PiNav::GetCompassHeading()
{
    // check if sensor is connected
    // if (!ahrs)
    //     return;

    try
    {
        return ahrs->GetCompassHeading();
    }
    catch (std::exception &ex)
    {
        std::string err_string = "Error communicating with Drive System:  ";
        err_string += ex.what();
        std::cout << err_string.c_str() << "\n";
    }
    return 0;
}

void PiNav::Reset()
{
    // check if sensor is connected
    // if (!ahrs)
    //     return;

    ahrs->ZeroYaw();
}

void PiNav::DriveStraightInit()
{
    Reset();
}

void PiNav::DriveStraightPeriodic(DifferentialDrive *drivetrain, Joystick *stick)
{
    // // check if sensor is connected
    // if (!ahrs)
    //     return;

    double drivepower = stick->GetRawAxis(1);

    double error = ahrs->GetAngle();
    double turnpower = kp * error;
    drivetrain->ArcadeDrive(-drivepower, turnpower);

    bool reset_yaw_button_pressed = stick->GetRawButton(1);
    if (reset_yaw_button_pressed)
    {
        Reset();
    }
}

void PiNav::UpdateSmartdashboardVeriables()
{
    // SmartDashboard::PutBoolean("IMU_Connected", ahrs->IsConnected());
    // SmartDashboard::PutNumber("IMU_Yaw", ahrs->GetYaw());
    // SmartDashboard::PutNumber("IMU_Pitch", ahrs->GetPitch());
    // SmartDashboard::PutNumber("IMU_Roll", ahrs->GetRoll());
    // SmartDashboard::PutNumber("IMU_CompassHeading", ahrs->GetCompassHeading());
    // SmartDashboard::PutNumber("IMU_Update_Count", ahrs->GetUpdateCount());
    // SmartDashboard::PutNumber("IMU_Byte_Count", ahrs->GetByteCount());

    // /* These functions are compatible w/the WPI Gyro Class */
    // SmartDashboard::PutNumber("IMU_TotalYaw", ahrs->GetAngle());
    // SmartDashboard::PutNumber("IMU_YawRateDPS", ahrs->GetRate());

    // SmartDashboard::PutNumber("IMU_Accel_X", ahrs->GetWorldLinearAccelX());
    // SmartDashboard::PutNumber("IMU_Accel_Y", ahrs->GetWorldLinearAccelY());
    // SmartDashboard::PutBoolean("IMU_IsMoving", ahrs->IsMoving());
    // SmartDashboard::PutNumber("IMU_Temp_C", ahrs->GetTempC());
    // SmartDashboard::PutBoolean("IMU_IsCalibrating", ahrs->IsCalibrating());

    // SmartDashboard::PutNumber("Velocity_X", ahrs->GetVelocityX());
    // SmartDashboard::PutNumber("Velocity_Y", ahrs->GetVelocityY());
    // SmartDashboard::PutNumber("Displacement_X", ahrs->GetDisplacementX());
    // SmartDashboard::PutNumber("Displacement_Y", ahrs->GetDisplacementY());

    // /* Display Raw Gyro/Accelerometer/Magnetometer Values                       */
    // /* NOTE:  These values are not normally necessary, but are made available   */
    // /* for advanced users.  Before using this data, please consider whether     */
    // /* the processed data (see above) will suit your needs.                     */

    // SmartDashboard::PutNumber("RawGyro_X", ahrs->GetRawGyroX());
    // SmartDashboard::PutNumber("RawGyro_Y", ahrs->GetRawGyroY());
    // SmartDashboard::PutNumber("RawGyro_Z", ahrs->GetRawGyroZ());
    // SmartDashboard::PutNumber("RawAccel_X", ahrs->GetRawAccelX());
    // SmartDashboard::PutNumber("RawAccel_Y", ahrs->GetRawAccelY());
    // SmartDashboard::PutNumber("RawAccel_Z", ahrs->GetRawAccelZ());
    // SmartDashboard::PutNumber("RawMag_X", ahrs->GetRawMagX());
    // SmartDashboard::PutNumber("RawMag_Y", ahrs->GetRawMagY());
    // SmartDashboard::PutNumber("RawMag_Z", ahrs->GetRawMagZ());
    // SmartDashboard::PutNumber("IMU_Temp_C", ahrs->GetTempC());

    // /* Omnimount Yaw Axis Information                                           */
    // /* For more info, see http://navx-mxp.kauailabs.com/installation/omnimount  */
    // AHRS::BoardYawAxis yaw_axis = ahrs->GetBoardYawAxis();
    // SmartDashboard::PutString("YawAxisDirection", yaw_axis.up ? "Up" : "Down");
    // SmartDashboard::PutNumber("YawAxis", yaw_axis.board_axis);

    // /* Sensor Board Information                                                 */
    // SmartDashboard::PutString("FirmwareVersion", ahrs->GetFirmwareVersion());

    // /* Quaternion Data                                                          */
    // /* Quaternions are fascinating, and are the most compact representation of  */
    // /* orientation data.  All of the Yaw, Pitch and Roll Values can be derived  */
    // /* from the Quaternions.  If interested in motion processing, knowledge of  */
    // /* Quaternions is highly recommended.                                       */
    // SmartDashboard::PutNumber("QuaternionW", ahrs->GetQuaternionW());
    // SmartDashboard::PutNumber("QuaternionX", ahrs->GetQuaternionX());
    // SmartDashboard::PutNumber("QuaternionY", ahrs->GetQuaternionY());
    // SmartDashboard::PutNumber("QuaternionZ", ahrs->GetQuaternionZ());
}