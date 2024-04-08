#pragma once

#include "../character/character.h"
#include "../character/monster.h"

#include <string>
#include <vector>

// Defines the size of a maze.
static constexpr int kMaxMazeSizeWidth = 50;
static constexpr int kMaxMazeSizeLength = 50;

// Define the max number of monsters in each maze.
static constexpr int kMaxNumberOfMonsters = 10;

/**
 * @brief Defines the basic elements of each maze. It also enacts as the hub of
 * all the others.
 *
 * @details Contains `main character`, `game board`, collection of `monster`s
 *
 */
class Maze {
  private:
	// By default, `#` represents walls.
	std::vector<std::string> grid_;

	std::vector<Monster> monsters_; // Store monsters' info
	main_character main_character_; // Store main character's info

  public:
	void init_grid();
	std::vector<std::string> getGrid();
	void showMaze();
	void loadMaze();
	void saveMaze();

	// Create a new maze. (Entering a new level / New game)
	void newMaze();
};