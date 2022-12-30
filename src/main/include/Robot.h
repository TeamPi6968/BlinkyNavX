// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

//motors
#include <ctre/Phoenix.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc/drive/DifferentialDrive.h>

#include <frc/Joystick.h.>
#include <frc/DriverStation.h>

#include <frc\Errors.h>

#include "PiNav.h"

using namespace frc;

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;
  void SimulationInit() override;
  void SimulationPeriodic() override;

 private:

  WPI_VictorSPX m_leftDrive{5};
  WPI_VictorSPX m_leftDrive2{2};
  WPI_VictorSPX m_rightDrive{3};
  WPI_VictorSPX m_rightDrive2{4};

  frc::PWMSparkMax m_leftIntake{1};
  frc::PWMSparkMax m_rightIntake{2};
  frc::PWMSparkMax m_Storage{0};

  DifferentialDrive m_robotDrive{m_leftDrive, m_rightDrive};

  const static int joystickChannel = 0;

  Joystick *stick;          // only joystick

  PiNav *pinav;
};
