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
            Translation2d(const Translation2d &start, const Translation2d &end);

            Translation2d operator+(const Translation2d &obj) const;
            bool operator==(const Translation2d &obj) const;
            friend std::ostream &operator<<(std::ostream &os, const Translation2d &t2d);

            double norm() const;
            double norm2() const;

            double getX() const;
            double getY() const;

            Translation2d translateBy(const Translation2d &other) const;
            Translation2d rotateBy(const Rotation2d &rotation) const;

            Rotation2d direction() const;
            Translation2d inverse() const;

            Translation2d interpolate(const Translation2d &other, double interpFactor) const;
            Translation2d extrapolate(const Translation2d &other, double interpFactor) const;

            Translation2d scale(double s) const;

            bool epsilonEquals(const Translation2d &other, double epsilon) const;

            static double dot(const Translation2d &a, const Translation2d &b);

            static Rotation2d getAngle(const Translation2d &a, const Translation2d &b);

            static double cross(const Translation2d &a, const Translation2d &b);

            double distance(const Translation2d &other) const;

        private:
            //Do not use. Instead, + by a negative translation
            Translation2d operator-(const Translation2d &obj) const;
        };
    } // namespace geometry
} // namespace ck