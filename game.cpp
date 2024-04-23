// #include "src/battle/battle.h"
#include "src/battle/battle.h"
#include "src/character/character.h"
#include "src/character/monster.h"
#include "src/maze/maze.hpp"
#include "src/ui/saving_ui.hpp"
#include "src/ui/start_endpage.h"
#include "src/utils/utils.hpp"
#include <iostream>
// #include <iostream>

int main() {
	save_file tmp;
	Maze maze;
	int level;

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
		tmp.maze = maze.getExtendedGrid();

		level = 0;
	} else {
		// Load game.
		// Load character.
		cha1 = tmp.save_character;
		level = tmp.level;
		// Load maze.
		maze.loadMaze(tmp.maze);
		// Load monsters.
	}

	/* INITIALIZATION HERE */
	maze.addMainCharacter(cha1);

	maze.addMonsters(monsters);
	// Before entering game, user may have many operations (switching
	// between continue, saves, new game, etc.) auto saving = start_page();

	// Main game.
	while (1) {
		// Show board.
		system("clear");
		// std::cout << cha1.getPosition().first << ", "
		// 		  << cha1.getPosition().second << std::endl;
		maze.showMaze();

		// Game process.

		// REMEMBER to check if user want to exit game.
		// and invoke save_saving function.

		// 0. Make a move
		int key = readKeyboard();
		if (key == 'Q' || key == 'q') { // quit game
			// std::cout << cha1.getPosition().first << ", "
			// 		  << cha1.getPosition().second << std::endl;
			// save_file a;
			// parse_file("data/savings/sav.txt", a, 1);
			// std::cout << a.save_character.getPosition().first << ", "
			// 		  << a.save_character.getPosition().second << std::endl;
			exit(0);
		} else if (key == 'e' || key == 'E') { // show menu (save)
			tmp.save_character = cha1;

			// std::cout << tmp.username << std::endl;
			// getchar();

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
			// init monster before battle
			clo1.reset(level, 0);
			rob1.reset(level, 0);
			man1.reset(level, 0);
			cit1.reset(level, 0);

			battle_monster(cha1.level, tmp1.second);
			maze.winning();
		}
		// 1.1 Fighs
		// (If we have) 2. Buffs/Traps/Treasure Chests/...
		// 3. Calculate new main character status



		// End game check.
		// 1. HP <= 0 (After fight)
		if (!cha1.is_alive()) {
//should implement a end page 
			return 0;
		}
		// 2. Reach exit
		if (maze.isMainCharacterAtExit()) {
			level++;
			cha1.upgrade();		// 3.1 Level up (and corresponding properties). implemente here
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
