// System includes
#include <vector>
#include <algorithm>

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

    // merge all overlapping intervals,
    // param[in] vector<vector<int>> meeting slots [start, end] times
    // param[out] vector<vector<int>> merged intervals
    std::vector<std::vector<int>> mergeIntervals(std::vector<std::vector<int>>& meeting_intervals)
    {
        // sort meetings by start times
        std::sort(meeting_intervals.begin(), meeting_intervals.end());

        std::vector<std::vector<int>> merged_meetings;
        // The first is already the first time
        merged_meetings.push_back(meeting_intervals[0]);

        
        // iterate through all the meetings
        // start from the second elment. 
        for(int i = 1; i < meeting_intervals.size(); ++i)
        {
            // compare current finish time against next start time
            if(merged_meetings.back()[1] < meeting_intervals[i][0])
            {
                merged_meetings.push_back(meeting_intervals[i]);
            }
            else
            {
                merged_meetings.back()[1] = std::max(merged_meetings.back()[1], meeting_intervals[i][1]);
            }
        }
        return merged_meetings;
    }
};

int main()
{
    Solution computer = Solution();
    std::vector<std::vector<int>> intervals = {{1,3},{2,6},{8,10},{15,18}};

     // expected output: [[1,6],[8,10],[15,18]]
    spdlog::info("Merged: {}", computer.mergeIntervals(intervals));    
}