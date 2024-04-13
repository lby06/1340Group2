#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "../character/character.h"
#include "../maze/maze.hpp"

void clear_screen();
int print_file(const string filename, int wait_time, bool clean);
void continue_game();
void parse_file(const string filename, save_file &s, int slot);
string new_game();
void start_page();
int rename_slot();
void save();
void end();
void main_game(save_file s);
struct save_file{
    // struct of character
    main_character save_character;
    // struct of maze
    vector<string> maze;
    // int seed;   // needed if the maze will be generated from the beginning
    int slot_number;
    string username;
};