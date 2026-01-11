/*
https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/description/
Given an array of integers nums sorted in non-decreasing order, find the
starting and ending position of a given target value. If target is not found in
the array, return [-1, -1]. You must write an algorithm with O(log n) runtime
complexity.

Example 1:
Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]

Example 2:
Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]

Example 3:
Input: nums = [], target = 0
Output: [-1,-1]
*/

// System includes
#include <algorithm>
#include <vector>

// Project includes
#include <spdlog/fmt/ranges.h>
#include <spdlog/spdlog.h>

class Solution {
public:
  // constructor
  Solution() {};

  ~Solution() = default;

  Solution(Solution &copy_constructor) = delete;
  Solution(Solution &&move_constructor) = delete;

  Solution operator=(Solution &copy_assignment) = delete;
  Solution operator=(Solution &&move_assignment) = delete;

  // find the starting and ending position of a given target value.
  // param[in] vector<int> searchable range
  // param[in] int target value
  // param[out] vector<int> lower and upper bound
  std::vector<int> searchRange(std::vector<int> &number_range, int target) {
    int lower_target_index =
        std::lower_bound(number_range.begin(), number_range.end(), target) -
        number_range.begin();

    int upper_target_inded =
        std::upper_bound(number_range.begin(), number_range.end(), target) -
        number_range.begin();

    if (lower_target_index == upper_target_inded) {
      // target not present
      return {-1, -1};
    }

    // Since rightIndex points to one past the last occurrence, we need to
    // subtract 1.
    return {lower_target_index, upper_target_inded - 1};
  }
};

int main() {
  spdlog::set_level(spdlog::level::debug);

  return 0;
}