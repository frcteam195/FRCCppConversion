#pragma once

#include "geometry/Geometry.hpp"
#include "geometry/State.hpp"
#include "MinMaxAcceleration.hpp"

namespace ck
{
    namespace trajectory
    {
        namespace timing
        {
            template <class S>
            class TimingConstraint
            {
                static_assert(std::is_base_of<ck::geometry::State, S>::value, "S must inherit from State");

            public:
                virtual double getMaxVelocity(const S &state) const = 0;
                virtual MinMaxAcceleration getMinMaxAcceleration(const S &state, double velocity) const = 0;
            };
        } // namespace timing
    }     // namespace trajectory
} // namespace ck