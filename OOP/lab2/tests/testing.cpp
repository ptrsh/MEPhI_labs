#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../lib/app.h"

TEST(Nephroid, Initialization) { 
    Nephroid nephroid;
    ASSERT_EQ(nephroid.getArea(), 0.0);
    ASSERT_EQ(nephroid.getLength(), 0.0);
}

TEST(Nephroid, setRadius) { 
    Nephroid nephroid;
    nephroid.setRadius(5.0);
    ASSERT_FLOAT_EQ(nephroid.getLength(), 120.0);
}

TEST(Nephroid, getRadiusOfCurvature) {
    Nephroid nephroid;
    nephroid.setRadius(5.0);
    ASSERT_EQ(nephroid.getRadiusOfCurvature(60), 4);
}

TEST(Nephroid, getLength) {
    Nephroid nephroid;
    nephroid.setRadius(10.0);
    ASSERT_FLOAT_EQ(nephroid.getLength(), 240.0);
}

TEST(Nephroid, getArea) {
    Nephroid nephroid;
    nephroid.setRadius(10.0);
    ASSERT_NEAR(nephroid.getArea(), 3769.91, 0.01);
}

TEST(Nephroid, getXY) {
    Nephroid nephroid;
    nephroid.setRadius(15.0);
    EXPECT_EQ(nephroid.getXY(0), "x = 30.000000\ny = 0.000000\n");
}

TEST(Nephroid, getEquation) {
    Nephroid nephroid;
    nephroid.setRadius(5.0);
    EXPECT_EQ(nephroid.getEquation(), "(x^2 + y^2 - 100.000000)^3 = 67500.000000 * y^2");
}

TEST(Nephroid, InvalidRadiusException) {
    Nephroid nephroid;
    ASSERT_THROW(nephroid.setRadius(-1), Nephroid::InvalidRadiusException);
}

TEST(Nephroid, InvalidParameterException) {
    Nephroid nephroid;
    ASSERT_THROW(nephroid.getRadiusOfCurvature(-100), Nephroid::InvalidParameterException);
}

int main(){
  ::testing::InitGoogleTest();
  ::testing::InitGoogleMock();
  return RUN_ALL_TESTS();
}