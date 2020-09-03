#include <vector>
#include <iostream>
#include <chrono>

#include "gtest/gtest.h"
#include "utils/CKMath.hpp"
#include "geometry/Geometry.hpp"
#include "trajectory/timing/TimedState.hpp"
#include "trajectory/timing/TimingUtil.hpp"

using namespace std;
using namespace ck::geometry;
using namespace ck::trajectory;
using namespace ck::trajectory::timing;

template <class S>
void checkTrajectory(Trajectory<TimedState<S>> &traj,
                     std::vector<TimingConstraint<S>> &constraints,
                     double start_vel,
                     double end_vel,
                     double max_vel,
                     double max_acc)
{
    static double kTestEpsilon = 1e-12;

    ASSERT_FALSE(traj.isEmpty());
    ASSERT_NEAR(traj.getState(0).velocity(), start_vel, kTestEpsilon);
    ASSERT_NEAR(traj.getState(traj.length() - 1).velocity(), end_vel, kTestEpsilon);

    // Go state by state, verifying all constraints are satisfied and integration is correct.
    for (int i = 0; i < traj.length(); ++i)
    {
        const TimedState<S> &state = traj.getState(i);
        for (const TimingConstraint<S> &constraint : constraints)
        {
            ASSERT_TRUE(state.velocity() - kTestEpsilon <= constraint.getMaxVelocity(state.state()));
            MinMaxAcceleration accel_limits = constraint.getMinMaxAcceleration(state.state(), state.velocity());
            ASSERT_TRUE(state.acceleration() - kTestEpsilon <= accel_limits.max_acceleration());
            ASSERT_TRUE(state.acceleration() + kTestEpsilon >= accel_limits.min_acceleration());
        }
        if (i > 0)
        {
            const TimedState<S> &prev_state = traj.getState(i - 1);
            ASSERT_NEAR(state.velocity(), prev_state.velocity() + (state.t() - prev_state.t()) * prev_state.acceleration(), kTestEpsilon);
        }
    }
}

template <class S>
Trajectory<TimedState<S>> buildAndCheckTrajectory(DistanceView<S> &dist_view,
                                                  double step_size,
                                                  std::vector<TimingConstraint<S>> &constraints,
                                                  double start_vel,
                                                  double end_vel,
                                                  double max_vel,
                                                  double max_acc)
{
    Trajectory<TimedState<S>> timed_traj = TimingUtil::timeParameterizeTrajectory(false, dist_view, step_size, constraints, start_vel, end_vel, max_vel, max_acc);
    checkTrajectory(timed_traj, constraints, start_vel, end_vel, max_vel, max_acc);
    return timed_traj;
}

static vector<Translation2d> kTimingUtilTestWaypoints 
{
    Translation2d(0.0, 0.0),
    Translation2d(24.0, 0.0),
    Translation2d(36.0, 12.0),
    Translation2d(60.0, 12.0)
};

TEST(TimingUtilTest, NoConstraints)
{
    Trajectory<Translation2d> traj(kTimingUtilTestWaypoints);
    DistanceView<Translation2d> dist_view(traj);

    vector<TimingConstraint<Translation2d>> tmpVector;
    // // Triangle profile.
    Trajectory<TimedState<Translation2d>> timed_traj = buildAndCheckTrajectory(dist_view, 1.0, tmpVector, 0.0, 0.0, 20.0, 5.0);
    // tmpVector.clear();

    // // Trapezoidal profile.
    // timed_traj = buildAndCheckTrajectory(dist_view, 1.0, tmpVector, 0.0, 0.0, 10.0, 5.0);
    // tmpVector.clear();

    // // Trapezoidal profile with start and end velocities.
    // timed_traj = buildAndCheckTrajectory(dist_view, 1.0, tmpVector, 5.0, 2.0, 10.0, 5.0);
}