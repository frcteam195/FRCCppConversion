#pragma once

#include <vector>
#include <cmath>
#include <type_traits>
#include "geometry/State.hpp"
#include "utils/CKMath.hpp"
#include "TrajectoryView.hpp"

namespace ck
{
    namespace trajectory
    {
        template <class S>
        class DistanceView : public TrajectoryView<S>
        {
        protected:
            Trajectory<S> trajectory_;
            std::vector<double> distances_;

        public:
            static_assert(std::is_base_of<ck::geometry::State<S>, S>::value, "S must inherit from State<S>");

            DistanceView(const Trajectory<S> &trajectory) : trajectory_(trajectory), distances_(trajectory.length())
            {
                distances_[0] = 0.0;
                for (int i = 1; i < trajectory_.length(); ++i)
                {
                    distances_[i] = distances_[i - 1] + trajectory_.getState(i - 1).distance(trajectory_.getState(i));
                }
            }
        };
    } // namespace trajectory
} // namespace ck