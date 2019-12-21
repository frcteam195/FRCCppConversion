#pragma once

#include <vector>
#include <initializer_list>

#include "utils/Subsystem.h"
#include "utils/Looper/Loop.h"
#include "utils/Looper/Looper.h"
#include "utils/TimeoutTimer.h"



class SubsystemManager : public ILooper {
public:
    static std::shared_ptr<SubsystemManager> GetInstance();

    SubsystemManager();

    bool CheckSystemsPassDiagnostics();

    void Register(Loop& loop) override;

    void RegisterEnabledLoops(Looper & enabledLooper);

    void RegisterDisabledLoops(Looper & disabledLooper);

private:
    static std::shared_ptr<SubsystemManager> mInstance;
    static std::vector<Subsystem*> mAllSubsystems;
    static std::vector<Loop*> mLoops;
    static std::vector<Reportable*> mLooperReports;

    friend class EnabledLoop;
    class EnabledLoop : public Loop {
    public:
        EnabledLoop()
        : mCriticalCheckTimeout(0.250) {

        };

        void OnFirstStart(double timestamp) override {
            for (Loop* loop : mLoops) {
                loop->OnFirstStart(timestamp);
            }
		};

        void OnStart(double timestamp) override {
            for (Loop* loop : mLoops) {
                loop->OnStart(timestamp);
            }
        };

        void OnLoop(double timestamp) override {
            for(Subsystem* subsystem : mAllSubsystems) {
                subsystem->ReadPeriodicInputs();
            }

            for (Loop* loop : mLoops) {
                loop->OnLoop(timestamp);
            }

            for(Subsystem* subsystem : mAllSubsystems) {
                subsystem->WritePeriodicOutputs();
            }

			if (mCriticalCheckTimeout.IsTimedOut()) {
                for(Subsystem* subsystem : mAllSubsystems) {
                    subsystem->IsSystemFaulted();
                }
				mCriticalCheckTimeout.Reset();
			}

			// if (Constants.LOGGING_ENABLED) {
			// 	generateReport();
			// 	DataReporter.reportOSCData(boundOSCMesage);
			// }
        };

        void OnStop(double timestamp) override {
            for (Loop* loop : mLoops) {
                loop->OnStop(timestamp);
            }
        };

        std::string GetName() override {
            return "SubsystemManagerEnabledLoop";
        };
    private:
        TimeoutTimer mCriticalCheckTimeout;
    };

    friend class DisabledLoop;
    class DisabledLoop : public Loop {
    public:
        DisabledLoop()
        : mCriticalCheckTimeout(0.250) {

        };

        void OnFirstStart(double timestamp) override {};

        void OnStart(double timestamp) override {};

        void OnLoop(double timestamp) override {
            for(Subsystem* subsystem : mAllSubsystems) {
                subsystem->ReadPeriodicInputs();
            }

            for(Subsystem* subsystem : mAllSubsystems) {
                subsystem->WritePeriodicOutputs();
            }

			if (mCriticalCheckTimeout.IsTimedOut()) {
                for(Subsystem* subsystem : mAllSubsystems) {
                    subsystem->IsSystemFaulted();
                }
				mCriticalCheckTimeout.Reset();
			}

			// if (Constants.LOGGING_ENABLED) {
			// 	generateReport();
			// 	DataReporter.reportOSCData(boundOSCMesage);
			// }
        };

        void OnStop(double timestamp) override {};

        std::string GetName() override {
            return "SubsystemManagerDisabledLoop";
        };
    private:
        TimeoutTimer mCriticalCheckTimeout;
    };

    EnabledLoop eLoop;
    DisabledLoop dLoop;
};
