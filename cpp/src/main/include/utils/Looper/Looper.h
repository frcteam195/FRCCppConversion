#pragma once

#include <vector>
#include <mutex>
#include <chrono>

#include "frc/Notifier.h"
#include "frc/Timer.h"

#include "../Subsystem.h"
#include "Loop.h"
#include "../TimeoutTimer.h"
#include "../../Constants.h"

class Looper : public ILooper, public Reportable {
public:
    static constexpr units::second_t kPeriod = 0_s;

    Looper()
    : notifier_([this]() {
        std::scoped_lock<std::mutex> lock(mtx);
        if (isFirstRun) {
            //Any init code here
            isFirstRun = false;
        }

        if (running_) {
            double now = frc::Timer::GetFPGATimestamp();
            try {
                for (auto & loop : loops_) {
                    loop.OnLoop(now);
                }
            }
            catch (std::exception &ex) {
                //ConsoleReporter.report(ex);
            }
            dt_ = now - timestamp_;
            timestamp_ = now;
        }
    }) {
        isFirstRun = true;
        isFirstStart = true;
        running_ = false;
    };

    void Register(Loop & loop) override {
        std::scoped_lock<std::mutex> lock(mtx);
        loops_.push_back(loop);
    }

    void Start() {
        if (!running_) {
            {   //Aquire lock for this scope only
                std::scoped_lock<std::mutex> lock(mtx);
                if (isFirstStart) {
                    timestamp_ = frc::Timer::GetFPGATimestamp();
                    try {
                        for (auto & loop : loops_) {
                            loop.OnFirstStart(timestamp_);
                        }
                    }
                    catch (std::exception &ex) {
                        //ConsoleReporter.report(ex);
                    }
                }
                timestamp_ = frc::Timer::GetFPGATimestamp();
                try {
                    for (auto & loop : loops_) {
                        loop.OnStart(timestamp_);
                    }
                }
                catch (std::exception &ex) {
                    //ConsoleReporter.report(ex);
                }
                running_ = true;
                isFirstStart = false;
            }

            
            notifier_.StartPeriodic(kPeriod);
        }
    }

    void Stop() {
        if (running_) {
            notifier_.Stop();
            std::scoped_lock<std::mutex> lock(mtx);
            running_ = false;
            timestamp_ = frc::Timer::GetFPGATimestamp();
            try {
                for (auto & loop : loops_) {
                    loop.OnStop(timestamp_);
                }
            }
            catch (std::exception &ex) {
                //ConsoleReporter.report(ex);
            }
        }
    }

    std::vector<void *> GenerateReport() override {
        throw std::exception();
    };

private:
    bool running_;
    std::vector<Loop> loops_;
    frc::Notifier notifier_;
    double timestamp_;
    double dt_;
    bool isFirstStart;
    bool isFirstRun;
    std::mutex mtx;

};