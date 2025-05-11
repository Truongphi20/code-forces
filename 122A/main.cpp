#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> determine_i_range(int target_number)
{
    std::vector<int> i_range;
    int sum_ten_i = 0;
    for (int i=0; sum_ten_i <= target_number; i++)
    {
        i_range.emplace_back(i);
        sum_ten_i += std::pow(10,i);
    }

    return i_range;
}

bool checkLuckey(int number)
{
    int process_number = number;
    while (process_number > 1)
    {
        int tail_number = process_number % 10;
        if (tail_number != 4 && tail_number != 7)
        {
            return false;
        }
        process_number /= 10;
    }

    return true;
}

bool checkNumber(int target_number, int i)
{
    int decimal_sum{0};
    for (int counter=0; counter <= i; ++counter)
    {
        decimal_sum += std::pow(10, counter);
    }

    int upper_fence{ (int)std::floor(static_cast<float>(target_number)/(4*decimal_sum)) };
    int downer_fence{ (int)std::ceil(static_cast<float>(target_number)/(7*decimal_sum)) };

    for (int counter=downer_fence; counter <= upper_fence; ++counter)
    {
        if (target_number % counter == 0 && checkLuckey(target_number / counter))
        {
            return true;
        }
    }

    return false;

    
}

int main()
{
    int target_number;
    std::cin >> target_number;

    std::vector<int> i_range { determine_i_range(target_number) };

    for (const int &i: i_range)
    {
        if (checkNumber(target_number, i)){
            std::cout << "YES" << '\n';
            return 0;
        }
    }

    std::cout << "NO" << '\n';

    return 0;
}