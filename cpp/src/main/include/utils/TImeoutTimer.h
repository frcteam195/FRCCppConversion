#pragma once

#include <mutex>
#include <math.h>
#include "ElapsedTimer.h"

class TimeoutTimer {
public:
    TimeoutTimer(double timeout) {
        this->timeout = timeout;
        SetFirstRun(true);
    };

    bool IsTimedOut() {
        if (firstRun) {
			eTimer.Start();
			SetFirstRun(false);
		}
		return eTimer.HasElapsed() > timeout;
    };

    void Reset() {
        SetFirstRun(true);
    };
    
    double GetTimeLeft() {
		return std::max(timeout - eTimer.HasElapsed(), 0.0);
	};

private:
    double timeout;
    bool firstRun;
    ElapsedTimer eTimer;

    std::mutex mtx; 

    void SetFirstRun(bool firstRun) {
        std::scoped_lock<std::mutex> lock(mtx);
        this->firstRun = firstRun;
    };
};