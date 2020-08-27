#include "geometry/Translation2d.hpp"

namespace ck
{
    namespace geometry
    {
        const Translation2d &Translation2d::identity()
        {
            static Translation2d kIdentity;
            return kIdentity;
        }
        Translation2d::Translation2d() : x(0), y(0) {}
        Translation2d::Translation2d(double x, double y) : x(x), y(y) {}
        Translation2d::Translation2d(const Translation2d &start, const Translation2d &end) : x(end.x - start.x), y(end.y - start.y) {}

        Translation2d Translation2d::operator+(const Translation2d &obj) const
        {
            return Translation2d(this->x + obj.x, this->y + obj.y);
        }
        //Do not use. Instead, + by a negative translation
        Translation2d Translation2d::operator-(const Translation2d &obj) const
        {
            return Translation2d(this->x - obj.x, this->y - obj.y);
        }
        bool Translation2d::operator==(const Translation2d &obj) const
        {
            return distance(obj) < ck::math::kEpsilon;
        }

        std::ostream &operator<<(std::ostream &os, const Translation2d &t2d)
        {
            os << std::setprecision(3) << "(x: " << t2d.x << ", y: " << t2d.y << ")";
            return os;
        }

        double Translation2d::norm() const
        {
            return std::hypot(x, y);
        }

        double Translation2d::norm2() const
        {
            return ((x * x) + (y * y));
        }

        double Translation2d::getX() const { return x; }
        double Translation2d::getY() const { return y; }

        Translation2d Translation2d::translateBy(const Translation2d &other) const
        {
            return *this + other;
        }

        Translation2d Translation2d::rotateBy(const Rotation2d &rotation) const
        {
            return Translation2d(x * rotation.cos() - y * rotation.sin(), x * rotation.sin() + y * rotation.cos());
        }

        Rotation2d Translation2d::direction() const
        {
            return Rotation2d(x, y, true);
        }

        Translation2d Translation2d::inverse() const
        {
            return Translation2d(-x, -y);
        }

        Translation2d Translation2d::interpolate(const Translation2d &other, double interpFactor) const
        {
            if (interpFactor <= 0)
            {
                return Translation2d(*this);
            }
            else if (interpFactor >= 1)
            {
                return Translation2d(other);
            }
            return Translation2d(extrapolate(other, x));
        }

        Translation2d Translation2d::extrapolate(const Translation2d &other, double interpFactor) const
        {
            return Translation2d(interpFactor * (other.x - x) + x, interpFactor * (other.y - y) + y);
        }

        Translation2d Translation2d::scale(double s) const
        {
            return Translation2d(x * s, y * s);
        }

        bool Translation2d::epsilonEquals(const Translation2d &other, double epsilon) const
        {
            return ck::math::epsilonEquals(x, other.x, epsilon) && ck::math::epsilonEquals(y, other.y, epsilon);
        }

        double Translation2d::dot(const Translation2d &a, const Translation2d &b)
        {
            return a.x * b.x + a.y * b.y;
        }

        Rotation2d Translation2d::getAngle(const Translation2d &a, const Translation2d &b)
        {
            double cos_angle = dot(a, b) / (a.norm() * b.norm());
            if (std::isnan(cos_angle))
            {
                return Rotation2d();
            }
            return Rotation2d::fromRadians(std::acos(ck::math::min(1.0, ck::math::max(cos_angle, -1.0))));
        }

        double Translation2d::cross(const Translation2d &a, const Translation2d &b)
        {
            return a.x * b.y - a.y * b.x;
        }

        double Translation2d::distance(const Translation2d &other) const
        {
            return inverse().translateBy(other).norm();
        }

    } // namespace geometry
} // namespace ck
