#pragma once

#include "../character/character.h"
#include "../character/monster.h"

#include <string>
#include <vector>

extern int kMaxMazeSizeWidth, kMaxMazeSizeHeight, kMaxNumberOfMonsters;

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

	std::vector<Monster> *monsters_;  // Store monsters' info
	main_character *main_character_;  // Store main character's info

  public:
	Maze();
	// Get extended grid (i.e. filled with spaces), otherwise height is much
	// larger than width. Not suitable for display.
	std::vector<std::string> getExtendedGrid();
	// Deprecated. As API is provided in `battle/print_features.h`.
	void showMaze();
	// Load the maze from loaded.
	void loadMaze(std::vector<std::string> &);
	// Save the maze to data file.
	void saveMaze();
	// Manage the main character pointer.
	void addMainCharacter(main_character &);
	// Manage the monsters pointer.
	void addMonsters(std::vector<Monster> &);
	// Create a new maze. (Entering a new level / New game)
	void newMaze();
	// Fill the maze with monsters
	void init_grid();
	// Randomize a grid.
	void randomGrid();
	// What is this cell.
	char whatIsThisCell(int, int);
	// Read a key and move main character.
	void moveMainCharacter(int);
	// Check if the main character is at the exit.
	bool isMainCharacterAtExit();
	// Check if the main character is at the entrance.
	bool isMainCharacterAtEntrance();
	// Check if the main character encounters a monster.
	bool isMainCharacterEncounterMonster();
};