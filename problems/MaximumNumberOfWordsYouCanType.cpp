// There is a malfunctioning keyboard where some letter keys do not work. 
// All other keys on the keyboard work properly.
// 
// Given a string text of words separated by a single space 
// no leading or trailing spaces and a string brokenLetters of all 
// distinct letter keys that are broken, 
// return the number of words in text you can fully type using this keyboard.
// 
// Example 1:
// 
// Input: text = "hello world", brokenLetters = "ad"
// Output: 1
// Explanation: We cannot type "world" because the 'd' key is broken.
// 
// Example 2:
// 
// Input: text = "leet code", brokenLetters = "lt"
// Output: 1
// Explanation: We cannot type "leet" because the 'l' and 't' keys are broken.
// 
// Example 3:
// 
// Input: text = "leet code", brokenLetters = "e"
// Output: 0
// Explanation: We cannot type either word because the 'e' key is broken.

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>

int workingWords(std::string input, std::string broken_letter)
{
    int word_result  = 0;
    std::unordered_set<char> broken_keys;
    std::istringstream string_stream(input);
    std::string word;

    for(char& key : broken_letter)
    {
        broken_keys.insert(key);
    }

    while(std::getline(string_stream, word, ' '))
    {
        for(auto& letter : word)
        {
            if(broken_keys.count(letter))
            {
                // the key is broken stop checking the work
                break;
            }
            if(letter == word.back())
            {
                std::cout << "working word: " << word << std::endl;
                word_result++;
            }

        }
    }
    
    return word_result;
}

int main(int argc, char** argv)
{
    std::string first_input =  "hello world";   // output 1
    std::string first_bad  = "ad";

    std::string second_input =  "leet code";    // output 1
    std::string second_bad  = "lt";

    std::string third_input =  "leet code";     // output 0
    std::string third_bad  = "e";

    std::cout << workingWords(first_input, first_bad) << std::endl;
    std::cout << workingWords(second_input, second_bad) << std::endl;
    std::cout << workingWords(third_input, third_bad) << std::endl;
}