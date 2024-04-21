#include "src/character/character.h"
#include "src/character/monster.h"
#include "src/maze/maze.hpp"
#include "src/ui/start_endpage.h"
#include "src/utils/utils.hpp"
// #include <iostream>

int main() {
	start_page();
	/* INITIALIZATION HERE */
	Maze maze;

	maze.newMaze();

	// Create a main character for test.
	bool successfullyCreated = false;
	while (!successfullyCreated) {
		std::cerr << "Creating main character..." << std::endl;
		auto p = randomPosition();
		if (maze.whatIsThisCell(p.first, p.second) == 0) {
			successfullyCreated = true;
			cha1.setPosition(p.first, p.second);
		}
	}
	maze.addMainCharacter(cha1);

	// Create monsters for test.
	std::vector<Monster> monsters = createMonsters(kMaxNumberOfMonsters);
	maze.addMonsters(monsters);

	// Before entering game, user may have many operations (switching
	// between continue, saves, new game, etc.) auto saving = start_page();

	// Main game.
	while (1) {
		// Show board.
		system("clear");
		maze.showMaze();

		// Game process.

		// REMEMBER to check if user want to exit game.
		// and invoke save_saving function.

		// 0. Make a move
		int key = readKeyboard();
		maze.moveMainCharacter(key);
		// 1. Interact (if possible)

		// Invoke corresponding functions to perform interactions.
		// 1. Meet a monster
		if (maze.isMainCharacterEncounterMonster()) {
			// TODO
		}
		// 1.1 Fighs
		// (If we have) 2. Buffs/Traps/Treasure Chests/...
		// 3. Calculate new main character status

		// 3.1 Level up (and corresponding properties).

		// End game check.
		// 1. HP <= 0 (After fight)
		if (!cha1.is_alive()) {
			return 0;
		}
		// 2. Reach exit
		if (maze.isMainCharacterAtExit()) {
			// Create new maze.
			maze.newMaze();
			continue;

			// Create new monsters.
			monsters = createMonsters(kMaxNumberOfMonsters);
			maze.addMonsters(monsters);

			// system("clear");
			// std::cout << "You have reached the exit!" << std::endl;
		}
	}
}