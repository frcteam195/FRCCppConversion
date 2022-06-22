#include "subsystems/Drive.hpp"

#include "utils/DriveSignal.hpp"

DataReporter *Drive::logReporter = &NetworkDataReporter::getInstance();

Drive::Drive()
{
}

void Drive::stop()
{
}

void Drive::onFirstStart(double timestamp)
{
}

void Drive::onStart(double timestamp)
{
}

void Drive::onStop(double timestamp)
{
    stop();
}

void Drive::onLoop(double timestamp)
{
}

std::string Drive::getName()
{
    return "DriveLoop";
}

void Drive::registerEnabledLoops(ILooper &enabledLooper)
{
    enabledLooper.registerLoop(*this);
}

double Drive::inchesToRotations(double inches)
{
    return inches / (K_DRIVE_WHEEL_DIAMETER_INCHES * M_PI);
}

double Drive::radiansPerSecondToRpm(double radiansPerSecond)
{
    return radiansPerSecond / (2.0 * M_PI) * 60.0;
}

double Drive::rotationsToInches(double rotations)
{
    return rotationsToInches * (K_DRIVE_WHEEL_DIAMETER_INCHES * M_PI);
}

bool Drive::isSystemFaulted()
{
    return false;
}

bool Drive::runDiagnostics()
{
    return true;
}

bool Drive::isDoneWithTrajectory()
{
    if (mMotionPlanner == NULL || mDriveControlState != PATH_FOLLOWING)
    {
        return false;
    }

    return mMotionPlanner->isDone() || mOverrideTrajectory;
}

double Drive::getLeftEncoderDistance()
{
    return rotationsToInches(mPeriodicIO.leftPositionRotations);
}

double Drive::getRightEncoderDistance()
{
    return rotationsToInches(mPeriodicIO.rightPositionRotations);
}

double Drive::getRightLinearVelocity()
{
    return rotationsToInches(mPeriodicIO.rightVelocityRpm / 60.0);
}

double Drive::getLeftLinearVelocity()
{
    return rotationsToInches(mPeriodicIO.leftVelocityRpm / 60.0);
}

double Drive::getLinearVelocity()
{
    return (getLeftLinearVelocity() + getRightLinearVelocity()) / 2.0;
}

void Drive::setDriveControlState(DriveControlState driveControlState)
{
    std::scoped_lock<std::mutex> lock(memberAccessMtx);
    mDriveControlState = driveControlState;
}

void Drive::setOverrideTrajectory(bool value)
{
    mOverrideTrajectory = value;
}

void Drive::setTrajectory(TrajectoryIterator<TimedState<Pose2dWithCurvature>> trajectory)
{
    std::scoped_lock<std::mutex> lock(memberAccessMtx);
    if (mMotionPlanner != NULL)
    {
        mOverrideTrajectory = false;
        mMotionPlanner->reset();
        mMotionPlanner->setTrajectory(trajectory);
        setDriveControlState(PATH_FOLLOWING);
    }
}

Rotation2d Drive::getHeading()
{
    return mPeriodicIO.gyroHeading;
}

void Drive::setHeading(Rotation2d heading)
{
    mGyroOffset = heading.rotateBy(Rotation2d::fromDegrees(mGyro.getFusedHeading()).inverse());
    mPeriodicIO.gyroHeading = heading;
}

void Drive::forceBrakeModeUpdate(void)
{
    mForceBrakeUpdate = true;
}

bool Drive::isBrakeMode(void)
{
    return mIsBrakeMode;
}

void Drive::setBrakeMode(bool brake)
{
    mIsBrakeMode = brake;
}

void Drive::updatePathFollower(void)
{
    if (mDriveControlState == PATH_FOLLOWING)
    {
        double currentPathFollowingTime = Timer.getFPGATimestamp();

        Output motionPlannerOutput = mMotionPlanner.update(currentPathFollowingTime, RobotState.getInstance().getFieldToVehicle(currPathFollowingTime));

        utils::DriveSignal pathVelocityWheelContainer = utils::DriveSignal(0, 0);
        utils::DriveSignal pathFeedForwardWheelContainer = utils::DriveSignal(0, 0);

        mPeriodicIO.error = mMotionPlanner.error();
        mPeriodicIO.pathSetpoint = mMotionPlanner.setpoint();

        if (!mOverrideTrajectory)
        {
            pathVelWheelContainer.set(radiansPerSecondToRPM(motionPlannerOutput.left_velocity) * CalConstants.kDriveGearRatioMotorConversionFactor,
            //                           radiansPerSecondToRPM(motionPlannerOutput.right_velocity) * CalConstants.kDriveGearRatioMotorConversionFactor);
            // pathFFWheelContainer.set(motionPlannerOutput.left_feedforward_voltage / 12.0,
            //                          motionPlannerOutput.right_feedforward_voltage / 12.0);
            // setVelocity(pathVelWheelContainer, pathFFWheelContainer);

            mPeriodicIO.mLeftAcceleration = radiansPerSecondToRpm(motionPlannerOutput.mLeftAcceleration) / 1000.0;
            mPeriodicIO.mRightAcceleration = radiansPerSecondToRpm(motionPlannerOutput.mLeftAcceleration) / 1000.0;
        }
        else
        {
            // setVelocity(DriveSignal.BRAKE, DriveSignal.BRAKE);
            mPeriodicIO.mLeftAcceleration = 0.0;
            mPeriodicIO.mRightAcceleration = 0.0;
        }
        // } else {
        // 	ConsoleReporter.report("Drive is not in path following state", MessageLevel.ERROR);
    }
}