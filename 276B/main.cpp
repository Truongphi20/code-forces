#ifndef COMPUTE_HPP
#define COMPUTE_HPP

#include <string>
#include <iostream>
#include <unordered_map>

class Stringer{
    public:
    Stringer(std::string &input_s);
    bool check_paradrome();
    int count_odd();
    void reduce_achar();

    private:
    std::string &input_s;
    std::unordered_map<char, int> tracer;
    size_t length;
};

#endif


#ifndef IGNORE_IMPLEMENTATION

    Stringer::Stringer(std::string &input_s):
    input_s(input_s)
    {
        this->length = input_s.size();
        for (char &character: input_s)
        {
            this->tracer[character] += 1;
        }
    }

    int Stringer::count_odd()
    {
        int count = 0;
        for (auto &[character, count_value]: this->tracer)
        {
            if(count_value % 2 == 1) ++count;
        }

        return count;
    }

    bool Stringer::check_paradrome()
    {
        bool result{false};
        int count = this->count_odd();
        if (count > 1) result = false;
        if ((count == 1) && (this->length %2 == 1)) result = true;
        if (count == 0) result = true;
        return result;
    }

    void Stringer::reduce_achar()
    {
        int *image_count;
        for (auto &[character, count_value]: this->tracer)
        {
            if(count_value % 2 == 0 && count_value != 0){
                --count_value;
                --this->length;
                return;
            }else if (count_value == 1){
                image_count = &count_value;
            }
        }

        --(*image_count);
        --this->length;
    }

#endif


#ifndef IGNORE_MAIN

int main (){
    std::string input_s;
    std::cin >> input_s;

    Stringer stringer(input_s);
    int match = 0;
    while(!stringer.check_paradrome())
    {
        stringer.reduce_achar();
        ++match;
    }

    if (match % 2 == 0){
        std::cout << "First" << "\n";
    } else {
        std::cout << "Second" << "\n";
    }

}

#endif
