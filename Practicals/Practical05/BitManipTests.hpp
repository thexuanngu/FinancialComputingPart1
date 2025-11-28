#ifndef __PRACTICAL05_TEST_HPP__
#define __PRACTICAL05_TEST_HPP__

#include "gtest/gtest.h"
#include "Practical05/Practical05Exercises.hpp"

using exercises::subtract;
using exercises::swap;


TEST(SubtractionTest, ZeroZero){
  EXPECT_EQ(0,subtract(0,0)); // expected vs returned
}

TEST(SubtractionTest, Same){
  for(unsigned int i(0); i<200; i++)
    EXPECT_EQ(0u, subtract(i,i)); // i - i == 0
}

TEST(SubtractionTest, Different){
  for(unsigned int i(0); i<200; i++) {
    for(unsigned int j(0); j<200; j++) {
        EXPECT_EQ(j, subtract(i+j,i)); // (i+j) - i == j
        }
    }
}

TEST(Swapping, ZeroZero) {
    unsigned int a = 0;
    unsigned int b = 0;
    swap(a, b);

    EXPECT_EQ(0, a); // expected vs returned
    EXPECT_EQ(0, b); // expected vs returned
}

TEST(Swapping, Same){
  for(unsigned int i(0); i<200; i++) {
    unsigned int a = i;
    unsigned int b = i;
    swap(a, b);
    
    EXPECT_EQ(i, a);
    EXPECT_EQ(i, b);
  }
}
#endif //PRACTICAL05_TEST_HPP


