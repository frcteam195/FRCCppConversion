#pragma once

#include "ctre/Phoenix.h"
#include "utils/Subsystem.hpp"
#include "reporters/NetworkDataType.hpp"
#include "reporters/DataReporter.hpp"
#include "reporters/NetworkDataReporter.hpp"
#include "utils/Singleton.hpp"

using namespace ck::log;

class Drive : public Subsystem, public Singleton<Drive> {
    friend Singleton;
public:
    void stop() override;

    bool isSystemFaulted() override;

    bool runDiagnostics() override;

    
private:
    Drive();
    static DataReporter* logReporter;

    friend class PeriodicIO;
    class PeriodicIO {
    public:
        PeriodicIO();

        NetworkDouble left_position_rotations;
        NetworkDouble right_position_rotations;
    };

    PeriodicIO mPeriodicIO;
};
