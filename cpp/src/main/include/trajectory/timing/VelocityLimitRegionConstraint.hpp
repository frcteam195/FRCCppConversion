#pragma once

#include <type_traits>
#include "geometry/Geometry.hpp"
#include "MinMaxAcceleration.hpp"
#include "utils/CKMath.hpp"

namespace ck
{
    namespace trajectory
    {
        namespace timing
        {
            template <class S>
            class VelocityLimitRegionConstraint : public TimingConstraint<S>
            {
                static_assert(std::is_base_of<ck::geometry::ITranslation2d<S>, S>::value, "S must inherit from ITranslation2d<S>");

            protected:
                ck::geometry::Translation2d min_corner_;
                ck::geometry::Translation2d max_corner_;
                double velocity_limit_;

            public:
                VelocityLimitRegionConstraint(ck::geometry::Translation2d min_corner, ck::geometry::Translation2d max_corner, double velocity_limit) : min_corner_(min_corner), max_corner_(max_corner), velocity_limit_(velocity_limit) {}
                double getMaxVelocity(const S &state) const override
                {
                    ck::geometry::Translation2d translation = state.getTranslation();
                    if (translation.x() <= max_corner_.x() && translation.x() >= min_corner_.x() &&
                        translation.y() <= max_corner_.y() && translation.y() >= min_corner_.y())
                    {
                        return velocity_limit_;
                    }
                    return ck::math::POS_INF;
                }
                MinMaxAcceleration getMinMaxAcceleration(const S &state, double velocity) const override
                {
                    return MinMaxAcceleration::kNoLimits;
                }
            };
        } // namespace timing
    }     // namespace trajectory
} // namespace ck