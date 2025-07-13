// Write a function to find the longest common prefix string amongst an array of strings.
// If there is no common prefix, return an empty string "".
// 
// Example 1:
// Input: strs = ["flower","flow","flight"]
// Output: "fl"
// 
// Example 2 
// Input: strs = ["dog","racecar","car"]
// Output: ""
// Explanation: There is no common prefix among the input strings.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string longestCommonPrefix(std::vector<std::string>& word_set) {

    int set_size = word_set.size();
    std::string prefix_result = "";

    std::sort(word_set.begin(), word_set.end());   

    std::string first_word = word_set[0];
    std::string last_word = word_set[set_size-1];

    for(int i=0; i < std::min(first_word.size(), last_word.size()); i++){
        if(first_word[i]!=last_word[i]){
            return prefix_result;
        }
        prefix_result+=first_word[i];
    }
    return prefix_result;
    }


int main(int argc, char** argv)
{
    std::vector<std::string> first = {"flower","flow","flight"};
    std::vector<std::string> second = {"dog","racecar","car"};

    std:: cout << longestCommonPrefix(first) << std::endl;
    std:: cout << longestCommonPrefix(second) << std::endl;
}