#pragma once

#include <cmath>
#include <vector>
#include "utils/CKMath.hpp"
#include "utils/PolynomialRegression.hpp"

namespace ck
{
    namespace physics
    {
        struct CharacterizationConstants
        {
            double ks;
            double kv;
            double ka;
        };
        struct VelocityDataPoint
        {
            double velocity;
            double power;
        };
        struct AccelerationDataPoint
        {
            double velocity;
            double power;
            double acceleration;
        };
        struct CurvatureDataPoint
        {
            double linear_velocity;
            double angular_velocity;
            double left_voltage;
            double right_voltage;
        };
        static CharacterizationConstants &characterizeDrive(std::vector<VelocityDataPoint> velocityData, std::vector<AccelerationDataPoint> accelerationData)
        {
            CharacterizationConstants constants{0, 0, 0};
            std::vector<double> xPoints;
            std::vector<double> yPoints;
            getVelocityData(velocityData, xPoints, yPoints);
            getVelocityCharacterization(xPoints, yPoints, constants);
            getAccelerationData(accelerationData, constants, xPoints, yPoints);
            getAccelerationCharacterization(xPoints, yPoints, constants);
            return constants;
        };
        //TODO: Needs testing of new PolynomailRegression methods
        static void getVelocityCharacterization(std::vector<double> &xPoints, std::vector<double> &yPoints, CharacterizationConstants &constants)
        {
            PolynomialRegression<double> p;
            std::vector<double> coeffs;
            p.fitIt(xPoints, yPoints, 1, coeffs);
            // ConsoleReporter.report("r^2: " + p.R2());
            constants.ks = coeffs[0];
            constants.kv = coeffs[1];
        };
        static void getAccelerationCharacterization(std::vector<double> &xPoints, std::vector<double> &yPoints, CharacterizationConstants &constants)
        {
            PolynomialRegression<double> p;
            std::vector<double> coeffs;
            p.fitIt(xPoints, yPoints, 1, coeffs);
            // ConsoleReporter.report("r^2: " + p.R2());
            constants.ka = coeffs[1];
        };

        static void getVelocityData(std::vector<VelocityDataPoint> &input, std::vector<double> &xPoints, std::vector<double> &yPoints)
        {
            xPoints.clear();
            yPoints.clear();
            int startTrim = 0;
            for (int i = 0; i < input.size(); ++i)
            {
                if (input[i].velocity > ck::math::kEpsilon)
                {
                    if (startTrim == 0)
                    {
                        startTrim = i;
                    }
                    xPoints.push_back(input[i].velocity);
                    yPoints.push_back(input[i].power);
                }
            }
        };

        static void getAccelerationData(std::vector<AccelerationDataPoint> &input, CharacterizationConstants &constants, std::vector<double> &xPoints, std::vector<double> &yPoints)
        {
            xPoints.clear();
            yPoints.clear();
            for (int i = 0; i < input.size(); ++i)
            {
                xPoints.push_back(input[i].acceleration);
                yPoints.push_back(input[i].power - constants.kv * input[i].velocity - constants.ks);
            }
        };
    } // namespace physics
} // namespace ck