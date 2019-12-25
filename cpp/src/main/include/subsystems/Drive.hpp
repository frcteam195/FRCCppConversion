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

    void registerEnabledLoops(ILooper & enabledLooper) override;
    
private:
    Drive();
    static DataReporter* logReporter;

    friend class DriveLoop;
    class DriveLoop : public Loop {
        void onFirstStart(double timestamp) override;
        void onStart(double timestamp) override;
        void onStop(double timestamp) override;
        void onLoop(double timestamp) override;
        std::string getName() override;
    };

    friend class PeriodicIO;
    class PeriodicIO {
    public:
        PeriodicIO();

        NetworkDouble left_position_rotations;
        NetworkDouble right_position_rotations;
    };

    PeriodicIO mPeriodicIO;
    DriveLoop mDriveLoop;
};
