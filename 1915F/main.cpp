#ifndef COMPUTE_HPP
#define COMPUTE_HPP
// Decraration
#include <vector>
#include <iostream>

class Greeting {
    public:
    Greeting(std::vector<std::vector<int>> &vectors);
    Greeting& operator=(const Greeting &&other);
    int greeting_count(); 

    private:
    std::vector<std::vector<int>> &vectors;
};
#endif

#ifndef IGNORE_IMPLEMENTATION
// Defination
Greeting::Greeting(std::vector<std::vector<int>> &vectors):
    vectors(vectors)
{}

Greeting& Greeting::operator=(const Greeting &&other)
{

}

int Greeting::greeting_count()
{

}

#endif


#ifndef IGNORE_MAIN
// Main
int main()
{
    // Collect inputs
    int test_case{0};
    std::cin >> test_case;
    std::vector<Greeting> greetings(test_case);
    while(--test_case)
    {
        int vector_num{0};
        std::cin >> vector_num;
        std::vector<std::vector<int>> vectors(vector_num, std::vector<int>{2});
        while(--vector_num)
        {
            std::cin >> vectors[vector_num][0] >> vectors[vector_num][1];
        }

        greetings[test_case] = std::move(Greeting(vectors));
    }

    // Solve
    for (Greeting &greeting: greetings)
    {
        std::cout << greeting.greeting_count();
    }

    return 0;
}

#endif

