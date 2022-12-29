#include <gtest/gtest.h>
#include "../lib/app.h"

#define ENTER_VECTOR_12345 "5\n1\n2\n3\n4\n5"
#define ENTER_NEW_VECTOR "1"
#define ENTER_TWO_VECTORS_AND_ADD_UP "2"
#define ENTER_TWO_VECTORS_AND_SUBSTRUCT "3"
#define ENTER_TWO_VECTORS_AND_MULTIPLY "4"
#define PRINT_VECTOR "5"
#define GET_NORM "6"
#define EXIT "7"

std::string run(std::string commands) {
    testing::internal::CaptureStdout();
    std::cin.rdbuf(std::istringstream(commands).rdbuf());
    App app;
    app.start();
    std::string output = testing::internal::GetCapturedStdout();
    return output;
}

TEST(Vector, Initialization) { 
    ASSERT_NO_THROW(Vector vector);
}

TEST(Vector, InitializationWithOneNum) { 
    Vector vector(1.0);
    ASSERT_EQ(vector.getNorm(), 1);
}

TEST(Vector, InitializationWithArrayOfNums) { 
    double data[] = {1.0, 2.0, 3.0};
    ASSERT_NO_THROW(Vector(3, data));
}

TEST(Vector, GetNorm) { 
    double data[] = {1.0, 2.0, -3.0, 4.0, 10000.0, -10000.1};
    Vector vector(6, data);
    ASSERT_EQ(vector.getNorm(), -10000.1);
}

TEST(Vector, AdditionResult) { 
    double data1[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    Vector vector1(6, data1);
    double data2[] = {100.0, 200.0, -3.0, 400.0, 500.0, 600.0};
    Vector vector2(6, data2);

    ASSERT_EQ(vector1.size, vector2.size);
    Vector vector3 = vector1 + vector2;
    double result[] = {101.0, 202.0, 0.0, 404.0, 505.0, 606.0};

    for (int i = 0; i < 6; i++) EXPECT_EQ(vector3.data[i], result[i]);
}

TEST(Vector, SubstitutionResult) { 
    double data1[] = {100.0, 200.0, -3.0, 400.0, 500.0, 600.0};
    Vector vector1(6, data1);
    double data2[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    Vector vector2(6, data2);

    ASSERT_EQ(vector1.size, vector2.size);
    Vector vector3 = vector1 - vector2;
    double result[] = {-99.0, -198.0, 6.0, -396.0, -495.0, -594.0};

    for (int i = 0; i < 6; i++) EXPECT_EQ(vector3.data[i], result[i]);
}     

TEST(Vector, MultiplicationResult) { 
    double data1[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    Vector vector1(6, data1);
    double data2[] = {100.0, 200.0, -3.0, 400.0, 500.0, 600.0};
    Vector vector2(6, data2);

    ASSERT_EQ(vector1.size, vector2.size);

    double result = vector1 * vector2;
    ASSERT_EQ(result, 8191.0);
}

TEST(Vector, Equal) { 
    Vector vector1(6);
    Vector vector2 = vector1;

    ASSERT_EQ(vector1.size, vector2.size);
    for (int i = 0; i < vector1.size; i++) EXPECT_EQ(vector1[i], vector2[i]);
}

TEST(Vector, AdditionDifferentIndexesException) {
    double data1[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    Vector vector1(5, data1);
    double data2[] = {100.0, 200.0, -3.0, 400.0, 500.0, 600.0};
    Vector vector2(6, data2);
    ASSERT_THROW(vector1 + vector2, Vector::DifferentIndexesException);
}

TEST(Vector, SubstitutionDifferentIndexesException) {
    double data1[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    Vector vector1(5, data1);
    double data2[] = {100.0, 200.0, -3.0, 400.0, 500.0, 600.0};
    Vector vector2(6, data2);
    ASSERT_THROW(vector1 - vector2, Vector::DifferentIndexesException);
}

TEST(Vector, MultiplicationDifferentIndexesException) {
    double data1[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    Vector vector1(5, data1);
    double data2[] = {100.0, 200.0, -3.0, 400.0, 500.0, 600.0};
    Vector vector2(6, data2);
    ASSERT_THROW(vector1 * vector2, Vector::DifferentIndexesException);
}

TEST(Application, Initialization) {
    ASSERT_NO_THROW(App app);
}

TEST(Application, StartAndExit) {
    std::string commands;
    commands += ENTER_VECTOR_12345;
    commands += "\n";
    commands += EXIT;

    std::string output = run(commands);
    ASSERT_NE(output.find("Menu:"), -1);
}

TEST(Application, PrintVector) {
    std::string commands;
    commands += ENTER_VECTOR_12345;
    commands += "\n";
    commands += PRINT_VECTOR;
    commands += "\n";
    commands += EXIT;
    std::string output = run(commands);
    ASSERT_NE(output.find("Vector:\n1 2 3 4 5"), -1);
}

TEST(Application, GetNorm) {
    std::string commands;
    commands += ENTER_VECTOR_12345;
    commands += "\n";
    commands += GET_NORM;
    commands += "\n";
    commands += EXIT;
    std::string output = run(commands);
    ASSERT_NE(output.find("Norm of vector:\n5"), -1);
}

TEST(Application, EnterInvalidCommand) {
    std::string commands;
    commands += ENTER_VECTOR_12345;
    commands += "\n";
    commands += "-100";
    commands += "\n";
    commands += "-100";
    commands += "\n";
    commands += EXIT;

    std::string output = run(commands);
    ASSERT_NE(output.find("Invalid input! Try again!"), -1);
}

int main(){
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}