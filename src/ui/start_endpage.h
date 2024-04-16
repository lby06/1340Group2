#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "../character/character.h"
#include "../maze/maze.hpp"
struct save_file{
    // struct of character
    main_character save_character;
    // struct of maze
	std::vector<std::string> maze;
	// int seed;
	// Needed if the maze will be generated from the beginning
    int slot_number;
	std::string username;
};

void clear_screen();
int print_file(const std::string filename, int wait_time, bool clean);
std::pair<int, save_file> continue_or_modify_saving();

// Read player info.
void parse_file(const std::string filename, save_file &s, int slot);
std::string new_game();
void save();
save_file start_page();
int rename_slot();
void end();
bool main_game(save_file s, Maze &, main_character &, std::vector<Monster> &);
