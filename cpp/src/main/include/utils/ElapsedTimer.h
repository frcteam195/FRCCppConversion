#pragma once

#include "frc/Timer.h"

class ElapsedTimer {
public:
    ElapsedTimer() {};
    void Start() {
        startTime = frc::Timer::GetFPGATimestamp();
    }
    double HasElapsed() {
        return frc::Timer::GetFPGATimestamp() - startTime;
    }
private:
    double startTime;
};