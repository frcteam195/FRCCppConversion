#pragma once

#include "ctre/Phoenix.h"
#include "geometry/Pose2d.hpp"
#include "geometry/Pose2dWithCurvature.hpp"
#include "geometry/Rotation2d.hpp"
#include "plannners/DriveMotionPlanner.hpp"
#include "reporters/DataReporter.hpp"
#include "reporters/NetworkDataReporter.hpp"
#include "reporters/NetworkDataType.hpp"
#include "trajectory/TrajectoryIterator.hpp"
#include "trajectory/timing/TimedState.hpp"
#include "utils/Singleton.hpp"
#include "utils/Subsystem.hpp"
#include "utils/drivers/CKTalonFX.hpp"

#include <atomic>
#include <mutex>

using namespace ck::geometry;
using namespace ck::log;
using namespace ck::planners;
using namespace ck::trajectory;
using namespace ck::trajectory::timing;

class Drive : public Subsystem, public Singleton<Drive>, public Loop
{
    friend Singleton;
    friend class PeriodicIO;

public:
    enum DriveControlState
    {
        OPEN_LOOP,
        PATH_FOLLOWING,
        VELOCITY,
        CLIMB,
        OPEN_LOOP_AUTOMATED
    };

    void stop() override;

    bool isSystemFaulted() override;

    bool runDiagnostics() override;

    void registerEnabledLoops(ILooper &enabledLooper) override;

    void onFirstStart(double timestamp) override;
    void onStart(double timestamp) override;
    void onStop(double timestamp) override;
    void onLoop(double timestamp) override;
    std::string getName() override;

    bool isDoneWithTrajectory(void);

    void forceBrakeModeUpdate(void);
    bool isBrakeMode(void)
    void setBrakeMode(bool brake);

    double getLeftEncoderDistance(void);
    double getRightEncoderDistance(void);
    double getRightLinearVelocity(void);
    double getLeftLinearVelocity(void);
    double getLinearVelocity(void);

    void updatePathFollower(void);

    void setDriveControlState(DriveControlState driveControlState);
    void setOverrideTrajectory(bool value);
    void setTrajectory(TrajectoryIterator<TimedState<Pose2dWithCurvature>> trajectory);

    Rotation2d getHeading();
    void setHeading(Rotation2d heading);

private:
    Drive();
    ctre::
    CKTalonFX *mLeftMaster;
    CKTalonFX *mRightMaster;
    CKTalonFX *mLeftSlave;
    CKTalonFX *mRightSlave;
    DriveControlState mDriveControlState;
    DriveMotionPlanner *mMotionPlanner;

    Rotation2d mGyroOffset = Rotation2d::identity();
    bool mOverrideTrajectory = false;

    std::atomic_bool mIsBrakeMode = false;
    std::atomic_bool mForceBrakeUpdate = false;
    bool mPreviousBrakeMode;

    static DataReporter *logReporter;
    std::mutex memberAccessMtx;

    const ElapsedTimer *loopTimer = new ElapsedTimer();
    const ElapsedTimer *driveLoopTimer = new ElapsedTimer();

    static double inchesToRotations(double inches);
    static double radiansPerSecondToRpm(double radiansPerSecond);
    static double rotationsToInches(double rotations);

    class PeriodicIO
    {
    public:
        PeriodicIO() {};

        double leftPositionRotations;
        double rightPositionRotations;

        double leftDistance;
        double rightDistance;
        double leftVelocityRpm;
        double rightVelocityRpm;
        Rotation2d gyroHeading = Rotation2d::identity();
        double gyroRoll;
        Pose2d error = Pose2d::identity();

        double leftBusVoltage;
        double rightBusVoltage;

        double leftDriveCurrent;
        double rightDriveCurrent;

        bool gyroPresent;

        double previousLeftRotations;
        double previousRightRotations;
        double deltaLeftRotations;
        double deltaRightRotations;

        // OUTPUTS
        double leftDemand;
        double rightDemand;
        double leftAcceleration;
        double rightAcceleration;
        double leftFeedForward;
        double rightFeedForward;
        TimedState<Pose2dWithCurvature> *pathSetpoint = new TimedState<Pose2dWithCurvature>(Pose2dWithCurvature::identity());
        double driveLoopTime;
    };

    PeriodicIO mPeriodicIO;
};
