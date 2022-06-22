#pragma once

#include <mutex>

namespace ck {

    class DriveSignal
    {
        public:
            DriveSignal(double left, double right);
            DriveSignal(double left, double right, bool brakeMode);

            bool getBrakeMode(void);
            double getLeft(void);
            double getRight(void);

            void set(double left, double right);
            void setLeftMotor(double left);
            void setRightMotor(double right);

        private:
            std::mutex mtx;

            double mLeftMotor;
            double mRightMotor;
            bool mBrakeMode;
    };

}