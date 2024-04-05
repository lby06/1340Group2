#pragma once

#include <iostream>
#include <string>

void clear_screen();
int print_file(const std::string filename, int wait_time, bool clean);
std::string new_game();
void start_page();
int rename_slot();
int save();
void end();