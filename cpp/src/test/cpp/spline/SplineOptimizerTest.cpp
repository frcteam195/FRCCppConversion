#include <vector>
#include <iostream>
#include <chrono>

#include "gtest/gtest.h"
#include "spline/QuinticHermiteSpline.hpp"
#include "utils/CKMath.hpp"

using namespace std;
using namespace ck::geometry;
using namespace ck::spline;

#define CURRENT_MILLIS (std::chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count())

TEST(SplineOptimizationTest, PlausibleOutput)
{
    double kTestEps = 1e-12;
    Pose2d a(Translation2d(0, 100), Rotation2d::fromDegrees(270));
    Pose2d b(Translation2d(50, 0), Rotation2d::fromDegrees(0));
    Pose2d c(Translation2d(100, 100), Rotation2d::fromDegrees(90));

    vector<QuinticHermiteSpline> splines;
    splines.push_back(QuinticHermiteSpline(a, b));
    splines.push_back(QuinticHermiteSpline(b, c));

    auto start_time = std::chrono::high_resolution_clock::now();
    ASSERT_TRUE(QuinticHermiteSpline::optimizeSpline(splines) < 0.014);
    cout << "Optimization time (us): " << (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start_time).count() / 1000.0) << std::endl;

    Pose2d d(Translation2d(0, 0), Rotation2d::fromDegrees(90));
    Pose2d e(Translation2d(0, 50), Rotation2d::fromDegrees(0));
    Pose2d f(Translation2d(100, 0), Rotation2d::fromDegrees(90));
    Pose2d g(Translation2d(100, 100), Rotation2d::fromDegrees(0));

    vector<QuinticHermiteSpline> splines1;
    splines1.push_back(QuinticHermiteSpline(d, e));
    splines1.push_back(QuinticHermiteSpline(e, f));
    splines1.push_back(QuinticHermiteSpline(f, g));

    start_time = std::chrono::high_resolution_clock::now();
    ASSERT_TRUE(QuinticHermiteSpline::optimizeSpline(splines1) < 0.16);
    cout << "Optimization time (us): " << (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start_time).count() / 1000.0) << std::endl;

    Pose2d h(Translation2d(0, 0), Rotation2d::fromDegrees(0));
    Pose2d i(Translation2d(50, 0), Rotation2d::fromDegrees(0));
    Pose2d j(Translation2d(100, 50), Rotation2d::fromDegrees(45));
    Pose2d k(Translation2d(150, 0), Rotation2d::fromDegrees(270));
    Pose2d l(Translation2d(150, -50), Rotation2d::fromDegrees(270));

    vector<QuinticHermiteSpline> splines2;
    splines2.push_back(QuinticHermiteSpline(h, i));
    splines2.push_back(QuinticHermiteSpline(i, j));
    splines2.push_back(QuinticHermiteSpline(j, k));
    splines2.push_back(QuinticHermiteSpline(k, l));

    start_time = std::chrono::high_resolution_clock::now();
    double interVal = QuinticHermiteSpline::optimizeSpline(splines2);
    // cout << "DCurv2 Val: " << interVal << std::endl;
    ASSERT_TRUE(interVal < 0.05);
    ASSERT_NEAR(splines2[0].getCurvature(1.0), 0.0, kTestEps);
    ASSERT_NEAR(splines2[2].getCurvature(1.0), 0.0, kTestEps);
    cout << "Optimization time (us): " << (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start_time).count() / 1000) << std::endl;
}