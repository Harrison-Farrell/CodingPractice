/*
https://leetcode.com/problems/koko-eating-bananas/description/
Koko loves to eat bananas. There are n piles of bananas, the ith pile has
piles[i] bananas. The guards have gone and will come back in h hours.

Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses
some pile of bananas and eats k bananas from that pile. If the pile has less
than k bananas, she eats all of them instead and will not eat any more bananas
during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before
the guards return.

Return the minimum integer k such that she can eat all the bananas within h
hours.

Example 1:
Input: piles = [3,6,7,11], h = 8
Output: 4

Example 2:
Input: piles = [30,11,23,4,20], h = 5
Output: 30

Example 3:
Input: piles = [30,11,23,4,20], h = 6
Output: 23
*/
// System includes
#include <limits.h>
#include <vector>

// Project includes
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

  // bananas-per-hour eating speed
  // param[in] vector<int> banana pile
  // param[in] int hours
  // param[out] int bananas-per-hour
  int bananasPerHous(std::vector<int> banana_piles, int allowed_hours) {
    // left node
    int minimum_speed = 1;
    // right node
    int maximum_speed = 1e9;

    // binary search method
    while (minimum_speed < maximum_speed) {
      // mid point
      int average_speed = minimum_speed + (maximum_speed - minimum_speed) / 2;
      // speed variable
      int bananas_per_hour = 0;

      // find the average eating speed
      for (int &pile : banana_piles) {
        bananas_per_hour += (pile + average_speed - 1) / average_speed;
      }

      if (bananas_per_hour <= allowed_hours) {
        // we finished the banana piles within the time
        maximum_speed = average_speed;
      } else {
        // wasn't able to finish the bananas within the time
        minimum_speed = average_speed + 1;
      }
    }
    // Exit the while loop.
    // minimum_speed no longer smaller than maximum_spedd
    return minimum_speed;
  }
};

int main() {
  spdlog::set_level(spdlog::level::debug);

  Solution computer = Solution();

  std::vector<int> pileA{3, 6, 7, 11};       // h = 8      output = 4
  std::vector<int> pileB{30, 11, 23, 4, 20}; // h = 5      output = 30
  std::vector<int> pileC{30, 11, 23, 4, 20}; // h = 6      output = 23

  spdlog::info("First Pile: {}", computer.bananasPerHous(pileA, 8));
  spdlog::info("Second Pile: {}", computer.bananasPerHous(pileB, 5));
  spdlog::info("Third Pile: {}", computer.bananasPerHous(pileC, 6));
  return 0;
}