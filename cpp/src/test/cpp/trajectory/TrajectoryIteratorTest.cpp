#include <vector>
#include <iostream>
#include <chrono>

#include "gtest/gtest.h"
#include "utils/CKMath.hpp"
#include "geometry/Geometry.hpp"
//#include "trajectory/timing/TimedState.hpp"
//#include "trajectory/timing/TimingUtil.hpp"
#include "trajectory/Trajectory.hpp"
#include "trajectory/TrajectoryIterator.hpp"


static double kTestEpsilon = 1e-9;

static std::vector<ck::geometry::Translation2d> kWaypoints =
{ ck::geometry::Translation2d(0.0, 0.0),
  ck::geometry::Translation2d(24.0, 0.0),
  ck::geometry::Translation2d(36.0, 12.0),
  ck::geometry::Translation2d(60.0, 12.0) };


TEST(TrajIteratorTest, Test)
{
    ck::trajectory::Trajectory<ck::geometry::Translation2d>* traj =
        new ck::trajectory::Trajectory<ck::geometry::Translation2d>(kWaypoints);

    ck::trajectory::TrajectoryIterator<ck::geometry::Translation2d> iterator =
        ck::trajectory::TrajectoryIterator<ck::geometry::Translation2d>(&(traj->getIndexView()));

    // Initial conditions.
    ASSERT_NEAR(0.0, iterator.getProgress(), kTestEpsilon);
    ASSERT_NEAR(3.0, iterator.getRemainingProgress(), kTestEpsilon);
    ASSERT_EQ(kWaypoints[0], iterator.getState());
    ASSERT_FALSE(iterator.isDone());

    // Advance forward.
    ASSERT_EQ(kWaypoints[0].interpolate(kWaypoints[1], 0.5), iterator.preview(0.5).state());
    ASSERT_EQ(kWaypoints[0].interpolate(kWaypoints[1], 0.5), iterator.advance(0.5).state());
    ASSERT_NEAR(0.5, iterator.getProgress(), kTestEpsilon);
    ASSERT_NEAR(2.5, iterator.getRemainingProgress(), kTestEpsilon);
    ASSERT_FALSE(iterator.isDone());

    // Advance backwards.
    ASSERT_EQ(kWaypoints[0].interpolate(kWaypoints[1], 0.25), iterator.preview(-0.25).state());
    ASSERT_EQ(kWaypoints[0].interpolate(kWaypoints[1], 0.25), iterator.advance(-0.25).state());
    ASSERT_NEAR(0.25, iterator.getProgress(), kTestEpsilon);
    ASSERT_NEAR(2.75, iterator.getRemainingProgress(), kTestEpsilon);
    ASSERT_FALSE(iterator.isDone());

    // Advance past end.
    ASSERT_EQ(kWaypoints[3], iterator.preview(5.0).state());
    ASSERT_EQ(kWaypoints[3], iterator.advance(5.0).state());
    ASSERT_NEAR(3.0, iterator.getProgress(), kTestEpsilon);
    ASSERT_NEAR(0.0, iterator.getRemainingProgress(), kTestEpsilon);
    ASSERT_TRUE(iterator.isDone());

    // Advance past beginning.
    ASSERT_EQ(kWaypoints[0], iterator.preview(-5.0).state());
    ASSERT_EQ(kWaypoints[0], iterator.advance(-5.0).state());
    ASSERT_NEAR(0.0, iterator.getProgress(), kTestEpsilon);
    ASSERT_NEAR(3.0, iterator.getRemainingProgress(), kTestEpsilon);
    ASSERT_FALSE(iterator.isDone());

    delete traj;
}
