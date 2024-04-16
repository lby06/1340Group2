#pragma once

#include <random>
#include <utility>

static std::mt19937 rng(std::random_device{}());
// Real-time keyboard input.
// Returns the ASCII value of the character input.
int readKeyboard();

// Generate random position.
std::pair<int, int> randomPosition();