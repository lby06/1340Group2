#include "maze.hpp"
#include "../utils/utils.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>

// Defines the size of a maze.
int kMaxMazeSizeWidth = 30;
int kMaxMazeSizeHeight = 30;

// Define the max number of monsters in each maze.
int kMaxNumberOfMonsters = 10;

// [Deprecated]
// Generate path to saving files.
const std::string kPathPrefix = "./data/savings/sav";
const std::string kPathSuffix = ".dat";
std::string constructPath(int i) {
	return kPathPrefix + std::to_string(i) + kPathSuffix;
}

/// Default constructor. Set pointers to null to avoid memory fatal error.
Maze::Maze() : main_character_(nullptr), monsters_(nullptr) {}

/// @brief Adds pointer to main-game main character to interact with maze
/// elements involving positions more conveniently
/// @param main_character Main character in main game
void Maze::addMainCharacter(main_character &main_character) {
	this->main_character_ = &main_character;
}

/**
 * @brief Adds pointers to monsters. Purpose is the same as the above.
 *
 * @param monsters Monsters in main game.
 */
void Maze::addMonsters(std::vector<Monster> &monsters) {
	this->monsters_ = &monsters;

	// Check position validity
	for (auto &monster : monsters) {
		while (1) {
			auto tmp = monster.getPosition();
			if (whatIsThisCell(tmp.first, tmp.second) == 3 ||
				whatIsThisCell(tmp.first, tmp.second) == 4 ||
				tmp == main_character_->getPosition()) {
				// If not ok, generate new position
				auto new_pos = randomPosition();
				monster.setPosition(new_pos.first, new_pos.second);
			} else {
				break;
			}
		}
	}
}

/**
 * @brief Return what is this cell (walls, main character, monster, exit)
 *
 * @param x
 * @param y
 * @return 1->main character;
 * 2->monster;
 * 3->wall;
 * 4->exit;
 * 0->empty cell
 */
char Maze::whatIsThisCell(int x, int y) {
	// is it main charac?
	if (main_character_ != nullptr) {
		auto tmp = main_character_->getPosition();
		if (x == tmp.first && y == tmp.second) {
			return 1;
		}
	}

	// is it a monster?
	if (monsters_ != nullptr) {
		for (auto &monster : *monsters_) {
			auto tmp = monster.getPosition();
			if (x == tmp.first && y == tmp.second) {
				return 2;
			}
		}
	}

	// is it a wall?
	if (this->grid_[x][y] == '#') {
		return 3;
	}

	// Is it an exit?
	if (this->grid_[x][y] == '@') {
		return 4;
	}

	// empty
	return 0;
}

/**
 * @brief Accept a key from keyboard and move main character. This method
 * invokes `main_character` class method.
 *
 * @param key key read from keyboard
 */
