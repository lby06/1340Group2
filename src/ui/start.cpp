#include "../character/character.h"
#include "../utils/utils.hpp"
#include "start_endpage.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <utility>
#include <vector>
using namespace std;

void clear_screen() {
#ifdef _WIN32
	system("CLS"); // 奇形怪状的bug
#elif __unix__
	system("clear"); // 正常
#endif
}

// Print a line with padding.
void printPadded(const string &s, int padding) {
	cout << string(padding, ' ') << s << endl;
};

// Non-interactive print screen.
int print_file(const string filename, int wait_time, bool clean) {
	ifstream file;
	string line;
	file.open(filename.c_str());
	if (file.fail()) {
		cout << "error: file not found" << endl;
		exit(1);
	}
	if (clean) clear_screen();
	while (getline(file, line)) {
		cout << line << endl;
	}
	file.close();
	this_thread::sleep_for(
		chrono::seconds(wait_time)); // windows 上无法运行, linux 上正常
	return line.size();
}

/// Starts a new game, including animation, starting page.
string new_game() {
	// Loading Animation
	print_file("data/scripts/ascii_images/sith_code.txt", 8, true);
	print_file("data/scripts/ascii_images/script1.txt", 10, true);

	string name;
	bool valid = false;
	do {
		// Starting page
		print_file("data/scripts/ascii_images/computer.txt", 0, true);
		// cin.ignore();
		cout << "Enter your name (no more than 10 chars): ";
		getline(cin, name);

		if (name.size() < 11) {
			valid = true;

			// Story Introduction
			ifstream file_in("data/scripts/ascii_images/script3.txt");
			vector<string> lines;
			string line;
			while (getline(file_in, line)) {
				lines.push_back(line);
			}
			file_in.close();
			lines[25] = "  \"" + name + ", my most unlikely servant. Your ";

			// Store user name to file
			ofstream file_out("data/scripts/ascii_images/script3.txt");
			if (file_out.fail()) {
				cout << "error: file not found" << endl;
				exit(1);
			}
			for (const string &line : lines) {
				file_out << line << "\n";
			}
			file_out.close();

			ifstream fin("data/scripts/ascii_images/luke_skywalker.txt");
			vector<string> sec_lines;
			string sec_line;
			while (getline(fin, sec_line)) {
				sec_lines.push_back(sec_line);
			}
			fin.close();

			// REVIEW - [17]: out of index error?
			sec_lines[17] = "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⣿⣿⡿⣿⣿⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
							"          ****  " +
							name + "  ****";

			ofstream fout("data/scripts/ascii_images/luke_skywalker.txt");
			if (fout.fail()) {
				cout << "error: file not found" << endl;
				exit(1);
			}
			for (const string &sec_line : sec_lines) {
				fout << sec_line << "\n";
			}
			fout.close();
		}
	} while (!valid);
	print_file("data/scripts/ascii_images/luke_skywalker.txt", 4, true);
	print_file("data/scripts/ascii_images/script3.txt", 6, true);
	// main_game(choice);
	return name;
}

// Delete a slot of saving.
int delete_slot(int slot) {
	// int slot;
	// bool valid = false;

	// while (!valid) {
	// 	cout << "Enter the number of the slot you want to delete: ";
	// 	cin >> slot;
	// 	if (slot == 1 || slot == 2 || slot == 3) {
	// 		valid = true;
	// 	} else {
	// 		cout << "Invalid slot number.\n";
	// 	}
	// }

	ifstream file_in("data/scripts/ascii_images/save.txt");
	vector<string> lines;
	string line;
	while (getline(file_in, line)) {
		lines.push_back(line);
	}
	file_in.close();
	lines[2 * slot - 1] =
		lines[2 * slot - 1].substr(0, 11) + "Slot " + to_string(slot);

	ofstream file_out("data/scripts/ascii_images/save.txt");
	if (file_out.fail()) {
		cout << "error: file not found" << endl;
		return slot;
	}
	for (const string &line : lines) {
		file_out << line << "\n";
	}
	file_out.close();

	return slot;
}

