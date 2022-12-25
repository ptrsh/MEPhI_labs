#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../lib/app.h"

TEST(Vector, Initialization) { 
    ASSERT_NO_FATAL_FAILURE(GroupsTable Group{});
}

int main(){
  ::testing::InitGoogleTest();
  ::testing::InitGoogleMock();
  return RUN_ALL_TESTS();
}