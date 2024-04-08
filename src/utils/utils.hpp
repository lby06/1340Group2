#pragma once

#include <utility>

// Real-time keyboard input.
// Returns the ASCII value of the character input.
int readKeyboard();

// Generate random position.
std::pair<int, int> randomPosition();