// Choose a slot and continue gaming.
// Returns verdict and `save_file`. -1 if user wants to exit. 1 if ok.
int continue_or_modify_saving(save_file &s) {
	// Show all options.
	vector<string> options = {"Slot 1", "Slot 2", "Slot 3"};

	int slot = 0;
	int padding = 3;
	bool confirmed = false;

	while (!confirmed) {
		clear_screen();
		// Show cursor movement help tips.
		printPadded(
			"Press [W] to move up, [S] to move down, [C] to confirm, "
			"[ESC] to get back, [D] to delete saving, [R] to rename saving.",
			0);
		// Upper padding
		cout << "\n\n";
		// Show options
		for (int i = 0; i < (int)options.size(); i++) {
			printPadded("+---+", padding);
			string tmp;
			if (slot == i) {
				tmp = "| > |";
			} else {
				tmp = "|   |";
			}
			// TODO Add brief info (username)
			printPadded(tmp + "   " + options[i], padding);
			printPadded("+---+", padding);
		}
		// Read key
		int key = readKeyboard();
		if (key == 'W' || key == 'w') {
			slot = (slot - 1 + options.size()) % options.size();
		} else if (key == 'S' || key == 's') {
			slot = (slot + 1) % options.size();
		} else if (key == 'C' || key == 'c') {
			confirmed = true;
		} else if (key == 27) {
			confirmed = true;
			return -1;
		} else if (key == 'D' || key == 'd') {
			delete_slot(slot + 1);
		}
	}

	// Load stored setting to main game
	// std::cerr << "OK1\n";
	parse_file("data/savings/sav.txt", s, slot + 1);
	// std::cerr << "OK7\n";
	// debug save file s
	// cout << s.save_character.level << endl;
	// for (auto &x : s.maze) {
	// 	cout << x << endl;
	// }
	return 1; // return stored settings
}

/// Read information from files.
void parse_file(const string filename, save_file &s, int slot) {
	ifstream fin;
	fin.open(filename.c_str());

	// Check if saving file is opened succussfully
	if (fin.fail()) {
		cerr << "error: file not found" << endl;
		return;
	}

	double parameters[20];
	vector<string> lines;
	vector<string> maze;
	string username, line;
	bool valid = false;

	while (getline(fin, line)) {
		if (line.substr(0, 7) == "@slot " + to_string(slot)) {
			valid = true;
		} else if (line.substr(0, 7) == "@slot " + to_string(slot + 1)) {
			break;
		}
		if (valid) {
			lines.push_back(line);
		}
	}
	int temp_m;
	for (int i = 0; i < lines.size(); i++) {
		if (i > 1 && i < 22) {
			parameters[i - 2] = stod(lines[i]);
		} else if (i >= 23 && i <= 72) {
			maze.push_back(lines[i]);
		} else if (i == 74) {
			username = lines[i];
		}
	}
	// while(getline(fin, line)){
	//     if(line.substr(0, 7) == "@slot " + to_string(slot)){
	//         cnt = -2;
	//     }
	//     if(cnt >= 0 && cnt < 20) parameters[cnt] = stod(line);
	//     if(line.substr(0, 11) == "@username") username = line;
	//     cnt++;
	// }
	s.save_character.set(parameters);
	// std::cerr << parameters[1] << " " << parameters[2] << std::endl;
	// getchar();
	s.maze = maze;
	s.username = username;
	fin.close();
	// std::cerr << "OK2\n";
	return;
}

