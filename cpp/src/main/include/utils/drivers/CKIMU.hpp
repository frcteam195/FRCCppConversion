#pragma once

class CKIMU
{
	virtual double getFusedHeading() = 0;

	virtual double getRawYawDegrees() = 0;

	virtual double getPitch() = 0;

	virtual double getRoll() = 0;

	virtual bool isPresent() = 0;

	virtual bool reset() = 0;
};