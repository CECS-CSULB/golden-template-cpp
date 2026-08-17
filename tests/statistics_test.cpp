#include <array>

#include <gtest/gtest.h>

#include "statistics.h"

TEST(MeanTest, FindsMeanOfConsecutiveValues) {
    std::array<int, 10> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    EXPECT_DOUBLE_EQ(mean(data), 5.5);
}

TEST(MeanTest, FindsMeanWithNegativeValues) {
    std::array<int, 10> data = {-10, -8, -6, -4, -2, 2, 4, 6, 8, 10};

    EXPECT_DOUBLE_EQ(mean(data), 0.0);
}

TEST(MedianTest, FindsMedianOfUnsortedValues) {
    std::array<int, 10> data = {10, 2, 8, 4, 6, 1, 9, 3, 7, 5};

    EXPECT_DOUBLE_EQ(median(data), 5.5);
}

TEST(MedianTest, FindsMedianWithRepeatedValues) {
    std::array<int, 10> data = {8, 3, 3, 1, 8, 3, 5, 3, 9, 3};

    EXPECT_DOUBLE_EQ(median(data), 3.0);
}

TEST(MedianTest, DoesNotChangeTheInputArray) {
    std::array<int, 10> data = {10, 2, 8, 4, 6, 1, 9, 3, 7, 5};
    std::array<int, 10> original_data = data;

    median(data);

    EXPECT_EQ(data, original_data);
}
