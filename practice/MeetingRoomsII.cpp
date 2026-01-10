// System includes
#include <vector>
#include <algorithm>
#include <map>

// Project includes
#include <spdlog/spdlog.h>

class Interval
{
    public: 

        int start;
        int end;

        Interval(int start, int end) {
            this->start = start;
            this->end = end;
        }
};

// Three, Five, Zero
class Solution
{
    public:
        // constructor
        Solution(){};

        ~Solution() = default;

        Solution(Solution& copy_constructor) = delete;
        Solution operator=(Solution& copy_assignment) = delete;

        Solution(Solution&& move_constructor) = delete;
        Solution operator=(Solution&& move_assignment) = delete;
        
        // minimum number of days required to schedule all meetings without any conflicts.
        // param[in] vector of intervals
        // param[out] minimum number of day
        int minMeetingRooms(std::vector<Interval>& intervals)
        {
            // possible time slots in accordance to the constraints
            int slots = 1000000;
            std::vector<int> time_slots(slots, 0);

            if(intervals.empty())
            {
                return 0;
            }

            // ordered map of <Start time : End time>
            std::map<int, int> ordered_meetings;
            for(Interval& meeting : intervals)
            {
                ordered_meetings.emplace(meeting.start, meeting.end);
                spdlog::debug("Emplace [key:value]\t[{}:{}]", meeting.start, meeting.end);
            }

            for(auto const& [start_time, end_time] : ordered_meetings)
            {
                spdlog::debug("Add Meeting: {}:{}", start_time, end_time);
                // The room is in use
                ++time_slots[start_time];
                // THe room is free
                --time_slots[end_time];
            }

            // sum the room usages, capturing the overlaps
            for(int i = 0; i < slots -1; ++i)
            {
                time_slots[i + 1] += time_slots[i];
            }

            // dereference iterator, return the maximum value
            return  *std::max_element(time_slots.begin(), time_slots.end());
        }

};


int main(int argc, char** argv)
{
    spdlog::set_level(spdlog::level::debug);

    std::vector<Interval> meetings;
    meetings.push_back(Interval(0,40));
    meetings.push_back(Interval(5,10));
    meetings.push_back(Interval(15,20));
   
    Solution comupter = Solution();

    spdlog::info("minimum number of days: {}", comupter.minMeetingRooms(meetings));

    return 0;
}