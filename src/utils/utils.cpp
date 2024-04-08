#include "utils.hpp"
#include "../maze/maze.hpp"

#include <cstdlib>
#include <ctime>
// #include <iostream>
#include <termio.h>

int readKeyboard() {
	int in;
	struct termios new_settings, stored_settings;

	tcgetattr(0, &stored_settings);
	new_settings = stored_settings;
	new_settings.c_lflag &= (~ICANON);
	new_settings.c_lflag &= (~ECHO); // Disable output
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &new_settings);

	in = getchar();

	tcsetattr(0, TCSANOW, &stored_settings);
	return in;
}

// Generate random position.
std::pair<int, int> randomPosition() {
	srand(time(NULL)); // Set seed
	return std::make_pair(rand() % kMaxMazeSizeWidth,
						  rand() % kMaxMazeSizeHeight);
}

// FUNCTION TEST
// int main() {
// 	// while (1) {
// 	// 	std::cout << "Retrieved input: " << char(readKeyboard()) << std::endl;
// 	// }
// 	auto pr = randomPosition();
// 	std::cout << pr.first << " " << pr.second << std::endl;
// }