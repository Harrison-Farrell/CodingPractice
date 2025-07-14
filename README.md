[ALL TIME QUESTIONS](https://github.com/krishnadey30/LeetCode-Questions-CompanyWise/blob/master/atlassian_alltime.csv)

## 1366: Rank Team by Votes

1. Create the 2D Vector array to store the votes
2. Count the counts, storing the result into the array
3. Sort the array.

```cpp
class Solution {
public:
    string rankTeams(vector<string>& votes)
    {
        int n = votes[0].size();
        string ans = votes[0];

        vector<vector<int>> freq(26, vector<int> (n)); // (1)

        for(auto i : votes)
        {
            for(int j=0;j<n;j++)
            {
                freq[i[j]-'A'][j]++; // (2)
            }
        }

        sort(ans.begin(), ans.end(), [&](auto& x, auto& y)
             {
                if(freq[x-'A'] == freq[y-'A'])
                    return x<y;

                 return freq[x-'A'] > freq[y-'A'];
             }); // (3)

        return ans;
    }
};
```

## 359: Logger Rate Limiter

1. Construct an unordered_map using the message as the Key
2. Check the new message is in the unordered_map
3. Check the last sent time stamp
4. Update the time stamp if message is logged

```cpp
class Logger {
public:
    unordered_map<string, int> lastTime; // (1)

    bool shouldPrintMessage(int timestamp, string message)
    {
        if (lastTime.count(message) ) // (2)
        {
            if( timestamp - lastTime[message] < 10) // (3)
            {
              return false;
            }

            lastTime[message] = timestamp; (4)
            return true;
        }
    }
};
```

## 911: Online Election

Constructor method

1. Count the votes
2. As each vote is cast. Check the current leader.
3. Log the Leader against the time

Return Leader method

1. Find the upper_bound
2. Return the leader index

```cpp
class TopVotedCandidate {
private:
    vector<int> lead;
    vector<int> time;
public:
    TopVotedCandidate(vector<int>& persons, vector<int>& times) {
        int n = persons.size();
        time = move(times);
        lead.assign(n , 0);
        unordered_map<int, int> voteCount;
        int leader = -1, maxVotes = 0;
        for (int i = 0; i < n; ++i) {
            int p = persons[i];
            if (++voteCount[p] >= maxVotes) {
                leader = p;
                maxVotes = voteCount[p];
            }
            lead[i] = leader;
        }
    }
    int q(int t) {
        int idx = upper_bound(time.begin(), time.end(), t) - time.begin() - 1;
        return lead[idx];
    }
};
```

## 362: Design a Hit Counter

1. Construct an unordered_map for unique time stamps
2. Increment the time stamp each new
3. Iterate through the unordered_map
4. if time stamp is less than 5 minutes. Count the hit

```cpp
class HitCounter {
    public:
      std::unorder_map<int, int> hitCounts;

        void hit(int timestamp) {
            // Increment the hit count for the given timestamp
            // If it does not exist, it is inserted into the map with a count of 0, then incremented
            hitCounts[timestamp]++;
        }

        int getHits(int timestamp) {
            int hits = 0; // Variable to accumulate the number of hits
            // Iterate through all entries in the unordered_map
            for (auto &entry : hitCounts) {
                // Check if the entry's timestamp is within the past 5 minutes from the current timestamp
                if (timestamp - entry.first < 300) { // 300 seconds equals 5 minutes
                    // Sum up the hits that are within the past 5 minutes
                    hits += entry.second;
                }
            }
            // Return the total number of hits
            return hits;
        }
};
```

## 297: Serialize and Deserialize a Binary tree

Encoding.

1. Walking through the Tree. Performing recursion on the Linked list.
2. Get the value + Serialize the left & right nodes.

Decoding

1. Create a helper function to step through the string
2. Create a Tree node for the string value

```cpp
  class Codec {
public:

    string serialize(TreeNode* root) {
        ostringstream out;
        serialize(root, out);
        return out.str();
    }

    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserialize(in);
    }

private:

    void serialize(TreeNode* root, ostringstream& out) {
        if (root) {
            out << root->val << ' ';
            serialize(root->left, out);
            serialize(root->right, out);
        } else {
            out << "# ";
        }
    }

    TreeNode* deserialize(istringstream& in) {
        string val;
        in >> val;
        if (val == "#")
            return nullptr;
        TreeNode* root = new TreeNode(stoi(val));
        root->left = deserialize(in);
        root->right = deserialize(in);
        return root;
    }
};
```

## 1970: Last Day Where You Can Still Cross

Binary Search:

1. Initialize left as 0 (representing the earliest day) and right as row \* col (representing the latest possible day).
2. While left is less than right - 1, do the following:
   1. Calculate the mid-day as mid = (left + right) / 2.
   2. Check if it is possible to cross the grid on day mid by calling the isPossible function.
   3. The isPossible function checks if it is possible to cross the grid by considering the first mid cells from the given list. It uses BFS to explore the grid and checks if the bottom row can be reached.
   4. If it is possible to cross, update left to mid and store the latest possible day in a variable (let's call it latestPossibleDay).
   5. If it is not possible to cross, update right to mid.
3. Return latestPossibleDay as the latest day where it is still possible to cross the grid.

Breadth-First Search (BFS):

The isPossible function:

1. Create a grid with dimensions (m + 1) x (n + 1) and initialize all cells to 0.
2. Mark the cells from the given list as blocked by setting their corresponding positions in the grid to 1.
3. Create a queue to perform BFS.
4. For each cell in the first row of the grid, if it is not blocked, add it to the queue and mark it as visited.
5. While the queue is not empty, do the following:
   1. Dequeue a cell from the front of the queue.
   2. Get the current cell's coordinates (row and column).
   3. Explore the neighboring cells (up, down, left, and right) by checking their validity and whether they are blocked or not.
   4. If a neighboring cell is valid, not blocked, and has not been visited, mark it as visited and enqueue it.
   5. If a neighboring cell is in the last row, return true as it means a

path to the bottom row has been found. 6. If we finish the BFS without finding a path to the bottom row, return false.

```cpp
class Solution {
public:
    bool isPossible(int m, int n, int t, vector<vector<int>>& cells) {
        vector<vector<int>> grid(m + 1, vector<int>(n + 1, 0)); // Grid representation
        vector<pair<int, int>> directions {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // Possible directions

        for (int i = 0; i < t; i++) {
            grid[cells[i][0]][cells[i][1]] = 1; // Mark cells from the given list as blocked
        }

        queue<pair<int, int>> q;

        for (int i = 1; i <= n; i++) {
            if (grid[1][i] == 0) {
                q.push({1, i}); // Start BFS from the top row
                grid[1][i] = 1; // Mark the cell as visited
            }
        }
        while (!q.empty()) {
            pair<int, int> p = q.front();
            q.pop();
            int r = p.first, c = p.second; // Current cell coordinates
            for (auto d : directions) {
                int nr = r + d.first, nc = c + d.second; // Neighbor cell coordinates
                if (nr > 0 && nc > 0 && nr <= m && nc <= n && grid[nr][nc] == 0) {
                    grid[nr][nc] = 1; // Mark the neighbor cell as visited
                    if (nr == m) {
                        return true; // Found a path to the bottom row
                    }
                    q.push({nr, nc}); // Add the neighbor cell to the queue for further exploration
                }
            }
        }
        return false; // Unable to find a path to the bottom row
    }

    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        int left = 0, right = row * col, latestPossibleDay = 0;
        while (left < right - 1) {
            int mid = left + (right - left) / 2; // Calculate the mid-day
            if (isPossible(row, col, mid, cells)) {
                left = mid; // Update the left pointer to search in the upper half
                latestPossibleDay = mid; // Update the latest possible day
            } else {
                right = mid; // Update the right pointer to search in the lower half
            }
        }
        return latestPossibleDay;
    }
};

```

## 23: Merge K Sorted Lists

```cpp
class Solution {
public:

    ListNode* mergeSort(ListNode* head1, ListNode* head2){
        if(head1 == NULL){
            return head2;
        }
        if(head2 == NULL){
            return head1;
        }

        if(head1->val < head2->val){
            head1->next = mergeSort(head1->next, head2);
            return head1;
        } else {
            head2->next = mergeSort(head1, head2->next);
            return head2;
        }
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        queue<ListNode*> q;
        for(auto node : lists){
            q.push(node);
        }

        while(!q.empty()){
            ListNode* head1 = q.front();
            q.pop();
            if(q.empty()){
                return head1;
            }
            ListNode* head2 = q.front();
            q.pop();

            ListNode* ans = mergeSort(head1, head2);

            q.push(ans);
        }

        return NULL;
    }
};
```

## 821: Shortest Distance to a Character

1. Create two vectors, position & answer
2. Find all the known positions of the target char
3. Find the shortest distance from the current char to the target
4. Push back the index distance into the answer vector

```cpp
class Solution {
public:
    vector<int> shortestToChar(string s, char c) {
        vector<int> position;
        vector<int> answer;
        for(int i=0; i<s.size(); i++)
        {
            if(s[i]==c)
                position.push_back(i);
        }
        for(int i=0; i<s.size(); i++)
        {
            int shortest_dist = INT_MAX;
            for(int j=0; j<position.size(); j++)
            {
                shortest_dist = min(shortest_dist, abs(i-position[j]));
            }
            answer.push_back(shortest_dist);
        }
        return answer;
    }
};
```

## 366: Find Leaves of Binary Tree

1. Use the concept of Depth First Search (DFS)
2. Step down through the left most node using recursion
3. Once at the bottom node.
4. Step back up the tree

```cpp
class Solution
{
  vector<vector<int>> response; // response[i] stores all nodes with a level of i

  int DepthFirstSearch(TreeNode* u)
  {
    if(u == nullptr) return -1;  // end of the Tree branch

    int left_level = DepthFirstSearch(u->left);
    int right_level = DepthFirstSearch(u->right);

    int current_level = std::max(left_level, right_level) + 1
    while(response.size() <= current_level)
    {
      response.push_back({})
    }

    response[current_level].push_back(u->val);
    return current_level;
  }

  vector<vector<int>> findLeaves(TreeNode* root)
  {
    DepthFirstSearch(root)
    return response;
  }
}
```

## 353: Design Snake Game

1. Construct the game & Snake
2. Move the Snake
3. Check the move is in bounds
4. Check the move collects food
   1. IF yes, add score and food count
   2. IF no, remove tail cell
5. Check for snake collision with itself
6. Add head cell

```cpp
class SnakeGame
{
public:

  int game_width;
  int game_height;
  vector<vector<int>> food_cells;
  int score;
  depue<int> snake;
  unordered_set<int> snake_position;

  int arrayTransform(int row, int col)
  {
    // convert 2D array into 1D
    return row * game_width + col;
  }

  SnakeGame(int width, int height, vector<vector<int>>& food_cells)
  : game_width(width),
    game_height(height),
    food_cells(food_cells),
    score(0),
    food_cell_index(0),
  {
    snake.push_front(encode(0,0));
    snake_position.insert(0);
  }

  int move(string direction)
  {
    int snake_head = snake.font();
    int current_row = snake_head / game_width
    int current_col = snake_head % game_width

    if(direction == 'U') current_row--;
    if(direction == 'D') current_row++;
    if(direction == 'L') current_col--;
    if(direction -- 'R') current_col++;

    if(current_row < 0 || current_row >= game_height || current_col < 0 || current_col >= game_width)
    {
      return -1 // game over
    }

    if (m_foodIndex < m_food.size() && current_row == m_food[m_foodIndex][0] && current_col == m_food[m_foodIndex][1])
    {
      score++;
      food_cell_index++;
    }
    else
    {
      int tailCode = snake.back();
      snake.pop_back();
      snake_positions.erase(tailCode);
    }

    int newHeadCode = arrayTransform(row, col);

    // Check for snake collision with itself
    if (snake_positions.count(newHeadCode))
    {
      return -1;
    }

    // Add the new head to the snake deque and set of occupied positions
    snake.push_front(newHeadCode);
    snake_positions.insert(newHeadCode);
    return m_score;
  }
}
```

## 757: Set Intersection Size At Least Two

```cpp
class Solution {
public:
    // Function to calculate the minimum size of a set so that for every
    // interval in 'intervals' there are at least two distinct set elements which
    // are in the interval.
    int intersectionSizeTwo(std::vector<std::vector<int>>& intervals) {
        // Sort the intervals based on their end points. If end points are the same,
        // sort based on the start points in decreasing order. This way, we prefer
        // intervals with larger start points for same end points.
        sort(intervals.begin(), intervals.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
            return a[1] == b[1] ? a[0] > b[0] : a[1] < b[1];
        });
        int ans = 0; // Initialize the answer to 0.
        int smallest = -1, secondSmallest = -1; // Initialize the two smallest elements seen so far to -1.

        // Iterate through the sorted intervals
        for (const auto& interval : intervals) {
            int start = interval[0], end = interval[1];
            // If the current start is less than or equal to smallest, this interval is already covered
            // by the elements chosen so far.
            if (start <= smallest) continue;
            // If the current start is greater than secondSmallest, we need to add two more elements to the set.
            if (start > secondSmallest) {
                ans += 2;
                // The secondSmallest is now the end of the interval minus one, and the smallest
                // is the end of the interval.
                secondSmallest = end - 1;
                smallest = end;
            } else {
                // If start is between smallest and secondSmallest, we need to add one more element.
                ans += 1;
                // The new secondSmallest becomes the smallest we had, and the new smallest becomes the end of this interval.
                secondSmallest = smallest;
                smallest = end;
            }
        }
        // Return the total number of elements added to the set.
        return ans;
    }
};
```

## 2851: String Transformation

```cpp
class Solution {
    // Define modulo constant for operations to ensure result remains within integer bounds.
    static const int MOD = 1e9 + 7;
    // Utility function to perform addition under modulo.
    int add(int x, int y) {
        x += y;
        if (x >= MOD) {
            x -= MOD;
        }
        return x;
    }
    // Utility function to perform multiplication under modulo.
    int mul(long long x, long long y) {
        return static_cast<int>((x * y) % MOD);
    }
    // Generate Z-array for string matching, which will be used to find the number of matches of t in s.
    vector<int> generateZArray(const string& s) {
        const int n = s.length();
        vector<int> z(n);
        for (int i = 1, left = 0, right = 0; i < n; ++i) {
            if (i <= right && z[i - left] < right - i + 1) {
                z[i] = z[i - left];
            } else {
                z[i] = max(0, right - i + 1);
                while (i + z[i] < n && s[i + z[i]] == s[z[i]]) {
                    ++z[i];
                }
            }
            if (i + z[i] - 1 > right) {
                left = i;
                right = i + z[i] - 1;
            }
        }
        return z;
    }
    // Perform matrix multiplication and return the result.
    vector<vector<int>> matrixMultiply(const vector<vector<int>>& a, const vector<vector<int>>& b) {
        const int m = a.size(), n = b.size(), p = b[0].size();
        vector<vector<int>> result(m, vector<int>(p, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < p; ++k) {
                    result[i][k] = add(result[i][k], mul(a[i][j], b[j][k]));
                }
            }
        }
        return result;
    }
    // Compute matrix exponentiation a^y and return the result.
    vector<vector<int>> matrixPower(const vector<vector<int>>& a, long long y) {
        const int n = a.size();
        vector<vector<int>> res(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            res[i][i] = 1;
        }
        vector<vector<int>> x = a;
        while (y) {
            if (y & 1) {
                res = matrixMultiply(res, x);
            }
            x = matrixMultiply(x, x);
            y >>= 1;
        }
        return res;
    }
public:
    // Calculate the number of ways 't' can be formed from 's' after 'k' operations.
    int numberOfWays(const string& s, const string& t, long long k) {
        const int n = s.length();

        // Compute the dynamic programming base cases using matrix exponentiation.
        const auto dpBaseCases = matrixPower({{0, 1}, {n - 1, n - 2}}, k)[0];

        // Concatenate strings for z-array processing.
        string concatenated = s + t + t;
        const auto z = generateZArray(concatenated);
        const int m = n + t.length();

        // Calculate the result by checking z-values for string t's occurrences in s.
        int result = 0;
        for (int i = n; i < m; ++i) {
            if (z[i] >= n) {
                result = add(result, dpBaseCases[i - n != 0]);
            }
        }
        return result;
    }
};
```

## 1166 Design File System

```cpp
class TrieNode {
public:
    std::unordered_map<std::string, TrieNode*> children; // Children of the current node
    int value; // Value associated with the node

    // Constructor initializing TrieNode with a given value
    TrieNode(int v) : value(v) {}

    // Inserts a path with a value into the Trie
    bool insert(const std::string& w, int v) {
        TrieNode* node = this; // Starting at the root
        std::vector<std::string> parts = split(w, '/'); // Split the path
        // Traverse the parts of the path excluding the first and last
        for (size_t i = 1; i < parts.size() - 1; ++i) {
            const std::string& p = parts[i];
            // If the part is not found in children, return false (cannot insert)
            if (!node->children.count(p)) {
                return false;
            }
            node = node->children[p]; // Move to the next part
        }
        // If the last part is already in children, return false (path exists)
        if (node->children.count(parts.back())) {
            return false;
        }
        // Create a new node for the last part with the given value
        node->children[parts.back()] = new TrieNode(v);
        return true; // Successfully inserted
    }

    // Searches for a value by the given path in the Trie
    int search(const std::string& w) {
        TrieNode* node = this; // Starting at the root
        std::vector<std::string> parts = split(w, '/'); // Split the path
        // Traverse the parts of the path
        for (size_t i = 1; i < parts.size(); ++i) {
            const std::string& p = parts[i];
            // If the part is not found in children, return -1 (path does not exist)
            if (!node->children.count(p)) {
                return -1;
            }
            node = node->children[p]; // Move to the next part
        }
        // Return the value of the found node
        return node->value;
    }
private:
    // Helper method to split a string by a delimiter into a vector of strings.
    std::vector<std::string> split(const std::string& s, char delim) {
        std::stringstream ss(s);
        std::string item;
        std::vector<std::string> res;
        while (std::getline(ss, item, delim)) {
            if (!item.empty()) { // Ignore empty strings from multiple '/' in a row
                res.push_back(item);
            }
        }
        return res;
    }
};

// Class representing a file system interface
class FileSystem {
public:
    // Constructor initializing FileSystem with a fake root node with value -1
    FileSystem() : trieRoot(new TrieNode(-1)) {}
    // Creates a path in the trie with the given value
    bool createPath(const std::string& path, int value) {
        return trieRoot->insert(path, value);
    }
    // Gets the value of the node associated with the path
    int get(const std::string& path) {
        return trieRoot->search(path);
    }
private:
    TrieNode* trieRoot; // The root of the Trie
};
```

## 1639: Number of Ways to Form a Target String Given a Dictionary

```cpp
class Solution {
public:
    int numWays(vector<string>& words, string target) {
        const int MOD = 1e9 + 7; // Define the modulus to keep the numbers within the integer limit
        int targetLength = target.size(), wordLength = words[0].size(); // Size of the target string and length of each word in the array
        vector<vector<int>> count(wordLength, vector<int>(26)); // 2D vector to store the count of each character at each position

        // Loop to count the frequency of each character at each column in the word list
        for (auto& word : words) {
            for (int j = 0; j < wordLength; ++j) {
                ++count[j][word[j] - 'a']; // Increment the count of the character at the relevant position
            }
        }
        // DP array initialized with -1 to indicate that the value hasn't been computed yet
        int dp[targetLength][wordLength];
        memset(dp, -1, sizeof(dp));

        // Recursive lambda function to compute the number of ways using Depth First Search (DFS)
        function<int(int, int)> dfs = [&](int i, int j) -> int {
            if (i >= targetLength) {
                return 1; // If the whole target is found, return 1 way
            }
            if (j >= wordLength) {
                return 0; // If the end of the word is reached, no more ways can be found, return 0
            }
            if (dp[i][j] != -1) {
                return dp[i][j]; // If the value is already computed, return the cached result
            }
            int ways = dfs(i, j + 1); // Recursive call to check for ways without using the current position
            ways = (ways + 1LL * dfs(i + 1, j + 1) * count[j][target[i] - 'a']) % MOD; // Add the ways using the current character and proceed
            return dp[i][j] = ways; // Store the computed ways in the DP array for memoization
        };
        // Call the DFS function starting from the first character of the target and the word
        return dfs(0, 0);
    }
};
```

## 741: Cherry Pickup

```cpp
class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int size = grid.size();
        // 3D dp array initialized with very small negative values
        vector<vector<vector<int>>> dp(2 * size, vector<vector<int>>(size, vector<int>(size, INT_MIN)));
        dp[0][0][0] = grid[0][0]; // Starting cell

        // 'k' is the sum of the indices (i+j) of each step, determining the "time" step diagonal
        for (int k = 1; k < 2 * size - 1; ++k) {
            for (int i1 = 0; i1 < size; ++i1) {
                for (int i2 = 0; i2 < size; ++i2) {
                    // Calculate the second coordinate of the robots' positions based on k
                    int j1 = k - i1, j2 = k - i2;
                    // Skip out-of-bounds coordinates or thorns
                    if (j1 < 0 || j1 >= size || j2 < 0 || j2 >= size || grid[i1][j1] == -1 || grid[i2][j2] == -1) continue;

                    // Cherries picked up by both robots, don't double count if same cell
                    int cherries = grid[i1][j1];
                    if (i1 != i2) cherries += grid[i2][j2];

                    // Check all combinations of previous steps
                    for (int prevI1 = i1 - 1; prevI1 <= i1; ++prevI1) {
                        for (int prevI2 = i2 - 1; prevI2 <= i2; ++prevI2) {
                            if (prevI1 >= 0 && prevI2 >= 0) { // Boundary check
                                // Update the dp value for the maximum cherries collected
                                dp[k][i1][i2] = max(dp[k][i1][i2], dp[k - 1][prevI1][prevI2] + cherries);
                            }
                        }
                    }
                }
            }
        }
        // Return the max of 0 and the final cell to account for negative values
        return max(0, dp[2 * size - 2][size - 1][size - 1]);
    }
};
```

## 981: Time Based Key-Value Store

```cpp
class TimeMap {
public:
    TimeMap() {

    }
    map<string,vector<pair<int,string>>>cnt;
    void set(string key, string value, int timestamp) {
        cnt[key].push_back({timestamp,value});
    }

    string get(string key, int timestamp) {
        auto &p=cnt[key];
        int l=0,r=p.size()-1;
        string s;
        while(l<=r){
            int mid=l+(r-l)/2;
            if(p[mid].first<=timestamp){
                s=p[mid].second;
                l=mid+1;
            }
            else{
                r=mid-1;
            }
        }
        return s;
    }
};
```

## 17: Letter Combinations of a Phone Number

```cpp
class Solution {
private:
    void letterCombinations(string digits, vector<string>& output, string &temp, vector<string>& pad, int index){
        if(index == digits.size()){
            output.push_back(temp);
            return;
        }
        string value = pad[digits[index]-'0'];
        for(int i=0; i<value.size(); i++){
            temp.push_back(value[i]);
            letterCombinations(digits, output, temp, pad, index+1);
            temp.pop_back();
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        if(digits.empty()){
            return {};
        }
        vector<string> pad = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> output;
        string temp;
        letterCombinations(digits, output, temp, pad, 0);
        return output;
    }
};
```

## 540: Single Element in a Sorted Array

```cpp
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        unordered_set<int> s;
        for(auto c : nums)
            if(s.count(c)) s.erase(c);      // erase on 2nd occurence
            else s.insert(c);               // insert on 1st occurence
        return *begin(s);                   // only element at end is the element occuring once
    }
};
```

## 300: Longest Increasing Subsequence

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> res;
        for (auto x : nums) {
            if (find(res.begin(), res.end(),x) != res.end())
                continue;
            auto it = upper_bound(res.begin(), res.end(), x);
            if (it == res.end()) {
                res.push_back(x);
            } else {
                res[it - res.begin()] = x;
            }
        }
        return res.size();
    }
};
```

## 1120: Maximum Average Subtree

```cpp
class Solution {
public:
    double maximumAverageSubtree(TreeNode* root) {
        double maxAverage = 0; // This will hold the maximum average found.
        // Recursive function to perform DFS (Depth-First Search).
        std::function<std::pair<int, int>(TreeNode*)> dfs = [&](TreeNode* node) -> std::pair<int, int> {
            if (!node) {
                return {0, 0}; // If the node is null, return 0 sum and 0 count.
            }
            // Compute the sum and count for left subtree.
            std::pair<int, int> leftSubtree = dfs(node->left);
            // Compute the sum and count for right subtree.
            std::pair<int, int> rightSubtree = dfs(node->right);
            // Current sum is the value of the node plus sum of left and right subtrees.
            int currentSum = node->val + leftSubtree.first + rightSubtree.first;
            // Current count is 1 (for the current node) plus count of left and right subtrees.
            int currentCount = 1 + leftSubtree.second + rightSubtree.second;
            // Update the maximum average if the current average is greater.
            maxAverage = std::max(maxAverage, static_cast<double>(currentSum) / currentCount);
            // Return the current sum and count for further use.
            return {currentSum, currentCount};
        };
        // Start DFS from the root of the tree.
        dfs(root);
        // After the DFS is complete, maxAverage holds the maximum average value.
        return maxAverage;
    }
};
```

## 1223: Dice Roll Simulation

```cpp
class Solution {
public:
    int dieSimulator(int n, std::vector<int>& rollMax) {
        // The state of the dynamic programming (dp) table
        // dp[i][j][x] represents the number of sequences where:
        // i is the total rolls so far,
        // j is the last number rolled (1-6),
        // x is the consecutive times the last number j has been rolled.
        int dp[n][7][16];
        memset(dp, 0, sizeof dp); // Initialize the dp table with 0
        const int MOD = 1e9 + 7; // Define the modulo value

        // The recursive depth-first search function to explore the solution space
        std::function<int(int, int, int)> dfs = [&](int rollCount, int lastNumber, int consecCount) -> int {
            if (rollCount >= n) { // Base case: all dice have been rolled
                return 1;
            }
            if (dp[rollCount][lastNumber][consecCount]) { // Return memoized result
                return dp[rollCount][lastNumber][consecCount];
            }
            long long totalWays = 0; // Use long long to prevent overflow before taking mod
            for (int face = 1; face <= 6; ++face) {
                if (face != lastNumber) { // If the current face is different from the last number rolled
                    totalWays += dfs(rollCount + 1, face, 1); // Start count new number with 1
                } else if (consecCount < rollMax[lastNumber - 1]) { // If it's the same and under the rollMax limit
                    totalWays += dfs(rollCount + 1, lastNumber, consecCount + 1); // Continue sequence
                }
            }
            totalWays %= MOD; // Take modulo to prevent overflow
            return dp[rollCount][lastNumber][consecCount] = totalWays; // Memoize and Return
        };

        // Invoke the dfs function starting with count 0, lastNumber 0 (dummy), and consecCount 0
        return dfs(0, 0, 0);
    }
};
```

## 98: Validate Binary Search Tree

```cpp
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return isValid(root, LONG_MIN, LONG_MAX);
    }

    bool isValid(TreeNode* node, long min, long max) {
        if (!node) return true;
        if (node->val <= min || node->val >= max) return false;
        return isValid(node->left, min, node->val) && isValid(node->right, node->val, max);
    }
};
```

## 2: Add Two numbers

```cpp
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummyHead = new ListNode(0);
        ListNode* tail = dummyHead;
        int carry = 0;

        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int digit1 = (l1 != nullptr) ? l1->val : 0;
            int digit2 = (l2 != nullptr) ? l2->val : 0;

            int sum = digit1 + digit2 + carry;
            int digit = sum % 10;
            carry = sum / 10;

            ListNode* newNode = new ListNode(digit);
            tail->next = newNode;
            tail = tail->next;

            l1 = (l1 != nullptr) ? l1->next : nullptr;
            l2 = (l2 != nullptr) ? l2->next : nullptr;
        }

        ListNode* result = dummyHead->next;
        delete dummyHead;
        return result;
    }
};
```

## 3: Longest Substring Without Repeating Characters

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.length();
        int maxLength = 0;
        unordered_map<char, int> charMap;
        int left = 0;

        for (int right = 0; right < n; right++) {
            if (charMap.count(s[right]) == 0 || charMap[s[right]] < left) {
                charMap[s[right]] = right;
                maxLength = max(maxLength, right - left + 1);
            } else {
                left = charMap[s[right]] + 1;
                charMap[s[right]] = right;
            }
        }

        return maxLength;
    }
};
```
