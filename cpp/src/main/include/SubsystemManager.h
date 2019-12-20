#include <vector>
#include <initializer_list>

#include "Subsystem.h"
#include "Loop.h"
#include "TImeoutTimer.h"

class SubsystemManager : public ILooper {
public:
    static std::shared_ptr<SubsystemManager> GetInstance(std::initializer_list<Subsystem> subsystemList) {
        if(!mInstance) {
            mInstance = std::make_shared<SubsystemManager>(new SubsystemManager());
        }
        for( auto elem : subsystemList )
        {
            mAllSubsystems.push_back(elem);
        }

        return mInstance;
    };

    bool CheckSystemsPassDiagnostics() {
		bool retVal = true;
        for (auto & subsystem : mAllSubsystems) {
            retVal &= subsystem.RunDiagnostics();
        }
		return retVal;
	};

    void Register(Loop loop) override {
        mLoops.push_back(loop);
    }

private:
    static std::shared_ptr<SubsystemManager> mInstance;
    static std::vector<Subsystem> mAllSubsystems;
    std::vector<Loop> mLoops;
    std::vector<Reportable> mLooperReports;

    TimeoutTimer mCriticalCheckTimeout;
    TimeoutTimer mLogDataTimeout;

    SubsystemManager()
        : mCriticalCheckTimeout(0.250)
        , mLogDataTimeout(0.250) {

    };
};