/*
https://algo.monster/liteproblems/353
This problem asks you to implement a Snake game with the following rules and
requirements:

Game Setup:
The game is played on a screen with dimensions height x width
The snake starts at position (0, 0) (top-left corner) with length 1
Food items are provided as an array where food[i] = (ri, ci) represents the
row and column position of the i-th food piece

Game Mechanics:
When the snake eats food, both its length and the game score increase by 1
Food appears one at a time - the next food item only appears after the
current one is eaten Food is guaranteed to never appear on a position occupied
by the snake

Game Over Conditions:
The snake moves out of bounds (hits a wall)
The snake's head collides with its own body after moving

Implementation Requirements:

You need to implement a SnakeGame class with two methods:
SnakeGame(int width, int height, int[][] food): Constructor that initializes
the game with the screen dimensions and food positions

int move(String direction): Processes one move in the given direction ("U"
for up, "D" for down, "L" for left, "R" for right) and returns: The current
score if the move is valid -1 if the game is over (snake hits wall or itself)

The key challenge is tracking the snake's body positions efficiently while
handling the growth when eating food and checking for self-collision. The snake
moves by adding a new head position in the direction of movement and removing
the tail (unless food is eaten, in which case the tail remains to increase
length).
*/

// System includes
#include <algorithm>
#include <deque>
#include <string>
#include <unordered_set>
#include <vector>

// Project includes
#include <spdlog/fmt/ranges.h>
#include <spdlog/spdlog.h>

class SnakeGame {
public:
  // constructor
  // param[in] int board cell width
  // param[in] int board cell height
  // param[in] vector<vector<int>> food cells [[2,3], [1,1], [7,8]]
  SnakeGame(int width, int height, std::vector<std::vector<int>> food)
      : boardWidth(width), boardHeight(height), currentScore(0),
        snakeFood(food), foodIndex(0) {
    // starting snakeLength position
    snakeLength.push_front(0); // really Flattening {0,0}
    snakePositions.insert(0);
  }

  ~SnakeGame() = default;

  SnakeGame(SnakeGame &copy_constructor) = delete;
  SnakeGame(SnakeGame &&move_constructor) = delete;

  SnakeGame operator=(SnakeGame &copy_assignment) = delete;
  SnakeGame operator=(SnakeGame &&move_assignment) = delete;

  // Moves the snakeLength in the given direction. Returns the game score
  // param[in] string [U,D,LR]
  // param[out] int score. -1 if the game is over
  int move(std::string directon) {
    int snake_head = snakeLength.front();
    int new_row = snake_head / boardWidth;
    int new_col = snake_head % boardWidth;

    if (directon == "U") {
      new_row--;
    } else if (directon == "D") {
      new_row++;
    } else if (directon == "L") {
      new_col--;
    } else if (directon == "R") {
      new_col++;
    }

    spdlog::debug("Moved {}: {}:{}", directon, new_row, new_col);

    if (new_row >= boardHeight || new_row < 0 || new_col >= boardWidth ||
        new_col < 0) {
      // the snakeLength is outside the board size
      return -1;
    }

    if (foodIndex < snakeFood.size() && new_row == snakeFood[foodIndex][0] &&
        new_col == snakeFood[foodIndex][1]) {
      // the snakeLength found food
      foodIndex++;
      currentScore++;
    } else {
      //  remove the tail
      int tail_index = snakeLength.back();
      snakeLength.pop_back();
      snakePositions.erase(tail_index);
    }

    int head_index = FlattenIndex(new_row, new_col);
    if (snakePositions.count(head_index)) {
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
  int FlattenIndex(int row, int col) {
    // cell height * board width * cell width
    int index = row * boardWidth + col;

    spdlog::debug("Flatten Array value: {}:{} -> {}", row, col, index);

    return index;
  }
};

int main() {
  spdlog::set_level(spdlog::level::debug);
  spdlog::info("Design snakeLength Game");

  SnakeGame new_game = SnakeGame(3, 2, {{1, 2}, {0, 1}});

  spdlog::info("current score: {}", new_game.move("R"));
  spdlog::info("current score: {}", new_game.move("D"));
  spdlog::info("current score: {}", new_game.move("R"));
  spdlog::info("current score: {}", new_game.move("U"));
  spdlog::info("current score: {}", new_game.move("L"));
  spdlog::info("current score: {}", new_game.move("U"));
}