#pragma once

#include <cmath>
#include <ostream>
#include <iomanip>
#include "utils/CKMath.hpp"
#include "Rotation2d.hpp"

namespace ck
{
    namespace geometry
    {
        class Rotation2d;

        class Translation2d
        {
        protected:
            double x;
            double y;

        public:
            static const Translation2d &identity();

            Translation2d();
            Translation2d(double x, double y);
            Translation2d(Translation2d &start, Translation2d &end);

            Translation2d operator+(const Translation2d &obj);
            bool operator==(const Translation2d &obj);
            friend std::ostream &operator<<(std::ostream &os, const Translation2d &t2d);

            double norm();
            double norm2();

            double getX();
            double getY();

            Translation2d translateBy(Translation2d &other);
            Translation2d rotateBy(Rotation2d &rotation);

            Rotation2d direction();
            Translation2d inverse();

            Translation2d interpolate(Translation2d &other, double interpFactor);
            Translation2d extrapolate(Translation2d &other, double interpFactor);

            Translation2d scale(double s);

            bool epsilonEquals(Translation2d &other, double epsilon);

            static double dot(Translation2d &a, Translation2d &b);

            static Rotation2d getAngle(Translation2d &a, Translation2d &b);

            static double cross(Translation2d a, Translation2d b);

            double distance(Translation2d &other);

        private:
            //Do not use. Instead, + by a negative translation
            Translation2d operator-(const Translation2d &obj);
        };
    } // namespace geometry
} // namespace ck