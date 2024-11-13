#include "timsort.hpp"
#include <iostream>
#include <list>
#include <vector>

int main()
{
    std::list<int> data = {5, 2, 9, 1, 5, 6};

    // Output iterator can be back_inserter to collect sorted results
    std::vector<int> sorted_data;
    timsort::timsort(data.begin(), data.end(), std::back_inserter(sorted_data));

    for (int num : sorted_data)
    {
        std::cout << num << ' ';
    }
    return 0;
}
