// #include "src/battle/battle.h"
#include "src/character/character.h"
#include "src/character/monster.h"
#include "src/maze/maze.hpp"
#include "src/ui/saving_ui.hpp"
#include "src/ui/start_endpage.h"
#include "src/utils/utils.hpp"
// #include <iostream>

int main() {
	save_file tmp;
	Maze maze;

	auto new_game_verdict = start_page(tmp);
	std::vector<Monster> monsters = createMonsters(kMaxNumberOfMonsters);

	if (new_game_verdict == 1) {
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
		maze.addMonsters(monsters);
	} else {
		// Load game.
		// Load character.
		cha1 = tmp.save_character;
		// Load maze.
		maze.loadMaze(tmp.maze);
		maze.addMainCharacter(cha1);
		// Load monsters.
		maze.addMonsters(monsters);
	}
	// std::cout << "Hello, world!" << std::endl;
	/* INITIALIZATION HERE */

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
		if (key == 'Q' || key == 'q') { // quit game
			exit(0);
		} else if (key == 'e' || key == 'E') { // show menu (save)
			SavingsUI ui;
			ui.loadEntries();
			ui.loadSavingfile(tmp);
			ui.display();
			ui.saveEntries();
			// std::cerr << "Successfully saved the game.\n";
			continue;
		}
		maze.moveMainCharacter(key);
		// 1. Interact (if possible)

		// Invoke corresponding functions to perform interactions.
		// 1. Meet a monster
		auto tmp1 = maze.isMainCharacterEncounterMonster();
		if (tmp1.first) {
			// battle_monster(std::to_string(cha1.level), tmp.second);
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
			cha1.upgrade();
			// Create new maze.
			maze.newMaze();

			tmp.maze = maze.getExtendedGrid();

			// Create new monsters.
			monsters = createMonsters(kMaxNumberOfMonsters);
			maze.addMonsters(monsters);
			continue;

			// system("clear");
			// std::cout << "You have reached the exit!" << std::endl;
		}
	}
	return 0;
}