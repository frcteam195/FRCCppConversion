#pragma once

#include "Reportable.hpp"
#include "CriticalSystemStatus.hpp"
#include "DiagnosableSubsystem.hpp"
#include "Looper/ILooper.hpp"

class Subsystem : public Reportable, public CriticalSystemStatus, public DiagnosableSubsystem {
public:
    void readPeriodicInputs() {};
    void writePeriodicOutputs() {};
    void zeroSensors() {};

    void registerEnabledLoops(ILooper & enabledLooper) {};

    virtual void stop() = 0;
};
