#include "utils.hpp"
#include "../maze/maze.hpp"

// #include <cstdlib>
// #include <ctime>
// #include <iostream>
#include <random>
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

	if (in == 27) { // [esc] is pressed
	}

	return in;
}

// Generate random position.
std::pair<int, int> randomPosition() {
	return std::make_pair(rng() % 48 + 1, rng() % 48 + 1);
}

// FUNCTION TEST
// int main() {
// 	// while (1) {
// 	// 	std::cout << "Retrieved input: " << char(readKeyboard()) << std::endl;
// 	// }
// 	auto pr = randomPosition();
// 	std::cout << pr.first << " " << pr.second << std::endl;
// }