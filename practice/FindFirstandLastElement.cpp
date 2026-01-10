// System includes
#include <algorithm>
#include <vector>

// Project includes
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ranges.h>

class Solution
{
    public: 
    // constructor
    Solution(){};

    ~Solution() = default;

    Solution(Solution& copy_constructor) = delete;
    Solution(Solution&& move_constructor) = delete;

    Solution operator=(Solution& copy_assignment) = delete;
    Solution operator=(Solution&& move_assignment) = delete;

    // find the starting and ending position of a given target value.
    // param[in] vector<int> searchable range
    // param[in] int target value
    // param[out] vector<int> lower and upper bound
    std::vector<int> searchRange(std::vector<int>& number_range, int target)
    {
        int lower_target_index = 
            std::lower_bound(number_range.begin(), number_range.end(),target) - number_range.begin();

        int upper_target_inded = 
            std::upper_bound(number_range.begin(), number_range.end(),target) - number_range.begin();

        if(lower_target_index == upper_target_inded)
        {
            // target not present
            return {-1, -1};
        }
        
        // Since rightIndex points to one past the last occurrence, we need to subtract 1.
        return {lower_target_index, upper_target_inded - 1};
    }
};


int main()
{
    spdlog::set_level(spdlog::level::debug);

    return 0;
}