int rename_slot() {
	int slot;
	string new_name;
	bool valid = false;

	while (!valid) {
		cout << "Enter the number of the slot you want to rename: ";
		cin >> slot;
		if (slot == 1 || slot == 2 || slot == 3) {
			valid = true;
		} else {
			cout << "Invalid slot number.\n";
		}
	}

	cout << "Enter a new name for the slot: ";
	cin.ignore();
	getline(cin, new_name);

	ifstream file_in("data/scripts/ascii_images/save.txt");
	vector<string> lines;
	string line;
	while (getline(file_in, line)) {
		lines.push_back(line);
	}
	file_in.close();
	lines[2 * slot - 1] = lines[2 * slot - 1].substr(0, 11) + new_name;

	ofstream file_out("data/scripts/ascii_images/save.txt");
	if (file_out.fail()) {
		cout << "error: file not found" << endl;
	}
	for (const string &line : lines) {
		file_out << line << "\n";
	}
	file_out.close();

	return slot;
}

//
void save(save_file &s, int slot) {
	// save_file save_files[3];
	// int slot;
	// char command;
	// init save_files
	// parse_file("data/savings/sav.txt", save_files[0], 1);
	// parse_file("data/savings/sav.txt", save_files[1], 2);
	// parse_file("data/savings/sav.txt", save_files[2], 3);
	// waiting for user input
	// print_file("data/scripts/ascii_images/save.txt", 0, true);
	// cin.ignore();
	// cout << "Enter [S] to save your game, [D] to erase existing "
	// 		"slot: ";
	// cin >> command;
	// if (command == 's') {
	// 	slot = rename_slot();

	// save_files[slot - 1] = s;

	// } else if (command == 'd') {
	// 	slot = delete_slot(-1); // TODO a modification here
	// }

	// double *save_parameters;
	// vector<string> savemap;
	// string username;
	auto save_parameters = s.save_character.save();
	// auto &savemap = s.maze;
	// slot = slot;
	// auto &username = s.username;
	// std::cerr << s.username << "\n";

	// input save file
	ifstream fin;
	fin.open("data/savings/sav.txt");
	if (fin.fail()) {
		cout << "error: file not found" << endl;
		exit(1);
	}

	vector<string> lines;
	string line;
	while (getline(fin, line)) {
		lines.push_back(line);
	}
	fin.close();

	// calculate the part that needs to change
	int init_pos, end_pos;
	if (slot == 1) {
		init_pos = 0;
		end_pos = 74;
	} else if (slot == 2) {
		init_pos = 75;
		end_pos = 149;
	} else if (slot == 3) {
		init_pos = 150;
		end_pos = 224;
	}
	// cerr << lines.size() << endl;
	// change content of the save file
	//      delete
	// if (command == 'd') {
	// 	for (int i = init_pos; i <= end_pos; i++) {
	// 		if (lines[i].substr(0, 1) != "@") {
	// 			lines[i] = "";
	// 		}
	// 	}

	// 	// rewrite save file
	// 	ofstream fout("data/savings/sav.txt");
	// 	if (fout.fail()) {
	// 		cout << "error: file not found" << endl;
	// 	}
	// 	for (int i = 0; i < lines.size(); i++) {
	// 		if (i == lines.size() - 1) {
	// 			fout << lines[i];
	// 			break;
	// 		}
	// 		fout << lines[i] << "\n";
	// 	}
	// 	fout.close();

	// 	return;
	// }
	//      save
	// for (int i = init_pos + 2; i <= end_pos; i++) {
	// 	if (i > init_pos + 1 && i < init_pos + 22) {
	// 		auto t = to_string(save_parameters[i - init_pos - 2]);
	// 		lines[i].swap(t);
	// 	} else if (i >= init_pos + 23 && i <= init_pos + 72) {
	// 		auto t = s.maze[i - init_pos - 23];
	// 		lines[i].swap(t);
	// 	} else if (i == init_pos + 74) {
	// 		// lines[i] = username;
	// 		auto t = s.username;
	// 		lines[i].swap(t);
	// 	}
	// }

	// rewrite save file
	ofstream fout("data/savings/sav.txt");
	if (fout.fail()) {
		cout << "error: file not found" << endl;
		exit(1);
	}
	for (int i = 0; i < lines.size(); i++) {
		if (i < init_pos || i > end_pos) {
			fout << lines[i] << "\n";
		} else if (i == init_pos)
			fout << "@slot " << slot << "\n";
		else if (i == init_pos + 1)
			fout << "@character\n";
		else if (i == init_pos + 22)
			fout << "@maze\n";
		else if (i == init_pos + 73)
			fout << "@username\n";
		else if (i > init_pos + 1 && i < init_pos + 22) {
			fout << to_string(save_parameters[i - init_pos - 2]) << "\n";
		} else if (i >= init_pos + 23 && i <= init_pos + 72) {
			fout << s.maze[i - init_pos - 23] << "\n";
		} else if (i == init_pos + 74) {
			fout << s.username << "\n";
		}
	}
	// for (int i = 0; i < lines.size(); i++) {
	// 	if (i == lines.size() - 1) {
	// 		fout << lines[i];
	// 		break;
	// 	}
	// 	fout << lines[i] << "\n";
	// }
	fout.close();
	delete[] save_parameters;

	return;
}