void Maze::moveMainCharacter(int key) {
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

/**
 * @brief Check if the main character encounters a monster.
 *
 * @return Return a pair of bool and string. First element indicates whether
 * encounters (true: encounter), second element indicates the genre of monster
 * (needed by the battle part)
 */
std::pair<bool, std::string> Maze::isMainCharacterEncounterMonster() {
	auto tmp = main_character_->getPosition();
	int x = tmp.first, y = tmp.second;
	for (auto &monster : *monsters_) {
		auto tmp = monster.getPosition();
		if (x == tmp.first && y == tmp.second) {
			return {true, monster.genre_};
		}
	}
	return {false, "-1"};
}

/**
 * @brief Only invoked after battle. Remove the monster defeated, by checking
 * position collapse.
 *
 */
void Maze::winning() {
	for (auto it = monsters_->begin(); it != monsters_->end();) {
		if (it->getPosition().first == main_character_->getPosition().first &&
			it->getPosition().second == main_character_->getPosition().second) {
			it = monsters_->erase(it);
		} else {
			++it;
		}
	}
}

/**
 * @brief Invoked after each move. Check if main character is at the exit and
 * satisfy maze-clearing condition (defeat more than 7 monsters).
 *
 * @return true Yes.
 * @return false No.
 */
bool Maze::isMainCharacterAtExit() {
	auto tmp = main_character_->getPosition();
	int x = tmp.first, y = tmp.second;
	return this->grid_[x][y] == '@' && this->monsters_->size() <= 3;
}

/**
 * @brief Refresh screen. And print the maze to the terminal, along with main
 * character and monsters. (with colour highlighting)
 *
 */
void Maze::showMaze() {

	/* Print Helper */
	std::cout << "Press [w] to move up, [s] to move down, [a] to move left, "
				 "[d] to move right, [q] to quit, [e] to show menu."
			  << std::endl;

	// Print current EXP.
	std::cout << "\tCurrent EXP: " << main_character_->EXP() << std::endl;

	for (int i = 0; i < kMaxMazeSizeWidth; i++) {
		for (int j = 0; j < kMaxMazeSizeHeight; j++) {
			bool isCharacter = false;

			// If is the position of main character, print it.
			if (main_character_ != nullptr) {
				auto tmp = main_character_->getPosition();
				if (i == tmp.first && j == tmp.second) {
					std::cout << "\033[5;32m"
							  << "U"
							  << "\033[0m";
					isCharacter = 1;
					continue;
				}
			}

			// If is the position of a monster, print it.
			if (monsters_ != nullptr) {
				for (auto &monster : *monsters_) {
					auto tmp = monster.getPosition();
					if (i == tmp.first && j == tmp.second) {
						std::cout << "\033[31m" << monster.genre_[0]
								  << "\033[0m";
						isCharacter = 1;
						break;
					}
				}
			}

			if (!isCharacter) {
				if (this->grid_[i][j] == '@')
					std::cout << "\033[5;33m" << this->grid_[i][j] << "\033[0m";
				else
					std::cout << this->grid_[i][j];
			}
		}
		std::cout << std::endl;
	}
}
/**
 * @brief Load a maze from `vector<string>`
 * @deprecated This functionality is provided or has alternatives in `ui/`.
 *
 * @param m
 */
void Maze::loadMaze(std::vector<std::string> &m) {
	// Select a save.
	// TODO let user select saveID.
	this->grid_ = m;
}

/**
 * @brief Saves the maze to the file.
 * @deprecated This functionality is provided or has alternative in `ui/`
 *
 */
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
			// extended_row.push_back(' ');
		}
		extended_grid.push_back(extended_row);
	}
	return extended_grid;
}

/**
 * @brief Creates a new maze. Generate walls, and exit randomly.
 *
 */
void Maze::newMaze() {
	// Clear.
	this->grid_.clear();

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

	// Generate entrance and exit.
	while (1) {
		auto tmp = randomPosition();
		// Not wall or main character or monster.
		if (this->whatIsThisCell(tmp.first, tmp.second) == 0) {
			this->grid_[tmp.first][tmp.second] = '@';
			break;
		}
	}
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
			if (rng() % 20 < 2) {
				this->grid_[i][j] = '#';
			}
		}
	}
}

// // FUNCTION TEST
// int main() {
// 	Maze maze;
// 	// main_character tmp;

// 	maze.newMaze();

// 	// Create a main character for test.
// 	bool successfullyCreated = false;
// 	while (!successfullyCreated) {
// 		std::cerr << "Creating main character..." << std::endl;
// 		auto p = randomPosition();
// 		if (maze.whatIsThisCell(p.first, p.second) == 0) {
// 			successfullyCreated = true;
// 			cha1.setPosition(p.first, p.second);
// 		}
// 	}
// 	maze.addMainCharacter(cha1);

// 	// Create monsters for test.
// 	std::vector<Monster> monsters;
// 	for (int i = 0; i < 10; i++) {
// 		Monster monster;
// 		bool successfullyCreated = false;
// 		while (!successfullyCreated) {
// 			auto p = randomPosition();
// 			if (maze.whatIsThisCell(p.first, p.second) == 0) {
// 				successfullyCreated = true;
// 				monster.setPosition(p.first, p.second);
// 			}
// 		}
// 		monsters.push_back(monster);
// 	}
// 	maze.addMonsters(monsters);

// 	while (1) {
// 		system("clear");
// 		maze.showMaze();
// 		int key = readKeyboard();
// 		if (key == 'q') {
// 			exit(0);
// 		} else if (key == 'e') {
// 		}
// 		maze.moveMainCharacter(key);

// 		if (maze.isMainCharacterAtExit()) {
// 			maze.newMaze();
// 			// continue;
// 			// system("clear");
// 			// std::cout << "You have reached the exit!" << std::endl;
// 			// break;
// 		}
// 	}

// 	return 0;
// }
