#pragma once

#include "ctre/Phoenix.h"
#include "CKIMU.hpp"
#include <string>
#include <atomic>

class CKPigeon2 : public CKIMU
{
public:
    CKPigeon2(int deviceNumber = 0, std::string const &canbus = "");
	double getFusedHeading();
    double getRawYawDegrees();
	double getPitch();
    double getRoll();
    bool isPresent();
    bool reset();

private:
    Pigeon2 mPigeon;
};