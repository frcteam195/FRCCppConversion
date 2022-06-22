#include "utils/DriveSignal.hpp"

namespace ck
{
    DriveSignal::DriveSignal(double left, double right)
    {
        DriveSignal(left, right, false);
    }

    DriveSignal::DriveSignal(double left, double right, bool brakeMode)
    {
        mLeftMotor = left;
        mRightMotor = right;
        mBrakeMode = brakeMode;
    }

    bool DriveSignal::getBrakeMode(void)
    {
        return mBrakeMode;
    }

    double DriveSignal::getLeft(void)
    {
        return mLeftMotor;
    }

    double DriveSignal::getRight(void)
    {
        return mRightMotor;
    }

    void DriveSignal::set(double left, double right)
    {
        std::scoped_lock<std::mutex> lock(mtx);
        mLeftMotor = left;
        mRightMotor = right;
    }

    void DriveSignal::setLeftMotor(double left)
    {
        std::scoped_lock<std::mutex> lock(mtx);
        mLeftMotor = left;
    }

    void DriveSignal::setRightMotor(double right)
    {
        std::scoped_lock<std::mutex> lock(mtx);
        mRightMotor = right;
    }
}