#define IGNORE_IMPLEMENTATION
#include "main.cpp"
#include "gtest/gtest.h"

TEST(Stringer, find_winner_1){
    std::string input_s{"aba"};

    Stringer stringer(input_s);
    int match = 0;
    while(!stringer.check_paradrome())
    {
        stringer.reduce_achar();
        ++match;
    }

    EXPECT_EQ(match, 0);
}

TEST(Stringer, find_winner_2){
    std::string input_s{"abca"};

    Stringer stringer(input_s);
    int match = 0;
    while(!stringer.check_paradrome())
    {
        stringer.reduce_achar();
        ++match;
    }

    EXPECT_EQ(match, 3);
}