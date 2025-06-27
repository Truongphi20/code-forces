#ifndef COMPUTE_HPP
#define COMPUTE_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Compute{
    public:
    Compute(std::vector<int>*, std::vector<std::vector<int>>*);
    int64_t find_max();
    std::vector<std::pair<int, int>> sort_map();

    private:
    std::vector<int>* p_array;
    std::vector<std::vector<int>>* p_queries; 
    std::vector<int> statistis;

};
#endif

#ifndef IGNORE_IMPLEMENTATION
Compute::Compute(std::vector<int>* p_array, std::vector<std::vector<int>>* p_queries):
    p_array(p_array),
    p_queries(p_queries)
{
    this->statistis.resize(this->p_array->size() + 1, 0);
    std::sort(this->p_array->begin(), this->p_array->end(), [](int &a, int &b){return a > b;});
}

int64_t Compute::find_max()
{
    // Invoke statistic
    for(const std::vector<int> &query: *(this->p_queries))
    {
        ++this->statistis[query[0]-1];
        --this->statistis[query[1]];
    }
    // Return to statistic num
    for (int index=1; index < this->statistis.size(); ++index){
        this->statistis[index] += this->statistis[index-1];
    }

    // Sorting
    std::sort(this->statistis.begin(), this->statistis.end(), [](int &a, int &b){return a > b;});

    // Sum
    int64_t max_sum = 0;
    for(int index=0; index < (this->statistis.size() - 1); index++)
    {
        max_sum += static_cast<int64_t>((*this->p_array)[index]) * static_cast<int64_t>(this->statistis[index]); 
    }

    return max_sum;


}
#endif

#ifndef IGNORE_MAIN
int main() {
    // Get inputs
    std::size_t n, q;
    std::cin >> n >> q;
    std::vector<int> array(n);
    std::vector<std::vector<int>> queries(q, std::vector<int>(2)); 
    for (int i=0; i < n; i++)
    {
        std::cin >> array[i];
    }

    for(int i=0; i < q; i++)
    {
        std::cin >> queries[i][0] >> queries[i][1];
    }

    // Compute
    Compute compute(&array, &queries);
    std::cout << compute.find_max();

    return 0;
}
#endif
