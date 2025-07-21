/*
The LeetCode problem presents us with a classic game of Snake, 
where the objective is to control a snake that moves around a grid, 
eats food, and grows in length with each piece of food it consumes. 
The game stops if the snake either runs into the wall or itself.
We're asked to design the game logic for a snake initially of length 1 unit, 
starting from the top-left corner of the grid with dimensions height x width.

The grid functions like a 2D array where the food items are coordinates listed in the food array. 
The snake moves in one of four directions each turn: up (U), down (D), left (L), or right (R).
The game scores a point when the snake eats a piece of food, 
which involves moving to the same coordinate location as the next item in the food array. 
Food items appear sequentially, with the next item making its appearance only after the current
 one has been eaten. The game is over if the snake tries to move beyond the boundary 
 of the grid or into a space occupied by its body.

The objective is to implement the SnakeGame class with:
    A constructor SnakeGame(int width, int height, int[][] food) which initializes the game with the screen size and the food positions.
    A method int move(String direction) to move the snake in the requested direction and return the game's score or -1 if the game is over.

Input
["SnakeGame", "move", "move", "move", "move", "move", "move"]
[[3, 2, [[1, 2], [0, 1]]], ["R"], ["D"], ["R"], ["U"], ["L"], ["U"]]
Output
[null, 0, 0, 1, 1, 2, -1]

Explanation
SnakeGame snakeGame = new SnakeGame(3, 2, [[1, 2], [0, 1]]);
snakeGame.move("R"); // return 0
snakeGame.move("D"); // return 0
snakeGame.move("R"); // return 1, snake eats the first piece of food. The second piece of food appears at (0, 1).
snakeGame.move("U"); // return 1
snakeGame.move("L"); // return 2, snake eats the second food. No more food appears.
snakeGame.move("U"); // return -1, game over because snake collides with border

*/

#include <string>
#include <vector>
#include <iostream>
#include <deque>        // double ended queue
#include <unordered_set>

using namespace std;

class SnakeGame {
public:
    SnakeGame(int width, int height, std::vector<std::vector<int>> food)
    {
        m_width = width;
        m_height = height;
        m_food = food;
        m_score = 0;
        m_foodIndex = 0;
        snake.push_front(encode(0,0));
        snake_positions.insert(0);
    }

    int move(std::string direction)
    {
        int snake_head = snake.front();
        // reverse the helper function
        int row_index = snake_head / m_width;
        int col_index = snake_head % m_width;
        
        if(direction == "U") row_index--;
        else if (direction == "D") row_index++;
        else if (direction == "L") col_index--;
        else if (direction == "R") col_index++;

        // check the head is out of bounds
        if (row_index < 0 || row_index >= m_height || col_index < 0 || col_index >= m_width )
        {   
            // game over
            return -1;
        }

        // check the head is at food
        if (m_foodIndex < m_food.size() && row_index == m_food[m_foodIndex][0] && col_index == m_food[m_foodIndex][1])
        {
            m_score++;
            m_foodIndex++;
        }
        else
        {
            int snake_tail = snake.back();
            snake.pop_back();
            snake_positions.erase(snake_tail);
        }

        int new_snake_head = encode(row_index, col_index);

        // check the head hasn't ate itselt
        if (snake_positions.count(new_snake_head))
        {   
            // game over
            return -1;
        }

        snake.push_front(new_snake_head);
        snake_positions.insert(new_snake_head);

        return m_score;
    };

private:

    int m_width;
    int m_height;
    vector<vector<int>> m_food;
    int m_score;
    int m_foodIndex;
    deque<int> snake; // Stores the encoded positions of the snake parts
    unordered_set<int> snake_positions; // Tracks occupied positions by the snake

    // Helper function to encode 2D positions into a single integer
    int encode(int row, int col) {
        return row * m_width + col;
    }
};


int main(int argc, char** argv)
{
    SnakeGame game(3, 2, {{1,2}, {0,1}});
    
    std::cout << game.move("R") << std::endl;       // 0
    std::cout << game.move("D") << std::endl;       // 0
    std::cout << game.move("R") << std::endl;       // 1
    std::cout << game.move("U") << std::endl;       // 1
    std::cout << game.move("L") << std::endl;       // 2
    std::cout << game.move("U") << std::endl;       // -1

    return 0;
}
