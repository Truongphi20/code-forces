#include <iostream>

int main (){

    int number_of_drink;
    std::cin >> number_of_drink;


    float percentiles[number_of_drink];
    float sum{0};
    for (int i = 0; i < number_of_drink; ++i){
        std::cin >> percentiles[i];
        sum += percentiles[i];
    }

    float total_percentile;

    total_percentile = sum / number_of_drink;

    std::cout << total_percentile << '\n';

}