// Exit Game.
void end() {
	bool quit = true;
	cout << "       Are you sure ?  Enter 1 (Yes) / 0 (No):    " << endl;
	quit = readKeyboard() - '0';
	if (!quit) return;
	// Print ending animation.
	print_file("data/scripts/ascii_images/end.txt", 3, true);
	exit(1);
}

// Prints the start page and returns verdict of operation.
int print_start_page_helper() {
	// Show formatted options;
	vector<string> options = {"New Game", "Continue", "Exit"};
	int verdict = -1;
	int cursor = 0; // Which entry is the cursor pointing.

	while (verdict == -1) {
		clear_screen();
		cout << "\n\n"; // Upper padding

		// Print Logo.
		int padding =
			0.05 * print_file("data/scripts/ascii_images/start1.txt", 0, true);

		// Show cursor movement help tips.
		printPadded("Press [W] to move up, [S] to move down, [C] to confirm",
					padding);

		// Print Formatted Options
		cout << "\n";
		for (int i = 0; i < options.size(); i++) {
			printPadded("+---+", padding); // Upper border of selector
			string tmp = "";
			if (i == cursor) {
				tmp += "| > |";
			} else {
				tmp += "|   |";
			}
			printPadded(tmp + "   " + options[i], padding);
			printPadded("+---+", padding); // Lower border of selector
		}

		// Move cursor.
		int key = readKeyboard();
		if (key == 'W' || key == 'w') {
			cursor = (cursor - 1 + options.size()) % options.size();
		} else if (key == 'S' || key == 's') {
			cursor = (cursor + 1) % options.size();
		} else if (key == 'C' || key == 'c') {
			verdict = cursor;
			break;
		}
	}
	return verdict;
}

// Includes: New Game, Continue Game, Save, Start Tutorial, Exit.
int start_page(save_file &ret) {
	int tmp_verdict = -1;
	while (tmp_verdict != 2) {
		tmp_verdict = print_start_page_helper();
		// std::cerr << tmp_verdict << "\n";
		if (tmp_verdict == 0) {
			ret.username = new_game();
			return 1;
		} else if (tmp_verdict == 1) {
			// std::cerr << "OK5\n";
			// save_file ret;
			auto tmp = continue_or_modify_saving(ret);
			// successfully read settings.
			if (tmp == 1) {
				// return ret;
				return 2;
			}
			// break;
		} else if (tmp_verdict == 2) {
			end();
			break;
		}
	}
	// return {};
}

// Load stored settings to the game.
bool main_game(save_file s, Maze &mz, main_character &mc, vector<Monster> &ms) {
	// mz.addMainCharacter(mc);
	// mz.addMonsters(ms);
	// mz.loadMaze(s.maze);
	return true; // successfully load settings
}

// void save(){
//     return;
// }
// void tutorial(){
//     return;
// }
// void main_game(int choice)
// int main() { // for test
// 	start_page();
// 	return 0;
// }