#include "src/character/character.h"
#include "src/character/monster.h"
#include "src/maze/maze.hpp"
#include "src/ui/start_endpage.h"
#include "src/utils/utils.hpp"
#include <iostream>

int main() {
	Maze new_maze;
	main_character main_charac;
	std::vector<Monster> monsters;
	// 1. Show Greeting. (New Game/Continue)
	start_page();

	// TODO other logics

	// Main game.
	while (1) {
		new_maze.showMaze();
	}
}