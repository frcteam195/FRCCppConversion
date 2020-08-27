#pragma once

#include "Pose2d.hpp"

namespace ck
{
    namespace geometry
    {
        class Pose2dWithCurvature
        {
        protected:
            Pose2d pose;
            double curvature;
            double dcurvature_ds;

        public:
            static const Pose2dWithCurvature &identity();

            Pose2dWithCurvature();
            Pose2dWithCurvature(const Pose2d &pose, double curvature, double dcurvature_ds = 0);
            Pose2dWithCurvature(const Translation2d &translation, const Rotation2d &rotation, double curvature, double dcurvature_ds = 0);

            bool operator==(const Pose2dWithCurvature &obj) const;
            friend std::ostream &operator<<(std::ostream &os, const Pose2dWithCurvature &t2d);

            Pose2d getPose() const;
            Pose2dWithCurvature transformBy(const Pose2d &transform) const;
            Pose2dWithCurvature mirror() const;
            double getCurvature() const;
            double getDCurvatureDs() const;
            Translation2d getTranslation() const;
            Rotation2d getRotation() const;
            Pose2dWithCurvature interpolate(const Pose2dWithCurvature &other, double interpFactor) const;
            double distance(const Pose2dWithCurvature &other) const;

        };
    } // namespace geometry
} // namespace ck