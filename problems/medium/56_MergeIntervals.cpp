/*
Given an array of intervals where intervals[i] = [starti, endi],
merge all overlapping intervals, and return an array of the non-overlapping 
intervals that cover all the intervals in the input.

Example 1:
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].

Example 2:
Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.


Constraints:
    1 <= intervals.length <= 104
    intervals[i].length == 2
    0 <= starti <= endi <= 104
*/
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> mergeOverlap(std::vector<std::vector<int>> input)
{
    int interval_size = input.size();

    std::sort(input.begin(), input.end());
    std::vector<std::vector<int>> reponse;

    // initialize first element
    reponse.push_back(input[0]);

    for(int i = 1; i < interval_size; ++i)
    {
        // If the current interval does not overlap with the last interval in the result,
        // then simply add the current interval to the result
        if (reponse.back()[1] < input[i][0]) {
            reponse.push_back(input[i]);
        } else {
            // If there is an overlap, merge the current interval with the last interval
            // in the result by updating the end time to the maximum end time seen
            reponse.back()[1] = std::max(reponse.back()[1], input[i][1]);
        }
    }
    return reponse;
}

int main() {
    std::vector<std::vector<int>> input = {{7, 8}, {1, 5}, {2, 4}, {4, 6}};
    std::vector<std::vector<int>> answer = mergeOverlap(input);

    for (auto interval : answer)
        std::cout << interval[0] << " " << interval[1] << std::endl;

    return 0;
}