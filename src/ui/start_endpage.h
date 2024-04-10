#pragma once

#include <iostream>
#include <string>
#include "../character/character.h"
#include "../maze/maze.hpp"

// delete everything on the screen
void clear_screen();
// print an ascii painting
int print_file(const string filename, int wait_time, bool clean);
// continue from an existing saving point
void continue_game();
// extract and parse the saving file to continue the game
void parse_file(const string filename, save_file &s, int slot);
// start a new game
string new_game();
// init a start page where the player does what he wants
void start_page();
// enables the player to change the name of the saving file
int rename_slot();
// save the game
void save();
// exits the whole game
void end();
// to be continued
void main_game(save_file s);
// elements necessary for the body of the game
struct save_file{
    // struct of character
    main_character save_character;
    // struct of maze
    Maze save_maze;
    // int seed;   // needed if the maze will be generated from the beginning
    int slot_number;
    string username;
};