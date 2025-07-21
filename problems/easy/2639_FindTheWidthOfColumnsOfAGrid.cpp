/*
You are given a 0-indexed m x n integer matrix grid. The width of a column is the maximum length of its integers.
    For example, if grid = [[-10], [3], [12]], the width of the only column is 3 since -10 is of length 3.
Return an integer array ans of size n where ans[i] is the width of the ith column.
The length of an integer x with len digits is equal to len if x is non-negative, and len + 1 otherwise.


Example 1:
Input: grid = [[1],[22],[333]]
Output: [3]
Explanation: In the 0th column, 333 is of length 3.

Example 2:
Input: grid = [[-15,1,3],[15,7,12],[5,6,-2]]
Output: [3,1,2]
Explanation: 
In the 0th column, only -15 is of length 3.
In the 1st column, all integers are of length 1. 
In the 2nd column, both 12 and -2 are of length 2.


Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 100 
    -109 <= grid[r][c] <= 109
*/

#include <vector>
#include <algorithm>
#include <string>

using namespace std;


class Solution {
public:
    vector<int> findColumnWidth(vector<vector<int>>& input_grid)
    {
        // the number of columns
        int number_of_columns = input_grid[0].size();
        // create return object.
        vector<int> maxColumnValue(number_of_columns, 0);

        // iterate over the grids rows
        for(const auto& row : input_grid)
        {
            // iterate over the column value in each
            for(int index = 0; index < number_of_columns; ++index)
            {   
                // convert the value to a count of its parts
                int width = to_string(row[index]).size();
                // update the maximum width for that index position
                maxColumnValue[index] = max(maxColumnValue[index], width);
            }
        }
        return maxColumnValue;
    }
};



int main(int argc, char** argv)
{
    return 0;
}