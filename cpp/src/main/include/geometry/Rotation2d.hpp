#pragma once

#include <cmath>
#include <limits>
#include "Translation2d.hpp"
#include "utils/CKMath.hpp"

namespace ck
{
    namespace geometry
    {
        class Translation2d;

        class Rotation2d
        {
        protected:
            double cos_angle;
            double sin_angle;

        public:
            static const Rotation2d &identity();
            Rotation2d();
            Rotation2d(double x, double y, bool normalize);
            Rotation2d(Translation2d &direction, bool normalize);

            static Rotation2d fromRadians(double angle_radians);
            static Rotation2d fromDegrees(double angle_degrees);

            double cos();
            double sin();
            double tan();
            double getRadians();
            double getDegrees();
            Rotation2d rotateBy(Rotation2d &other);
            Rotation2d normal();
            Rotation2d inverse();
            bool isParallel(Rotation2d &other);
            Translation2d toTranslation();

        private:
        };
    } // namespace geometry
} // namespace ck