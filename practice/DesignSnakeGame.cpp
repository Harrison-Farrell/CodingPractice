// System includes
#include <algorithm>
#include <vector>
#include <string>
#include <deque>
#include <unordered_set>

// Project includes
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ranges.h>

class SnakeGame
{
    public: 
    // constructor
    // param[in] int board cell width
    // param[in] int board cell height
    // param[in] vector<vector<int>> food cells [[2,3], [1,1], [7,8]]
    SnakeGame(int width, int height, std::vector<std::vector<int>> food)
    : boardWidth(width), boardHeight(height), currentScore(0), snakeFood(food), foodIndex(0)
    {
        // starting snakeLength position
        snakeLength.push_front(0);        // really Flattening {0,0}
        snakePositions.insert(0);
    }

    ~SnakeGame() = default;

    SnakeGame(SnakeGame& copy_constructor) = delete;
    SnakeGame(SnakeGame&& move_constructor) = delete;

    SnakeGame operator=(SnakeGame& copy_assignment) = delete;
    SnakeGame operator=(SnakeGame&& move_assignment) = delete;

    // Moves the snakeLength in the given direction. Returns the game score 
    // param[in] string [U,D,LR]
    // param[out] int score. -1 if the game is over
    int move(std::string directon)
    {
        int snake_head = snakeLength.front();
        int new_row = snake_head / boardWidth;
        int new_col = snake_head % boardWidth;

        if(directon == "U")
        {
            new_row--;   
        }else if(directon == "D")
        {
            new_row++;
        }else if(directon == "L")
        {
            new_col--;
        }else if (directon == "R")
        {
            new_col++;
        }

        spdlog::debug("Moved {}: {}:{}", directon, new_row, new_col);
        
        if(new_row >= boardHeight || new_row < 0 || new_col >= boardWidth || new_col < 0)
        {
            // the snakeLength is outside the board size
            return -1;
        }

        if(foodIndex < snakeFood.size() && new_row == snakeFood[foodIndex][0] && new_col == snakeFood[foodIndex][1])
        {
            // the snakeLength found food
            foodIndex++;
            currentScore++;
        }else
        {
            //  remove the tail
            int tail_index = snakeLength.back();
            snakeLength.pop_back();
            snakePositions.erase(tail_index);
        }

        int head_index = FlattenIndex(new_row, new_col);
        if(snakePositions.count(head_index))
        {
            // the snakeLength as ran into itself
            return -1;
        }

        snakeLength.push_front(head_index);
        snakePositions.insert(head_index);
        return currentScore;
    };

    private:
    int boardWidth;
    int boardHeight;
    int currentScore;
    int foodIndex;
    std::vector<std::vector<int>> snakeFood;
    std::deque<int> snakeLength;
    std::unordered_set<int> snakePositions;

    // help function
    // param[in] int row value
    // param[in] int col value
    // param[out] int 1d array value Z
    int FlattenIndex(int row, int col)
    {
        // cell height * board width * cell width
        int index = row * boardWidth + col;

        spdlog::debug("Flatten Array value: {}:{} -> {}", row, col, index);

        return index;
    }
};

int main()
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Design snakeLength Game");

    SnakeGame new_game = SnakeGame(3,2, {{1,2}, {0,1}});

    spdlog::info("current score: {}", new_game.move("R"));
    spdlog::info("current score: {}", new_game.move("D"));
    spdlog::info("current score: {}", new_game.move("R"));
    spdlog::info("current score: {}", new_game.move("U"));
    spdlog::info("current score: {}", new_game.move("L"));
    spdlog::info("current score: {}", new_game.move("U"));
}