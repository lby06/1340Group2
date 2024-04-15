#include "maze.hpp"
#include "../utils/utils.hpp"

#include <fstream>
#include <iostream>
#include <string>

// Defines the size of a maze.

int kMaxMazeSizeWidth = 20;
int kMaxMazeSizeHeight = 20;

// Define the max number of monsters in each maze.
int kMaxNumberOfMonsters = 10;

const std::string kPathPrefix = "./data/savings/sav";
const std::string kPathSuffix = ".dat";
std::string constructPath(int i) {
	return kPathPrefix + std::to_string(i) + kPathSuffix;
}

Maze::Maze() : main_character_(nullptr), monsters_(0, nullptr) {
	// TODO for testing only, need delete it.
}

char Maze::whatIsThisCell(int x, int y) {
	// is it main charac?
	auto tmp = main_character_->getPosition();
	if (x == tmp.first && y == tmp.second) {
		return 1;
	}

	// is it a monster?
	for (const auto &monster : monsters_) {
		auto tmp = monster->getPosition();
		if (x == tmp.first && y == tmp.second) {
			return 2;
		}
	}

	// is it a wall?
	if (this->grid_[x][y] == '#') {
		return 3;
	}

	// empty
	return 0;
}

// Read a key from keyboard and move main character.
void Maze::moveMainCharacter() {
	char key = readKeyboard();
	auto tmp = main_character_->getPosition();
	int x = tmp.first, y = tmp.second;
	switch (key) {
	case 'w':
	case 'W':
		if (this->whatIsThisCell(x - 1, y) != 3) {
			main_character_->setPosition(x - 1, y);
		}
		break;
	case 's':
	case 'S':
		if (this->whatIsThisCell(x + 1, y) != 3) {
			main_character_->setPosition(x + 1, y);
		}
		break;
	case 'a':
	case 'A':
		if (this->whatIsThisCell(x, y - 1) != 3) {
			main_character_->setPosition(x, y - 1);
		}
		break;
	case 'd':
	case 'D':
		if (this->whatIsThisCell(x, y + 1) != 3) {
			main_character_->setPosition(x, y + 1);
		}
		break;
	default:
		break;
	}
}

// Check if the main character encounter a monster. (Then triggers a battle)
bool Maze::isMainCharacterEncounterMonster() {
	auto tmp = main_character_->getPosition();
	int x = tmp.first, y = tmp.second;
	for (const auto &monster : monsters_) {
		auto tmp = monster->getPosition();
		if (x == tmp.first && y == tmp.second) {
			return true;
		}
	}
	return false;
}

// Refresh screen. And print the maze to the terminal.
void Maze::showMaze() {
	for (int i = 0; i < kMaxMazeSizeWidth; i++) {
		for (int j = 0; j < kMaxMazeSizeHeight; j++) {
			bool isCharacter = false;
			// If is the position of main character, print it.
			auto tmp = main_character_->getPosition();
			if (i == tmp.first && j == tmp.second) {
				std::cout << "人"
						  << " ";
				isCharacter = 1;
				continue;
			}

			// If is the position of a monster, print it.
			for (const auto &monster : monsters_) {
				auto tmp = monster->getPosition();
				if (i == tmp.first && j == tmp.second) {
					std::cout << "怪"
							  << " ";
					isCharacter = 1;
					break;
				}
			}

			if (!isCharacter) std::cout << this->grid_[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
// Read information from savings.
void Maze::loadMaze(std::vector<std::string> &m) {
	// Select a save.
	// TODO let user select saveID.
	this->grid_ = m;
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

		// Close file.
		fout.close();
	}
}

// Get extended grid.
std::vector<std::string> Maze::getExtendedGrid() {
	std::vector<std::string> extended_grid;
	for (const auto &row : this->grid_) {
		std::string extended_row;
		for (const auto &ch : row) {
			// extended_row.push_back(' ');
			extended_row.push_back(ch);
			extended_row.push_back(' ');
		}
		extended_grid.push_back(extended_row);
	}
	return extended_grid;
}

// Create a new maze.
void Maze::newMaze() {
	// Fill border with walls. ('#')
	for (int i = 0; i < kMaxMazeSizeHeight; i++) {
		std::string row;
		for (int j = 0; j < kMaxMazeSizeWidth; j++) {
			if (i == 0 || i == kMaxMazeSizeHeight - 1 || j == 0 ||
				j == kMaxMazeSizeWidth - 1) {
				row.push_back('#');
			} else {
				row.push_back(' ');
			}
		}
		this->grid_.push_back(row);
	}

	// Randomly generate walls inside grid.
	this->randomGrid();
}

// Randomize some walls inside the grid.
void Maze::randomGrid() {
	// Randomly generate walls inside grid.
	for (int i = 0; i < kMaxMazeSizeHeight; i++) {
		for (int j = 0; j < kMaxMazeSizeWidth; j++) {
			if (i == 0 || i == kMaxMazeSizeHeight - 1 || j == 0 ||
				j == kMaxMazeSizeWidth - 1) {
				continue;
			}
			if (rand() % 20 < 3) {
				this->grid_[i][j] = '#';
			}
		}
	}
}

// // FUNCTION TEST
int main() {
	Maze maze;
	// auto p =
	// 	std::vector<std::string>{"#####", "#   #", "#   #", "#   #", "#####"};
	// maze.loadMaze(p);
	// for (const auto &line : maze.getExtendedGrid()) {
	// 	std::cout << line << std::endl;
	// }
	maze.newMaze();
	maze.showMaze();
	return 0;
}