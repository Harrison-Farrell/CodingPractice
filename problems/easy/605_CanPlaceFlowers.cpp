/*
You have a long flowerbed in which some of the plots are planted, and some are not. 
However, flowers cannot be planted in adjacent plots.

Given an integer array flowerbed containing 0's and 1's, where 0 means empty and 1 means not empty, 
and an integer n, return true if n new flowers can be planted in the flowerbed without violating the no-adjacent-flowers rule and false otherwise.

 
Example 1:
Input: flowerbed = [1,0,0,0,1], n = 1
Output: true

Example 2:
Input: flowerbed = [1,0,0,0,1], n = 2
Output: false

 
Constraints:
    1 <= flowerbed.length <= 2 * 104
    flowerbed[i] is 0 or 1.
    There are no two adjacent flowers in flowerbed.
    0 <= n <= flowerbed.length

*/

#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) 
    {
        int flowerbedSize = flowerbed.size(); // Size of the flowerbed.

        // Iterate through the flowerbed to find valid spots to plant flowers.
        for (int i = 0; i < flowerbedSize; ++i) {
            // Check the left neighbor (if i is 0, left neighbor is considered empty).
            int left = (i == 0) ? 0 : flowerbed[i - 1];
            // Check the right neighbor (if i is the last element, right neighbor is considered empty).
            int right = (i == flowerbedSize - 1) ? 0 : flowerbed[i + 1];

            // If both neighbors and current position are empty, we can plant a flower here.
            if (left + flowerbed[i] + right == 0) {
                flowerbed[i] = 1; // Plant a flower.
                --n; // Decrease the count of flowers needed to plant.
            }
        }

        // If n is less than or equal to 0, all flowers can be planted.
        return n <= 0;

    }
};



int main(int argc, char** argv)
{
    return 0;
}