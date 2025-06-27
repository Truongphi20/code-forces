#ifndef COMPUTE_HPP
#define COMPUTE_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Compute{
    public:
    Compute(std::vector<int>*, std::vector<std::vector<int>>*);
    int find_max();
    std::vector<std::pair<int, int>> sort_map();

    private:
    std::vector<int>* p_array;
    std::vector<std::vector<int>>* p_queries; 
    std::unordered_map<int, int> statistis;

};
#endif

#ifndef IGNORE_IMPLEMENTATION
Compute::Compute(std::vector<int>* p_array, std::vector<std::vector<int>>* p_queries):
    p_array(p_array),
    p_queries(p_queries)
{
    std::sort(this->p_array->begin(), this->p_array->end(), [](int &a, int &b){return a > b;});
}

std::vector<std::pair<int, int>> Compute::sort_map()
{
    std::vector<std::pair<int, int>> sorted_stats(statistis.begin(), statistis.end());
    std::sort(sorted_stats.begin(), sorted_stats.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

    return sorted_stats;
    
}

int Compute::find_max()
{
    // Invoke statistic
    for(const std::vector<int> &query: *(this->p_queries))
    {
        for (int index=query[0]-1; index < query[1]; index++)
        {
            ++this->statistis[index];
        }
    }

    // Sorting
    std::vector<std::pair<int, int>> sorted_stats = this->sort_map();

    // Sum
    int max_sum{0};
    for(int index=0; index<sorted_stats.size(); index++)
    {
        max_sum += (*this->p_array)[index] * sorted_stats[index].second; 
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
