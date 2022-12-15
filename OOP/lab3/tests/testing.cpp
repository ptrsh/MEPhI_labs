#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../lib/app.h"

TEST(Vector, Initialization) { 
    ASSERT_NO_FATAL_FAILURE(Vector vector);
}

TEST(Vector, InitializationWithOneNum) { 
    ASSERT_NO_FATAL_FAILURE(Vector vector(1.0));
}

TEST(Vector, InitializationWithArrayOfNums) { 
    double data[] = {1.0, 2.0, 3.0};
    ASSERT_NO_FATAL_FAILURE(Vector(3, data));
}

TEST(Vector, GetNorm) { 
    double data[] = {1.0, 2.0, -3.0, 4.0, 10000.0, -10000.1};
    Vector vector(6, data);
    ASSERT_EQ(vector.getNorm(), -10000.1);
}


TEST(Vector, Addition) { 
    double data1[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    Vector vector1(6, data1);
    double data2[] = {100.0, 200.0, -3.0, 400.0, 500.0, 600.0};
    Vector vector2(6, data2);

    ASSERT_EQ(vector1.size, vector2.size);
    Vector vector3 = vector1 + vector2;
    double result[] = {101.0, 202.0, 0.0, 404.0, 505.0, 606.0};

    for (int i = 0; i < 6; i++) EXPECT_EQ(vector3.data[i], result[i]);
    

}

TEST(Vector, Substitution) { 
    double data1[] = {100.0, 200.0, -3.0, 400.0, 500.0, 600.0};
    Vector vector1(6, data1);
    double data2[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    Vector vector2(6, data2);

    ASSERT_EQ(vector1.size, vector2.size);
    Vector vector3 = vector1 - vector2;
    double result[] = {-99.0, -198.0, 6.0, -396.0, -495.0, -594.0};

    for (int i = 0; i < 6; i++) EXPECT_EQ(vector3.data[i], result[i]);


}     

TEST(Vector, Multiplication) { 
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

int main(){
  ::testing::InitGoogleTest();
  ::testing::InitGoogleMock();
  return RUN_ALL_TESTS();
}