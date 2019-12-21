#include "SubsystemManager.h"

std::shared_ptr<SubsystemManager> SubsystemManager::mInstance;
std::vector<Subsystem*> SubsystemManager::mAllSubsystems;
std::vector<Loop*> SubsystemManager::mLoops;
std::vector<Reportable*> SubsystemManager::mLooperReports;

std::shared_ptr<SubsystemManager> SubsystemManager::GetInstance() {
    //std::initializer_list<Subsystem> subsystemList
    if(!mInstance) {
        mInstance = std::make_shared<SubsystemManager>();
    }
    // for(auto elem : subsystemList) {
    //     mAllSubsystems.push_back(elem);
    // }

    return mInstance;
}

SubsystemManager::SubsystemManager() {}

bool SubsystemManager::CheckSystemsPassDiagnostics() {
    bool retVal = true;
    for (Subsystem* subsystem : mAllSubsystems) {
        retVal &= subsystem->RunDiagnostics();
    }
    return retVal;
}

void SubsystemManager::Register(Loop& loop) {
    mLoops.push_back(&loop);
}

void SubsystemManager::RegisterEnabledLoops(Looper& enabledLooper) {
    for(Subsystem* subsystem : mAllSubsystems) {
        subsystem->RegisterEnabledLoops(*this);
    }
    enabledLooper.Register(eLoop);
    mLooperReports.push_back(&enabledLooper);
}

void SubsystemManager::RegisterDisabledLoops(Looper& disabledLooper) {
    disabledLooper.Register(dLoop);
    mLooperReports.push_back(&disabledLooper);
}
