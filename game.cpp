#include "src/maze/maze.hpp"
#include "src/ui/start_endpage.h"
#include "src/utils/utils.hpp"
#include <iostream>

int main() {
	Maze new_maze;
	// 1. Show Greeting. (New Game/Continue)
	start_page();

	// TODO other logics

	// Main game.
	while (1) {
		new_maze.showMaze();
	}
}