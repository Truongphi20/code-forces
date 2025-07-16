#ifndef COMPUTE_HPP
#define COMPUTE_HPP
// Decraration
#include <vector>
#include <iostream>

class Greeting {
    public:
    Greeting(std::vector<std::vector<int>> &vectors);
    Greeting(){};
    Greeting& operator=(const Greeting &&other) noexcept;
    int greeting_count();
    bool check_meeting(std::vector<int> &first_vector, std::vector<int> &second_vector); 

    private:
    std::vector<std::vector<int>> vectors;
};
#endif

#ifndef IGNORE_IMPLEMENTATION
// Defination
Greeting::Greeting(std::vector<std::vector<int>> &vectors):
    vectors(vectors)
{}

Greeting& Greeting::operator=(const Greeting &&other) noexcept
{
    this->vectors = std::move(other.vectors);

    return *this;
}

bool Greeting::check_meeting(std::vector<int> &first_vector, std::vector<int> &second_vector)
{
    bool answer = false;
    int multiple_delta = (first_vector[0] - second_vector[0]) * (first_vector[1] - second_vector[1]);
    if (multiple_delta < 0) 
        answer = true;
    else 
        answer = false;
    
    return answer;
}

int Greeting::greeting_count()
{
    int count{0};
    int64_t first_index = 0;
    int64_t sec_index = 1;
    while (true)
    {
        if (this->check_meeting(this->vectors[first_index], this->vectors[sec_index]))
            ++count;

        if (first_index == this->vectors.size() - 2)
            break;
        
        if (sec_index == this->vectors.size() - 1)
        {
            ++first_index;
            sec_index = first_index;
        }
        
        ++sec_index;
    }

    return count;

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
    for (int t = 0; t < test_case; ++t) {
        int vector_num;
        std::cin >> vector_num;
        std::vector<std::vector<int>> vectors(vector_num, std::vector<int>(2));
        for (int i = 0; i < vector_num; ++i) {
            std::cin >> vectors[i][0] >> vectors[i][1];
        }
        greetings[t] = Greeting(vectors);
    }

    // Solve
    for (Greeting &greeting: greetings)
    {
        std::cout << greeting.greeting_count() << '\n';
    }

    return 0;
}

#endif

