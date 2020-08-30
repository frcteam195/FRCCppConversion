#include <vector>
#include <iostream>

#include "gtest/gtest.h"
#include "physics/DriveCharacterization.hpp"

TEST(DriveCharacterizationTest, DetermineOutput) { 
    double kTestEps = 1e-5;
    std::cout << "Running sqrt test!" << std::endl;
    EXPECT_EQ(1, 1);
    std::vector<ck::physics::VelocityDataPoint> velocityData;
    std::vector<ck::physics::AccelerationDataPoint> accelData;
    velocityData.push_back(ck::physics::VelocityDataPoint {1, 10});
    velocityData.push_back(ck::physics::VelocityDataPoint {2, 12});
    velocityData.push_back(ck::physics::VelocityDataPoint {3, 15});
    velocityData.push_back(ck::physics::VelocityDataPoint {4, 20});
    
    accelData.push_back(ck::physics::AccelerationDataPoint {1, 10, 20});
    accelData.push_back(ck::physics::AccelerationDataPoint {2, 12, 60});
    accelData.push_back(ck::physics::AccelerationDataPoint {3, 15, 120});
    accelData.push_back(ck::physics::AccelerationDataPoint {4, 20, 400});
    ck::physics::CharacterizationConstants cc = ck::physics::DriveCharacterization::characterizeDrive(velocityData, accelData);
    std::cout << cc << std::endl;
    ASSERT_NEAR(cc.ks, 6, kTestEps);
    ASSERT_NEAR(cc.kv, 3.3, kTestEps);
    ASSERT_NEAR(cc.ka, 0.002149321267, kTestEps);
}