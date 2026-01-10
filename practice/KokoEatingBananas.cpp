// System includes
#include <vector>
#include <limits.h>

// Project includes
#include <spdlog/spdlog.h>


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

    // bananas-per-hour eating speed
    // param[in] vector<int> banana pile 
    // param[in] int hours
    // param[out] int bananas-per-hour
    int bananasPerHous(std::vector<int> banana_piles, int allowed_hours)
    {
        // left node
        int minimum_speed = 1;
        // right node
        int maximum_speed = 1e9;
        
        // binary search method
        while(minimum_speed < maximum_speed)
        {
            // mid point
            int average_speed = minimum_speed + (maximum_speed - minimum_speed) / 2;
            // speed variable
            int bananas_per_hour = 0;

            // find the average eating speed
            for(int& pile : banana_piles)
            {
                bananas_per_hour += (pile + average_speed -1) / average_speed;
            }

            if(bananas_per_hour <= allowed_hours)
            {
                // we finished the banana piles within the time
                maximum_speed = average_speed;
            }
            else 
            {
                // wasn't able to finish the bananas within the time
                minimum_speed = average_speed + 1;
            }
        }
        // Exit the while loop.
        // minimum_speed no longer smaller than maximum_spedd
        return minimum_speed;
    }
};


int main()
{
    spdlog::set_level(spdlog::level::debug);

    Solution computer = Solution();

    std::vector<int> pileA{3,6,7,11};           // h = 8      output = 4
    std::vector<int> pileB{30,11,23,4,20};      // h = 5      output = 30
    std::vector<int> pileC{30,11,23,4,20};      // h = 6      output = 23

    spdlog::info("First Pile: {}", computer.bananasPerHous(pileA, 8));
    spdlog::info("Second Pile: {}", computer.bananasPerHous(pileB, 5));
    spdlog::info("Third Pile: {}", computer.bananasPerHous(pileC, 6));
    return 0;
}