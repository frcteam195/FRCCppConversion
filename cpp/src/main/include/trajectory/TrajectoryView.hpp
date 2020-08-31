#pragma once

#include "geometry/Geometry.hpp"
#include "geometry/State.hpp"

namespace ck
{
    namespace trajectory
    {
        template <class S>
        class TrajectoryView
        {
            static_assert(std::is_base_of<ck::geometry::State, S>::value, "S must inherit from State");

        public:
            virtual TrajectorySamplePoint<S> sample(double interpolant) = 0;
            virtual double first_interpolant() = 0;
            virtual double last_interpolant() = 0;
            virtual Trajectory<S> trajectory() = 0;
        };
    } // namespace trajectory
} // namespace ck