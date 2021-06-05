#include "autonomous/AutoModeBase.hpp"
#include "frc/DriverStation.h"
#include "autonomous/AutoModeEndedException.hpp"

AutoModeBase::AutoModeBase() : threadRateControl() {}


void AutoModeBase::run() {
    mActive = true;

    try {
        routine();
    } catch (AutoModeEndedException e) {
        frc::DriverStation::ReportError("AUTO MODE DONE!!!! ENDED EARLY!!!!");
        return;
    }

    done();
}

void AutoModeBase::done() {
    //ConsoleReporter.report("Auto mode done");
}

void AutoModeBase::stop() {
    mActive = false;
}

bool AutoModeBase::isActive() {
    return mActive;
}

bool AutoModeBase::isActiveWithThrow() {
    if (!isActive()) {
        //throw AutoModeEndedException("Action ended early");
    }

    return isActive();
}

void AutoModeBase::runAction(Action &action) {
    isActiveWithThrow();
    threadRateControl.start(true);
    action.start();

    while (isActiveWithThrow() && !action.isFinished()) {
        action.update();
        threadRateControl.doRateControl((int)(mUpdateRate * 1000.0));
    }

    action.done();
}
