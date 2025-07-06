// Given a string s, find the length of the longest without duplicate characters.
// 
// Example 1:
// Input: s = "abcabcbb"
// Output: 3
// Explanation: The answer is "abc", with the length of 3.
//
// Example 2:
// Input: s = "bbbbb"
// Output: 1
// Explanation: The answer is "b", with the length of 1.
//
// Example 3:
// Input: s = "pwwkew"
// Output: 3
// Explanation: The answer is "wke", with the length of 3.
// Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

// Constraints:
// 0 <= s.length <= 5 * 10^4
// s consists of English letters, digits, symbols and spaces.

#include <iostream>
#include <string>
#include <unordered_set>

class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        // This unordered set is used to store the characters that are currently in the
        // longest substring without repeating characters.
        std::unordered_set<char> charSet;

        // The starting index of the substring.
        int start = 0;
        // The length of the longest substring without repeating characters.
        int maxLength = 0;

        // Iterate over the string.
        for (int end = 0; end < s.size(); ++end) {
            // If the character at the current ending index of the substring already exists
            // in the character set, continue to remove characters from the start of the
            // substring until the character is no longer in the set.
            while (charSet.count(s[end])) {
                charSet.erase(s[start]);
                start += 1;
            }

            // Insert the current character into the set.
            charSet.insert(s[end]);

            // Calculate the length of the current substring and update maxLength
            // if this length is the largest we've found so far.
            maxLength = std::max(maxLength, end - start + 1);
        }
        // Return the length of the longest substring found.
        return maxLength;
    };
};

int main(int argc, char** argv)
{
    std::string first = "abcabcbb";
    std::string second = "bbbbb";
    std::string third = "pwwkew";

    Solution longest;

    std::cout << longest.lengthOfLongestSubstring(first) << std::endl;
    std::cout << longest.lengthOfLongestSubstring(second) << std::endl;
    std::cout << longest.lengthOfLongestSubstring(third) << std::endl;
};