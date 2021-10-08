#include <vector>
#include <iostream>
#include <chrono>

#include "gtest/gtest.h"
#include "utils/CKMath.hpp"
#include "geometry/Geometry.hpp"
//#include "trajectory/timing/TimedState.hpp"
//#include "trajectory/timing/TimingUtil.hpp"
#include "trajectory/Trajectory.hpp"
#include "trajectory/DistanceView.hpp"

static double kTestEpsilon = 1e-9;

static std::vector<ck::geometry::Translation2d> waypoints =
{ ck::geometry::Translation2d(0.0, 0.0),
  ck::geometry::Translation2d(24.0, 0.0),
  ck::geometry::Translation2d(36.0, 0.0),
  ck::geometry::Translation2d(36.0, 24.0),
  ck::geometry::Translation2d(60.0, 24.0) };


TEST(DistanceView, test){
    // Create the reference trajectory (straight line motion between waypoints).
    ck::trajectory::Trajectory<ck::geometry::Translation2d> trajectory
        = ck::trajectory::Trajectory<ck::geometry::Translation2d>(waypoints);

    ck::trajectory::DistanceView<ck::geometry::Translation2d> distance_view
        = ck::trajectory::DistanceView<ck::geometry::Translation2d>(trajectory);

    ASSERT_NEAR(0.0, distance_view.first_interpolant(), kTestEpsilon);
    ASSERT_NEAR(84.0, distance_view.last_interpolant(), kTestEpsilon);

    ASSERT_EQ(waypoints[0], distance_view.sample(0.0).state());
    ASSERT_EQ(waypoints[0].interpolate(waypoints[1], 0.5), distance_view.sample(12.0).state());
    ASSERT_EQ(waypoints[3].interpolate(waypoints[4], 0.5), distance_view.sample(72.0).state());

}
