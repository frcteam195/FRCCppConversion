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
        Translation2d::Translation2d(double x, double y)
        {
            this->x = x;
            this->y = y;
        }
        Translation2d::Translation2d(Translation2d &start, Translation2d &end)
        {
            this->x = end.x - start.x;
            this->y = end.y - start.y;
        }

        Translation2d Translation2d::operator+(const Translation2d &obj)
        {
            return Translation2d(this->x + obj.x, this->y + obj.y);
        }
        //Do not use. Instead, + by a negative translation
        Translation2d Translation2d::operator-(const Translation2d &obj)
        {
            return Translation2d(this->x - obj.x, this->y - obj.y);
        }
        bool Translation2d::operator==(const Translation2d &obj)
        {
            return distance((Translation2d &)obj) < ck::math::kEpsilon;
        }

        std::ostream &operator<<(std::ostream &os, const Translation2d &t2d)
        {
            os << std::setprecision(3) << "x: " << t2d.x << ", y: " << t2d.y;
            return os;
        }

        double Translation2d::norm()
        {
            return std::hypot(x, y);
        }

        double Translation2d::norm2()
        {
            return ((x * x) + (y * y));
        }

        double Translation2d::getX() { return x; }
        double Translation2d::getY() { return y; }

        Translation2d Translation2d::translateBy(Translation2d &other)
        {
            return *this + other;
        }

        Translation2d Translation2d::rotateBy(Rotation2d &rotation)
        {
            x = x * rotation.cos() - y * rotation.sin();
            y = x * rotation.sin() + y * rotation.cos();
            return *this;
        }

        Rotation2d Translation2d::direction()
        {
            return Rotation2d(x, y, true);
        }

        Translation2d Translation2d::inverse()
        {
            return Translation2d(-x, -y);
        }

        Translation2d Translation2d::interpolate(Translation2d &other, double interpFactor)
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

        Translation2d Translation2d::extrapolate(Translation2d &other, double interpFactor)
        {
            return Translation2d(interpFactor * (other.x - x) + x, interpFactor * (other.y - y) + y);
        }

        Translation2d Translation2d::scale(double s)
        {
            return Translation2d(x * s, y * s);
        }

        bool Translation2d::epsilonEquals(Translation2d &other, double epsilon)
        {
            return ck::math::epsilonEquals(x, other.x, epsilon) && ck::math::epsilonEquals(y, other.y, epsilon);
        }

        double Translation2d::dot(Translation2d &a, Translation2d &b)
        {
            return a.x * b.x + a.y * b.y;
        }

        Rotation2d Translation2d::getAngle(Translation2d &a, Translation2d &b)
        {
            double cos_angle = dot(a, b) / (a.norm() * b.norm());
            if (std::isnan(cos_angle))
            {
                return Rotation2d();
            }
            return Rotation2d::fromRadians(std::acos(ck::math::min(1.0, ck::math::max(cos_angle, -1.0))));
        }

        double Translation2d::cross(Translation2d &a, Translation2d &b)
        {
            return a.x * b.y - a.y * b.x;
        }

        double Translation2d::distance(Translation2d &other)
        {
            return inverse().translateBy(other).norm();
        }

    } // namespace geometry
} // namespace ck
