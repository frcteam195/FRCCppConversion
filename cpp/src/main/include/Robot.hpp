/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>
#include <frc/livewindow/LiveWindow.h>
#include <iostream>
#include <frc/TimedRobot.h>

#include "SubsystemManager.hpp"
#include "utils/Looper/Looper.hpp"

#include "subsystems/Drive.hpp"

class Robot : public frc::TimedRobot {
public:
    void RobotInit() override;
    void RobotPeriodic() override;  
    void AutonomousInit() override;
    void AutonomousPeriodic() override;
    void TeleopInit() override;
    void TeleopPeriodic() override;
    void TestPeriodic() override;
    void DisabledInit() override;
    void DisabledPeriodic() override;

private:
    SubsystemManager* mSubsystemManager;
    Looper mEnabledLooper;
    Looper mDisabledLooper;
};
