#define IGNORE_IMPLEMENTATION
#include "main.cpp"
#include "gtest/gtest.h"

TEST(Compute, find_max){
    std::vector<int> array{5, 3, 2};
    std::vector<std::vector<int>> queries{ 
        std::vector<int>{1, 2},
        std::vector<int>{2, 3},
        std::vector<int>{1, 3}
    };

    Compute compute(&array, &queries);
    EXPECT_EQ(compute.find_max(), 25);
}


