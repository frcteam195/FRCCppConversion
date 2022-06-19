#pragma once

#include "geometry/Pose2dWithCurvature.hpp"
#include "physics/DifferentialDrive.hpp"
#include "trajectory/timing/TimingConstraint.hpp"
#include "trajectory/timing/TimedState.hpp"
#include "trajectory/Trajectory.hpp"
#include "trajectory/TrajectoryIterator.hpp"
#include "utils/CKMath.hpp"

namespace ck
{
    namespace planners
    {
        class DriveMotionPlanner
        {
        public:
            enum FollowerType
            {
                FEEDFORWARD_ONLY,
                PURE_PURSUIT,
                PID,
                NONLINEAR_FEEDBACK
            };

            DriveMotionPlanner(void);

            trajectory::Trajectory<trajectory::timing::TimedState<geometry::Pose2dWithCurvature>> generateTrajectory(bool reversed,
                                                                                                                     std::vector<geometry::Pose2d> waypoints,
                                                                                                                     std::vector<trajectory::timing::TimingConstraint<geometry::Pose2dWithCurvature>> constraints,
                                                                                                                     double maximumVelocity,   // Inches per Second
                                                                                                                     double maximumAcceleration, // Inches per Second^2
                                                                                                                     double maximumVoltage);
                                                                                                                     
            trajectory::Trajectory<trajectory::timing::TimedState<geometry::Pose2dWithCurvature>> generateTrajectory(bool reversed,
                                                                                                                     std::vector<geometry::Pose2d> waypoints,
                                                                                                                     std::vector<trajectory::timing::TimingConstraint<geometry::Pose2dWithCurvature>> constraints,
                                                                                                                     double startVelocity, // Inches per Second
                                                                                                                     double endVelocity, // Inches per Second
                                                                                                                     double maximumVelocity, // Inches per Second
                                                                                                                     double maximumAcceleration, // Inches per Second^2
                                                                                                                     double maximumVoltage);

            void setFollowerType(FollowerType type) { mFollowerType = type; }

        private:
            static constexpr double kMaxDx = 2.0;
            static constexpr double kMaxDy = 0.25;
            static constexpr double kMaxDtheta = 0.0872665; // 5 Degrees

            trajectory::TrajectoryIterator<trajectory::timing::TimedState<geometry::Pose2dWithCurvature>> *mCurrentTrajectory = NULL;

            FollowerType mFollowerType = FollowerType::NONLINEAR_FEEDBACK;
            
            bool mIsReversed = false;

            physics::DifferentialDrive *mModel;
        };

    } // namespace planners
} // namespace ck