#include "maze.hpp"

#include <iostream>

/**
 * @brief Refresh screen. And print the maze to the terminal.
 *
 * TODO: Apply modifications only to influenced cells (may be using other libs)
 */
void Maze::showMaze() {
    for (const auto &row : this->maze) {
        for (const auto &cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * @brief Read information from savings.
 *
 * @param saving_path Path to the savings file.
 */
void Maze::loadMaze(std::string saving_path) {}

/**
 * @brief Saves game info to savings file
 *
 */
void Maze::saveMaze() {}