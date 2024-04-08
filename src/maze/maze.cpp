#include "maze.hpp"

#include <fstream>
#include <iostream>
#include <string>

const std::string kPathPrefix = "./data/savings/sav";
const std::string kPathSuffix = ".dat";
std::string constructPath(int i) {
	return kPathPrefix + std::to_string(i) + kPathSuffix;
}

// Refresh screen. And print the maze to the terminal.
void Maze::showMaze() {
    for (const auto &row : this->grid_) {
        for (const auto &cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}

// Read information from savings.
void Maze::loadMaze() {
	// Select a save.
	// TODO let user select saveID.
	int saveID = 1;

	// Retrieve save path.
	auto path = constructPath(saveID);

	std::ifstream fin(path);
	if (!fin.is_open()) {
		std::cerr << "Error: Cannot open file." << std::endl;
		return;
	}

	// 1. Load maze.
	std::string line;
	this->grid_.clear();
	while (std::getline(fin, line)) {
		this->grid_.push_back(line);
	}

	// 2. Load main character.
	// 3. Load monsters.
}

// Saves maze to saving.
void Maze::saveMaze() {
	// Whether covers an existing save or saves to a new empty save.
	bool save_to_new = true;
	// TODO Invoke new UI to let the user decide.

	if (save_to_new) {
		// Opens new file
		std::ofstream fout("./data/savings");

		// Fails to open file.
		if (!fout.is_open()) {
			std::cerr << "Error: Cannot open file." << std::endl;
			return;
		}

		// 1. Write maze.
		for (const auto &row : this->grid_) {
			fout << row << std::endl;
		}

		// 2. Write main character.
		// 3. Write monsters.
	}
}

// Get grid.
std::vector<std::string> Maze::getGrid() { return this->grid_; }

// Create a new maze.
void Maze::newMaze() {
	// TODO
}