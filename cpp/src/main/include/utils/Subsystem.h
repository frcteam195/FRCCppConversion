#include "Reportable.h"
#include "CriticalSystemStatus.h"
#include "DiagnosableSubsystem.h"
#include "ILooper.h"

class Subsystem : public Reportable, public CriticalSystemStatus, public DiagnosableSubsystem {
public:
    void ReadPeriodicInputs() {};
    void WritePeriodicOutputs() {};
    void ZeroSensors() {};

    void RegisterEnabledLoops(ILooper enabledLooper) {};

    virtual void Stop() = 0;
};