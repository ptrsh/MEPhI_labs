#include <gtest/gtest.h>
#include "../lib/app.h"

#define ENTER_POSITIVE_RADIUS "3"
#define ENTER_NEGATIVE_RADIUS "-3"
#define SET_RADIUS "1"
#define GET_LENGTH "2"
#define GET_RADIUS_OF_CURVATURE "3"
#define GET_AREA "4"
#define GET_XY "5"
#define GET_EQUATION "6"
#define EXIT "7"

std::string run(std::string commands) {
    testing::internal::CaptureStdout();
    std::cin.rdbuf(std::istringstream(commands).rdbuf());
    App app;
    app.start();
    std::string output = testing::internal::GetCapturedStdout();
    return output;
}

TEST(Nephroid, Initialization) { 
    Nephroid nephroid;
    ASSERT_EQ(nephroid.getArea(), 0.0);
    ASSERT_EQ(nephroid.getLength(), 0.0);
}

TEST(Nephroid, setRadius) { 
    Nephroid nephroid;
    nephroid.setRadius(5.0);
    ASSERT_EQ(nephroid.radius, 5.0);
}

TEST(Nephroid, getRadiusOfCurvature) {
    Nephroid nephroid;
    nephroid.setRadius(5.0);
    ASSERT_NEAR(nephroid.getRadiusOfCurvature(60), 4.57, 0.01);
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

TEST(Application, Init) {
    ASSERT_NO_THROW(App app);
}

TEST(Application, StartAndExit) {
    std::string commands;
    commands += ENTER_POSITIVE_RADIUS;
    commands += "\n";
    commands += EXIT;

    std::string output = run(commands);
    ASSERT_NE(output.find("Menu:"), -1);
}

TEST(Application, EnterInvalidRadius) {
    std::string commands;
    commands += ENTER_NEGATIVE_RADIUS;
    commands += "\n";
    commands += ENTER_POSITIVE_RADIUS;
    commands += "\n";
    commands += EXIT;
    
    std::string output = run(commands);
    ASSERT_NE(output.find("Invalid input! Try again!"), -1);
}

TEST(Application, EnterInvalidCommand) {
    std::string commands;
    commands += ENTER_POSITIVE_RADIUS;
    commands += "\n";
    commands += "-100";
    commands += "\n";
    commands += EXIT;
    
    std::string output = run(commands);
    ASSERT_NE(output.find("Invalid input! Try again!"), -1);
}

TEST(Application, GetLength) {
    std::string commands;
    commands += ENTER_POSITIVE_RADIUS;
    commands += "\n";
    commands += GET_LENGTH;
    commands += "\n";
    commands += EXIT;
    
    std::string output = run(commands);
    ASSERT_NE(output.find("Length: 72"), -1);
}

TEST(Application, GetRadiusOfCurvature) {
    std::string commands;
    commands += ENTER_POSITIVE_RADIUS;
    commands += "\n";
    commands += GET_RADIUS_OF_CURVATURE;
    commands += "\n";
    commands += "30";
    commands += "\n";
    commands += EXIT;
    
    std::string output = run(commands);
    ASSERT_NE(output.find("Radius of curvature: 8.89228"), -1);
}

TEST(Application, GetArea) {
    std::string commands;
    commands += ENTER_POSITIVE_RADIUS;
    commands += "\n";
    commands += GET_AREA;
    commands += "\n";
    commands += EXIT;
    
    std::string output = run(commands);
    ASSERT_NE(output.find("Area: 339.292"), -1);
}

TEST(Application, GetXY) {
    std::string commands;
    commands += ENTER_POSITIVE_RADIUS;
    commands += "\n";
    commands += GET_XY;
    commands += "\n";
    commands += "30";
    commands += "\n";
    commands += EXIT;
    
    std::string output = run(commands);
    ASSERT_NE(output.find("x = 2.732484\ny = -11.574275"), -1);
}

TEST(Application, GetEquation) {
    std::string commands;
    commands += ENTER_POSITIVE_RADIUS;
    commands += "\n";
    commands += GET_EQUATION;
    commands += "\n";
    commands += EXIT;
    
    std::string output = run(commands);
    ASSERT_NE(output.find("Equation: (x^2 + y^2 - 36.000000)^3 = 8748.000000 * y^2"), -1);
}

int main(){
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}