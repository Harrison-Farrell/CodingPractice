// Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.
// You have the following three operations permitted on a word:
//     Insert a character
//     Delete a character
//     Replace a character
// 
// Example 1:
// Input: word1 = "horse", word2 = "ros"
// Output: 3
// Explanation: 
// horse -> rorse (replace 'h' with 'r')
// rorse -> rose (remove 'r')
// rose -> ros (remove 'e')
// 
// Example 2:
// Input: word1 = "intention", word2 = "execution"
// Output: 5
// Explanation: 
// intention -> inention (remove 't')
// inention -> enention (replace 'i' with 'e')
// enention -> exention (replace 'n' with 'x')
// exention -> exection (replace 'n' with 'c')
// exection -> execution (insert 'u')

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int NumberOfOperations(std::string target, std::string source)
{
    if(source == target) return 0;  // source equals target already

    int target_size = target.size();
    int source_size = source.size();

    // Dynamic Programing technical
    // i equals the character in word one
    // j equals the character in word two
    std::vector<int> previous(target.size() +1);
    std::vector<int> current(target.size() +1);

    for(int j = 0; j <= target_size; ++j)
    {
        previous[j] = j;
    }
    
    for (int i = 1; i <= source_size; ++i)
    {
        current[0] = i;
        for (int j = 1; j <= target_size; ++j)
        {
            if (source[i - 1] == target[j - 1])
                current[j] = previous[j - 1];
            else
                current[j]=1+std::min({previous[j],current[j - 1],previous[j- 1]});
        }
        previous = current;
    }

    return previous[target_size];
}


int main(int argc, char** argv)
{
    return 0;
}
