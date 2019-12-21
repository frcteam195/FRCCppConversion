#include "SubsystemManager.hpp"

SubsystemManager* SubsystemManager::mInstance = nullptr;
std::vector<Subsystem*> SubsystemManager::mAllSubsystems;
std::vector<Loop*> SubsystemManager::mLoops;
std::vector<Reportable*> SubsystemManager::mLooperReports;

SubsystemManager* SubsystemManager::getInstance(std::initializer_list<Subsystem*> subsystemList) {
    if(!mInstance) {
        mInstance = new SubsystemManager();
    }
    for(Subsystem* elem : subsystemList) {
        mAllSubsystems.push_back(elem);
    }

    return mInstance;
}

SubsystemManager::SubsystemManager() {}

bool SubsystemManager::checkSystemsPassDiagnostics() {
    bool retVal = true;
    for (Subsystem* subsystem : mAllSubsystems) {
        retVal &= subsystem->runDiagnostics();
    }
    return retVal;
}

void SubsystemManager::registerLoop(Loop& loop) {
    mLoops.push_back(&loop);
}

void SubsystemManager::registerEnabledLoops(Looper& enabledLooper) {
    for(Subsystem* subsystem : mAllSubsystems) {
        subsystem->registerEnabledLoops(*this);
    }
    enabledLooper.registerLoop(eLoop);
    mLooperReports.push_back(&enabledLooper);
}

void SubsystemManager::registerDisabledLoops(Looper& disabledLooper) {
    disabledLooper.registerLoop(dLoop);
    mLooperReports.push_back(&disabledLooper);
}
