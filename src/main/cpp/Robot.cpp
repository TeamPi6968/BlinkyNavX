// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <fmt/core.h>
#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit()
{

  // add controller
  stick = new Joystick(joystickChannel);

  // add pi nav x
  pinav = new PiNav();

  // Set motor direction
  m_leftDrive.SetInverted(false);
  m_leftDrive2.SetInverted(true);
  m_rightDrive.SetInverted(true);
  m_rightDrive2.SetInverted(false);
  m_leftIntake.SetInverted(true);
  m_rightIntake.SetInverted(false);
  m_Storage.SetInverted(false);

  // set breaking
  m_rightDrive.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);
  m_rightDrive2.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);
  m_leftDrive.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);
  m_leftDrive2.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);

  // create drivetrain
  m_leftDrive2.Follow(m_leftDrive);
  m_rightDrive2.Follow(m_rightDrive);
}

void Robot::RobotPeriodic() {
  pinav.UpdateSmartdashboardVeriables();
}

void Robot::AutonomousInit()
{
  pinav->DriveStraightInit();
}

void Robot::AutonomousPeriodic()
{
  pinav->DriveStraightPeriodic(&m_robotDrive, stick);
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic()
{
  m_robotDrive.ArcadeDrive(stick->GetY(), -stick->GetX());
  m_leftIntake.Set(stick->GetRawAxis(3));
  m_rightIntake.Set(stick->GetRawAxis(3));
  m_Storage.Set(stick->GetRawAxis(3));
}

void Robot::DisabledInit()
{
  m_rightDrive.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Coast);
  m_rightDrive2.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Coast);
  m_leftDrive.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Coast);
  m_leftDrive2.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Coast);
}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}

void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
