#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "../character/character.h"
#include "../maze/maze.hpp"
struct save_file{
	int level;
	// struct of character
    main_character save_character;
    // struct of maze
	std::vector<std::string> maze;
	// int seed;
	// Needed if the maze will be generated from the beginning
    int slot_number;
	std::string username;

	save_file(const save_file &sf) {
		save_character = sf.save_character;
		maze = sf.maze;
		slot_number = sf.slot_number;
		username = sf.username;
	}
	save_file() {}
};

void clear_screen();
int print_file(const std::string filename, int wait_time, bool clean);
int continue_or_modify_saving(save_file &s);

// Read player info.
void parse_file(const std::string filename, save_file &s, int slot);
std::string new_game();
void save(save_file &s, int slot);
int start_page(save_file &s);
void end();
bool main_game(save_file s, Maze &, main_character &, std::vector<Monster> &);
