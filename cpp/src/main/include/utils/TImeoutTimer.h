#include <mutex>
#include <math>
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
        mtx.lock();
        this->firstRun = firstRun;
        mtx.unlock();
    };
};