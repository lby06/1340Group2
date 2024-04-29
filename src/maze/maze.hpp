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
	/// Default constructor. Set pointers to null to avoid memory fatal error.
	Maze();
	// Get extended grid (i.e. filled with spaces), otherwise height is much
	// larger than width. Not suitable for display.
	std::vector<std::string> getExtendedGrid();

	/**
	 * @brief Refresh screen. And print the maze to the terminal, along with
	 * main character and monsters. (with colour highlighting)
	 *
	 */
	void showMaze();

	/**
	 * @brief Load a maze from `vector<string>`
	 * @deprecated This functionality is provided or has alternatives in `ui/`.
	 *
	 * @param m
	 */
	void loadMaze(std::vector<std::string> &);

	/**
	 * @brief Saves the maze to the file.
	 * @deprecated This functionality is provided or has alternative in `ui/`
	 *
	 */
	void saveMaze();

	/// @brief Adds pointer to main-game main character to interact with maze
	/// elements involving positions more conveniently
	/// @param main_character Main character in main game
	void addMainCharacter(main_character &);

	/**
	 * @brief Adds pointers to monsters. Purpose is the same as the above.
	 *
	 * @param monsters Monsters in main game.
	 */
	void addMonsters(std::vector<Monster> &);

	/**
	 * @brief Creates a new maze. Generate walls, and exit randomly.
	 *
	 */
	void newMaze();
	// Fill the maze with monsters
	void init_grid();
	// Randomize a grid.
	void randomGrid();
	/**
	 * @brief Return what is this cell (walls, main character, monster, exit)
	 *
	 * @param x
	 * @param y
	 * @return 1->main character;
	 * 2->monster;
	 * 3->wall;
	 * 4->exit;
	 * 0->empty cell
	 */
	char whatIsThisCell(int, int);
	/**
	 * @brief Accept a key from keyboard and move main character. This method
	 * invokes `main_character` class method.
	 *
	 * @param key key read from keyboard
	 */
	void moveMainCharacter(int);
	/**
	 * @brief Invoked after each move. Check if main character is at the exit
	 * and satisfy maze-clearing condition (defeat more than 7 monsters).
	 *
	 * @return true Yes.
	 * @return false No.
	 */
	bool isMainCharacterAtExit();
	/**
	 * @brief Only invoked after battle. Remove the monster defeated, by
	 * checking position collapse.
	 *
	 */
	void winning();
	/**
	 * @brief Check if the main character encounters a monster.
	 *
	 * @return Return a pair of bool and string. First element indicates whether
	 * encounters (true: encounter), second element indicates the genre of
	 * monster (needed by the battle part)
	 */
	std::pair<bool, std::string> isMainCharacterEncounterMonster();
};