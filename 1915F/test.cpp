#define IGNORE_IMPLEMENTATION
#include "main.cpp"
#include "gtest/gtest.h"

TEST(Greeting, check_1)
{
    std::vector<std::vector<int>> vectors {
        {2, 3},
        {1, 4}
    };

    int result = Greeting(vectors).greeting_count();
    EXPECT_EQ(result , 1);
}

TEST(Greeting, check_2)
{
    std::vector<std::vector<int>> vectors {
        {2, 6},
        {4, 5},
        {1, 8},
        {7, 10},
        {-2, 100}
    };

    int result = Greeting(vectors).greeting_count();
    EXPECT_EQ(result , 9);
}

TEST(Greeting, check_3)
{
    std::vector<std::vector<int>> vectors {
        {-10, 10},
        {-5, 5},
        {-12, 12},
        {-13, 13}
    };

    int result = Greeting(vectors).greeting_count();
    EXPECT_EQ(result , 6);
}

TEST(Greeting, check_4)
{
    std::vector<std::vector<int>> vectors {
        {-4, 9},
        {-2, 5},
        {3, 4},
        {6, 7},
        {8, 10}
    };

    int result = Greeting(vectors).greeting_count();
    EXPECT_EQ(result , 4);
}

TEST(Greeting, check_5)
{
    std::vector<std::vector<int>> vectors {
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 8}
    };

    int result = Greeting(vectors).greeting_count();
    EXPECT_EQ(result , 0);
}