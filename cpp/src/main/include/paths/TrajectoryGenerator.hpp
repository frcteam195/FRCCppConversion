#pragma once

#include "paths/MirroredTrajectory.hpp"
#include "utils/Singleton.hpp"

namespace ck
{
    namespace paths
    {
        class TrajectorySet
        {
            public:
                paths::MirroredTrajectory* test90DegPath;

                TrajectorySet(void);
        };

        class TrajectoryGenerator : public Singleton<TrajectoryGenerator>
        {
        friend Singleton;

        private:
            // static const double kMaxVoltage = 9.0;
            // static const double kMaxAccel = 40.0;
            // static const double kMaxVelocity = 60.0;

            // static const double kFirstPathMaxVoltage = 9.0;
            // static const double kFirstPathMaxAccel = 80.0;
            // static const double kFirstPathMaxVel = 100.0;

            // static const double kMaxCentripetalAccel = 100.0;

            TrajectorySet mTrajectorySet;

            TrajectoryGenerator(void);
        
        public:
            TrajectorySet getTrajectorySet(void);
        };

    } // namespace paths
} // namespace ck