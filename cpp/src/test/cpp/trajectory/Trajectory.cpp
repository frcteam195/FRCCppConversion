#include <vector>
#include <iostream>
#include <chrono>

#include "gtest/gtest.h"
#include "utils/CKMath.hpp"
#include "geometry/Geometry.hpp"
//#include "trajectory/timing/TimedState.hpp"
//#include "trajectory/timing/TimingUtil.hpp"
#include "trajectory/Trajectory.hpp"

double kTestEpsilon = 1e-9;


std::vector<ck::geometry::Translation2d> kWaypoints =
{ ck::geometry::Translation2d(0.0, 0.0),
  ck::geometry::Translation2d(24.0, 0.0),
  ck::geometry::Translation2d(36.0, 12.0),
  ck::geometry::Translation2d(60.0, 12.0) };


TEST(TrajTest, Construction){
    ck::trajectory::Trajectory<ck::geometry::Translation2d> traj =
        ck::trajectory::Trajectory<ck::geometry::Translation2d>();

    ASSERT_TRUE(traj.isEmpty());
    ASSERT_NEAR(0.0, traj.getIndexView().first_interpolant(), kTestEpsilon);
    ASSERT_NEAR(0.0, traj.getIndexView().last_interpolant(), kTestEpsilon);
    ASSERT_EQ(0, traj.length());


    traj = ck::trajectory::Trajectory<ck::geometry::Translation2d>(kWaypoints);
    ASSERT_FALSE(traj.isEmpty());
    ASSERT_NEAR(0.0, traj.getIndexView().first_interpolant(), kTestEpsilon);
    ASSERT_NEAR(3.0, traj.getIndexView().last_interpolant(), kTestEpsilon);
    ASSERT_EQ(4, traj.length());

}

TEST(TrajTest, StateAccessor){
    ck::trajectory::Trajectory<ck::geometry::Translation2d> traj =
        ck::trajectory::Trajectory<ck::geometry::Translation2d>();

        ASSERT_EQ( kWaypoints[0], traj.getState(0) );
        ASSERT_EQ( kWaypoints[1], traj.getState(1) );
        ASSERT_EQ( kWaypoints[2], traj.getState(2) );
        ASSERT_EQ( kWaypoints[3], traj.getState(3) );

        /*
        ASSERT_EQ( kWaypoints.get(0), traj.getInterpolated(0.0).state() );
        ASSERT_EQ( traj.getInterpolated(0.0).index_floor(), 0 );
        ASSERT_EQ( traj.getInterpolated(0.0).index_ceil(), 0 );
        ASSERT_EQ( kWaypoints.get(1), traj.getInterpolated(1.0).state() );
        ASSERT_EQ( traj.getInterpolated(1.0).index_floor(), 1 );
        ASSERT_EQ( traj.getInterpolated(1.0).index_ceil(), 1 );
        ASSERT_EQ( kWaypoints.get(2), traj.getInterpolated(2.0).state() );
        ASSERT_EQ( traj.getInterpolated(2.0).index_floor(), 2 );
        ASSERT_EQ( traj.getInterpolated(2.0).index_ceil(), 2 );
        ASSERT_EQ( kWaypoints.get(3), traj.getInterpolated(3.0).state() );
        ASSERT_EQ( traj.getInterpolated(3.0).index_floor(), 3 );
        ASSERT_EQ( traj.getInterpolated(3.0).index_ceil(), 3 );

        ASSERT_EQ( kWaypoints.get(0).interpolate(kWaypoints.get(1), .25), traj.getInterpolated(0.25).state() );
        ASSERT_EQ( traj.getInterpolated(0.25).index_floor(), 0 );
        ASSERT_EQ( traj.getInterpolated(0.25).index_ceil(), 1 );
        ASSERT_EQ( kWaypoints.get(1).interpolate(kWaypoints.get(2), .5), traj.getInterpolated(1.5).state() );
        ASSERT_EQ( traj.getInterpolated(1.5).index_floor(), 1 );
        ASSERT_EQ( traj.getInterpolated(1.5).index_ceil(), 2 );
        ASSERT_EQ( kWaypoints.get(2).interpolate(kWaypoints.get(3), .75), traj.getInterpolated(2.75).state() );
        ASSERT_EQ( traj.getInterpolated(2.75).index_floor(), 2 );
        ASSERT_EQ( traj.getInterpolated(2.75).index_ceil(), 3 );

        ck::trajectory::IndexView<ck::geometry::Translation2d> index_view = traj.getIndexView();
        ASSERT_EQ( kWaypoints.get(0).interpolate(kWaypoints.get(1), .25), index_view.sample(0.25).state() );
        ASSERT_EQ( kWaypoints.get(1).interpolate(kWaypoints.get(2), .5), index_view.sample(1.5).state() );
        ASSERT_EQ( kWaypoints.get(2).interpolate(kWaypoints.get(3), .75), index_view.sample(2.75).state() );
        */
}


