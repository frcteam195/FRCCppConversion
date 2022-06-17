#include "paths/TrajectoryGenerator.hpp"

namespace ck
{
    namespace paths
    {
        TrajectoryGenerator::TrajectoryGenerator(void)
        {
        }

        TrajectorySet::TrajectorySet(void)
        {
            
        }

        TrajectorySet TrajectoryGenerator::getTrajectorySet(void)
        {
            return this->mTrajectorySet;
        }

    } // namespace paths
} // namespace ck