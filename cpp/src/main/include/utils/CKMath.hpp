#pragma once

#include <limits>

namespace ck
{
    namespace math
    {
        constexpr double kEpsilon = 1e-12;
        constexpr double PI = 3.14159265358979323846;
        constexpr float PI_F = 3.14159265358979323846f;
        constexpr double POS_INF = std::numeric_limits<double>::infinity();
        constexpr double NEG_INF = -POS_INF;
        constexpr double POS_INF_F = std::numeric_limits<float>::infinity();
        constexpr double NEG_INF_F = -POS_INF_F;

        template <typename T>
        inline T max(T a, T b)
        {
            return a > b ? a : b;
        }

        template <typename T>
        inline T min(T a, T b)
        {
            return a < b ? a : b;
        }

        template <typename T>
        inline bool epsilonEquals(T const &a, T const &b, T epsilon)
        {
            return (a - epsilon <= b) && (a + epsilon >= b);
        }
        
        template <typename T>
        inline bool epsilonEquals(T const &a, T const &b)
        {
            return epsilonEquals(a, b, kEpsilon);
        }

        inline double deg2rad(double deg)
        {
            return deg * PI / 180.0;
        }

        inline float deg2radf(float deg)
        {
            return deg * PI_F / 180.0f;
        }

        inline double rad2deg(double rad)
        {
            return rad * 180.0 / PI;
        }

        inline float rad2degf(float rad)
        {
            return rad * 180.0f / PI_F;
        }
    } // namespace math
} // namespace ck
