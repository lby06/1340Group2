#pragma once

/**
 * @brief Defines the basic elements of each maze.
 *
 */
#include <array>
#include <string>
#include <vector>

// Defines the size of a maze
const int MAX_MAZE_SIZE_WIDTH = 50;
const int MAX_MAZE_SIZE_LENGTH = 50;

class Maze {
  private:
    std::array<std::array<char, MAX_MAZE_SIZE_LENGTH>, MAX_MAZE_SIZE_WIDTH> maze;
    /// TODO: Finish definition of arrays of monsters and characters
    // std::vector<> monsters; // To store monsters' info

  public:
    void showMaze();
    void loadMaze(std::string);
    void saveMaze();
};