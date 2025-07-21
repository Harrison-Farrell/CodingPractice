/*
Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. 
The guards have gone and will come back in h hours. Koko can decide her bananas-per-hour 
eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile.
If the pile has less than k bananas, she eats all of them instead and will not eat
any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer k such that she can eat all the bananas within h hours.

Example 1:
Input: piles = [3,6,7,11], h = 8
Output: 4

Example 2:
Input: piles = [30,11,23,4,20], h = 5
Output: 30

Example 3:
Input: piles = [30,11,23,4,20], h = 6
Output: 23

Constraints:
    1 <= piles.length <= 10^4
    piles.length <= h <= 10^9
    1 <= piles[i] <= 10^9
*/

#include <vector> // Include the vector library

class Solution {
public:
    // The function minEatingSpeed calculates the minimum speed at which 
    // all bananas in the piles can be eaten within 'h' hours.
    // Parameters:
    // piles: A vector of integers representing the number of bananas in each pile.
    // h: The total number of hours within which all bananas must be eaten.
    // Returns:
    // An integer representing the minimum eating speed (bananas per hour).

    int minEatingSpeed(std::vector<int>& piles, int h) {
        int left = 1; // Minimum possible eating speed (cannot be less than 1)
        int right = 1e9; // A large upper bound for the maximum eating speed.

      
        // Perform a binary search between the range [left, right]
        while (left < right) {
            int mid = left + (right - left) / 2; // Prevents overflow
            int hoursSpent = 0; // Initialize the hours spent to 0
          
            // Calculate the total number of hours it would take at the current speed 'mid'
            for (int pile : piles) {
                // The number of hours spent on each pile is the ceil of pile/mid
                // (pile + mid - 1) / mid is an efficient way to calculate ceil(pile/mid)
                hoursSpent += (pile + mid - 1) / mid;
            }
          
            // If the current speed 'mid' requires less than or equal to 'h' hours,
            // it is a potential solution and we try to find a smaller one.
            if (hoursSpent <= h) {
                right = mid;
            } else { 
                // If the current speed 'mid' requires more than 'h' hours,
                // it is not a valid solution and we must try a larger speed.
                left = mid + 1;
            }
        }
        // 'left' is now the minimum speed at which Koko can eat all the bananas within 'h' hours.
        return left;
    }
};