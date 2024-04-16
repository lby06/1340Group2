#include "src/character/character.h"
#include "src/character/monster.h"
#include "src/maze/maze.hpp"
#include "src/ui/start_endpage.h"
#include "src/utils/utils.hpp"
#include <iostream>

int main() {
	/* INITIALIZATION HERE */
	Maze maze;
	main_character main_charac;
	std::vector<Monster> monsters;

	// Before entering game, user may have many operations (switching between
	// continue, saves, new game, etc.)
	bool starts_game = false;
	while (!starts_game) {
	}

	// Main game.
	while (starts_game) {
		// Show board.
		maze.showMaze();

		// Game process.

		// REMEMBER to check if user want to exit game.
		// and invoke save_saving function.

		// 0. Make a move
		// 1. Interact (if possible)

		// Invoke corresponding functions to perform interactions.
		// 1. Meet a monster
		// 1.1 Fight
		// (If we have) 2. Buffs/Traps/Treasure Chests/...
		// 3. Calculate new main character status
		// 3.1 Level up (and corresponding properties).

		// End game check.
		// 1. HP <= 0 (After fight)
		// 2. Reach exit
	}
}