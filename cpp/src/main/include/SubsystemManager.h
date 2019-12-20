#pragma once

#include <vector>
#include <initializer_list>

#include "utils/Subsystem.h"
#include "utils/Looper/Loop.h"
#include "utils/Looper/Looper.h"
#include "utils/TimeoutTimer.h"

class SubsystemManager : public ILooper {
public:
    static std::shared_ptr<SubsystemManager> GetInstance() {
        //std::initializer_list<Subsystem> subsystemList
        if(!mInstance) {
            mInstance = std::make_shared<SubsystemManager>(new SubsystemManager());
        }
        // for(auto elem : subsystemList) {
        //     mAllSubsystems.push_back(elem);
        // }

        return mInstance;
    };

    bool CheckSystemsPassDiagnostics() {
		bool retVal = true;
        for (auto & subsystem : mAllSubsystems) {
            retVal &= subsystem.RunDiagnostics();
        }
		return retVal;
	};

    void Register(Loop & loop) override {
        mLoops.push_back(loop);
    };

    void RegisterEnabledLoops(Looper & enabledLooper) {
        for(auto subsystem : mAllSubsystems) {
            subsystem.RegisterEnabledLoops(*this);
        }
        //TODO: Check to make sure going out of scope here doesn't hurt us. Otherwise will need shared_ptr
        EnabledLoop eLoop;
		enabledLooper.Register(eLoop);
		mLooperReports.push_back(enabledLooper);
    };

    void RegisterDisabledLoops(Looper & disabledLooper) {
        //TODO: Check to make sure going out of scope here doesn't hurt us. Otherwise will need shared_ptr
        DisabledLoop dLoop;
		disabledLooper.Register(dLoop);
		mLooperReports.push_back(disabledLooper);
    };

private:
    static std::shared_ptr<SubsystemManager> mInstance;
    static std::vector<Subsystem> mAllSubsystems;
    static std::vector<Loop> mLoops;
    static std::vector<Reportable> mLooperReports;

    SubsystemManager() {};

    class EnabledLoop : public Loop {
    public:
        EnabledLoop()
        : mCriticalCheckTimeout(0.250) {

        };

        void OnFirstStart(double timestamp) override {
            for (auto & loop : mLoops) {
                loop.OnFirstStart(timestamp);
            }
		};

        void OnStart(double timestamp) override {
            for (auto & loop : mLoops) {
                loop.OnStart(timestamp);
            }
        };

        void OnLoop(double timestamp) override {
            for(auto subsystem : mAllSubsystems) {
                subsystem.ReadPeriodicInputs();
            }

            for (auto & loop : mLoops) {
                loop.OnLoop(timestamp);
            }

            for(auto subsystem : mAllSubsystems) {
                subsystem.WritePeriodicOutputs();
            }

			if (mCriticalCheckTimeout.IsTimedOut()) {
                for(auto subsystem : mAllSubsystems) {
                    subsystem.IsSystemFaulted();
                }
				mCriticalCheckTimeout.Reset();
			}

			// if (Constants.LOGGING_ENABLED) {
			// 	generateReport();
			// 	DataReporter.reportOSCData(boundOSCMesage);
			// }
        };

        void OnStop(double timestamp) override {
            for (auto & loop : mLoops) {
                loop.OnStop(timestamp);
            }
        };

        std::string GetName() override {
            return "SubsystemManagerEnabledLoop";
        };
    private:
        TimeoutTimer mCriticalCheckTimeout;
    };

    class DisabledLoop : public Loop {
    public:
        DisabledLoop()
        : mCriticalCheckTimeout(0.250) {

        };

        void OnFirstStart(double timestamp) override {};

        void OnStart(double timestamp) override {};

        void OnLoop(double timestamp) override {
            for(auto subsystem : mAllSubsystems) {
                subsystem.ReadPeriodicInputs();
            }

            for(auto subsystem : mAllSubsystems) {
                subsystem.WritePeriodicOutputs();
            }

			if (mCriticalCheckTimeout.IsTimedOut()) {
                for(auto subsystem : mAllSubsystems) {
                    subsystem.IsSystemFaulted();
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
};