// Given an integer x, return true if x is a palindrome, and false otherwise.
// 
// Example 1:
// Input: x = 121
// Output: true
// Explanation: 121 reads as 121 from left to right and from right to left.
// 
// Example 2:
// Input: x = -121
// Output: false
// Explanation: From left to right, it reads -121. From right to left, it becomes 121-. 
// Therefore it is not a palindrome.
// 
// Example 3:
// Input: x = 10
// Output: false
// Explanation: Reads 01 from right to left. Therefore it is not a palindrome.

#include <iostream>
#include <string>

bool isPalindrome(int value)
{   
    if(value < 0)
    {   
        // Negatives can never be a palindrome
        return false;
    }

    std::string string_value = std::to_string(value);
    // Only need to get to the middle of the string;
    int end_point = string_value.size();
    int mid_point = end_point / 2;

    for(int i = 0; i < mid_point; i++)
    {
        if(string_value[i] != string_value[end_point - i  -1]) // -1 as end_point is size()
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv)
{
    int first_example = 121;        // true
    int second_example = -121;      // false
    int third_example = 10;         // false
    
    std::cout << first_example << ":" << isPalindrome(first_example) << std::endl;
    std::cout << second_example << ":" << isPalindrome(second_example) << std::endl;
    std::cout << third_example << ":" << isPalindrome(third_example) << std::endl;

    return 0;
}