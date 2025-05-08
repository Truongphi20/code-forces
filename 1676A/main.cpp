#include <iostream>


int sum_of_digit(int number)
{
    int first = number / 100;
    int second = number / 10 % 10;
    int third = number % 10;

    int sum = first + second + third;
    return sum;
}

int main () 
{

    int number_of_seri;
    std::cin >> number_of_seri;

    int number_list[number_of_seri];
    for (int i=0; i < number_of_seri; ++i)
    {
        std::cin >> number_list[i];
    }
    
    
    for (const int &seri: number_list)
    {
        int ahead = seri / 1000;
        int backward = seri % 1000;

        if (sum_of_digit(ahead) == sum_of_digit(backward))
        {
            std::cout << "YES" << '\n';
        } else {
            std::cout << "NO" << '\n';
        }
    }
    return 0;
}