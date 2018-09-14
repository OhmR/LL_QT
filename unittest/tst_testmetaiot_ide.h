#pragma once

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
//#include "increment.h"

using namespace testing;

TEST(testMetaIOT_IDE, HelloWorldTest) { EXPECT_EQ(1, 2); }

// TEST(testMetaIOT_IDE, testIncrement) {
//  increment tObj;
//  int a = tObj.getIncrement(5);
//  EXPECT_EQ(a, 6);
//}
