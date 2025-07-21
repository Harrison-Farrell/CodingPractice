/*
Given an array of meeting time interval objects consisting of start and end times 
[[start_1,end_1],[start_2,end_2],...] (start_i < end_i), find the minimum number of days required to schedule all meetings without any conflicts.

Note: (0,8),(8,10) is not considered a conflict at 8.

Example 1:
Input: intervals = [(0,40),(5,10),(15,20)]
Output: 2

Explanation:
day1: (0,40)
day2: (5,10),(15,20)

Example 2:
Input: intervals = [(4,9)]
Output: 1

Constraints:
    0 <= intervals.length <= 500
    0 <= intervals[i].start < intervals[i].end <= 1,000,000
*/

#include <iostream>
#include <algorithm>

#include <vector>
#include <utility>
#include <map>

class Interval {
public:
    int start, end;
    Interval(int start, int end) {
        this->start = start;
        this->end = end;
    }
};

class Solution_SweepLine {
public:
    int minMeetingRooms(std::vector<Interval>& intervals) {
        // create a map of all times. Maps are ordered.
        // ordering my start time.
        std::map<int, int> room_usage;

        for (auto& i : intervals) {
            // increment the usage at the start time
            room_usage[i.start]++;
            // decrement the usage at the end time
            room_usage[i.end]--;
        }

        int running_usage = 0;
        int max_overlaps = 0;
        // Check the room usage for each hour
        for (auto& [key, value] : room_usage) {
            running_usage += value;
            max_overlaps = std::max(max_overlaps, running_usage);
        }
        return max_overlaps;
    }
};

// Time: 1, 2, 3, 4, 5, 6, 7, 8, 9
// Delta: +1 +1, 0 -1, -1, 0, +1, 0, -1
// Occupided: 1, 2, 3, 1, 0, 0, 1, 1, 0,

int main(int argc, char** argv)
{
    Solution_SweepLine answer;

    Interval first(0,40);
    Interval second(5,10);
    Interval third(15,20);
    std::vector<Interval> first_test = {first, second, third};
    std::vector<Interval> second_test = {second};

    std::cout << answer.minMeetingRooms(first_test) << std::endl;      // output is 2
    std::cout << answer.minMeetingRooms({second_test}) << std::endl;   // output is 1
}