#include "../character/character.h"
#include "../utils/utils.hpp"
#include "start_endpage.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
using namespace std;

void clear_screen() {
#ifdef _WIN32
	system("CLS"); // 奇形怪状的bug
#elif __unix__
	system("clear"); // 正常
#endif
}

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
	print_file("../../data/scripts/ascii_images/sith_code.txt", 8, true);
	print_file("../../data/scripts/ascii_images/script1.txt", 10, true);

	string name;
	bool valid = false;
	do {
		// Starting page
		print_file("../../data/scripts/ascii_images/computer.txt", 0, true);
		cin.ignore();
		cout << "Enter your name (no more than 10 chars): ";
		getline(cin, name);

		if (name.size() < 11) {
			valid = true;

			// Story Introduction
			ifstream file_in("../../data/scripts/ascii_images/script3.txt");
			vector<string> lines;
			string line;
			while (getline(file_in, line)) {
				lines.push_back(line);
			}
			file_in.close();
			lines[25] = "  \"" + name + ", my most unlikely servant. Your ";

			// Store user name to file
			ofstream file_out("../../data/scripts/ascii_images/script3.txt");
			if (file_out.fail()) {
				cout << "error: file not found" << endl;
				exit(1);
			}
			for (const string &line : lines) {
				file_out << line << "\n";
			}
			file_out.close();

			ifstream fin("../../data/scripts/ascii_images/luke_skywalker.txt");
			vector<string> sec_lines;
			string sec_line;
			while (getline(fin, sec_line)) {
				sec_lines.push_back(sec_line);
			}
			fin.close();

			// REVIEW - [17]: out of index error?
			sec_lines[17] = "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⣿⣿⡿⣿⣿⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
							"⠀         ****  " +
							name + "  ****";

			ofstream fout("../../data/scripts/ascii_images/luke_skywalker.txt");
			if (fout.fail()) {
				cout << "error: file not found" << endl;
			}
			for (const string &sec_line : sec_lines) {
				fout << sec_line << "\n";
			}
			fout.close();
		}
	} while (!valid);
	print_file("../../data/scripts/ascii_images/luke_skywalker.txt", 4, true);
	print_file("../../data/scripts/ascii_images/script3.txt", 6, true);
	// main_game(choice);
	return name;
}

void continue_game() {
	print_file("../../data/scripts/ascii_images/save.txt", 0, true);

	int slot;
	cin.ignore();
	cout << "Choose your game to continue: ";
	cin >> slot;

	save_file s;
	parse_file("../../data/savings/sav.txt", s, slot);
	main_game(s);
	return;
}

/// Read information from files.
void parse_file(const string filename, save_file &s, int slot) {
	ifstream fin;
	fin.open(filename.c_str());

	// Check if saving file is opened succussfully
	if (fin.fail()) {
		cout << "error: file not found" << endl;
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
		} else if (line.substr(0, 7) == "@slot" + to_string(slot + 1)) {
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
		} else if (lines[i].substr(0, 5) == "@maze") {
			temp_m = i;
		} else if (i > temp_m && lines[i].substr(0, 9) != "@username" &&
				   lines[i] != "") {
			maze.push_back(lines[i]);
		} else if (lines[i].substr(0, 11) == "@username") {
			username = lines[i + 1];
			break;
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
	s.maze.loadMaze(maze);
	s.username = username;
	fin.close();
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

	ifstream file_in("../../data/scripts/ascii_images/save.txt");
	vector<string> lines;
	string line;
	while (getline(file_in, line)) {
		lines.push_back(line);
	}
	file_in.close();
	lines[2 * slot - 1] = lines[2 * slot - 1].substr(0, 11) + new_name;

	ofstream file_out("../../data/scripts/ascii_images/save.txt");
	if (file_out.fail()) {
		cout << "error: file not found" << endl;
	}
	for (const string &line : lines) {
		file_out << line << "\n";
	}
	file_out.close();

	return slot;
}

int delete_slot() {
	int slot;
	bool valid = false;

	while (!valid) {
		cout << "Enter the number of the slot you want to delete: ";
		cin >> slot;
		if (slot == 1 || slot == 2 || slot == 3) {
			valid = true;
		} else {
			cout << "Invalid slot number.\n";
		}
	}

	ifstream file_in("../../data/scripts/ascii_images/save.txt");
	vector<string> lines;
	string line;
	while (getline(file_in, line)) {
		lines.push_back(line);
	}
	file_in.close();
	lines[2 * slot - 1] =
		lines[2 * slot - 1].substr(0, 11) + "Slot " + to_string(slot);

	ofstream file_out("../../data/scripts/ascii_images/save.txt");
	if (file_out.fail()) {
		cout << "error: file not found" << endl;
	}
	for (const string &line : lines) {
		file_out << line << "\n";
	}
	file_out.close();

	return slot;
}

void save(save_file s) {
	save_file save_files[3];
	int slot;
	char command;
	// init save_files
	parse_file("../../data/savings/sav.txt", save_files[0], 1);
	parse_file("../../data/savings/sav.txt", save_files[1], 2);
	parse_file("../../data/savings/sav.txt", save_files[2], 3);
	// waiting for user input
	print_file("../../data/scripts/ascii_images/save.txt", 0, true);
	cin.ignore();
	cout << "Enter \"s\" to save your game; enter \"d\" to erase existing "
			"slot: ";
	cin >> command;
	if (command == 's') {
		slot = rename_slot();
		save_files[slot - 1] = s;
	} else if (command == 'd') {
		slot = delete_slot();
	}

	double *save_parameters;
	vector<string> savemap;
	string username;
	save_parameters = s.save_character.save();
	// savemap =
	slot = slot;
	username = s.username;

	// input save file
	ifstream fin;
	fin.open("../../data/savings/sav.txt");
	if (fin.fail()) {
		cout << "error: file not found" << endl;
	}
	vector<string> lines;
	string line;
	while (getline(fin, line)) {
		lines.push_back(line);
	}
	fin.close();

	int init_pos, end_pos;
	if (slot == 1) {
		for (int i = 25; i < lines.size(); i++) {
			if (lines[i].substr(0, 7) == "@slot" + to_string(slot)) {
				init_pos = i;
			}
			if (lines[i].substr(0, 7) == "@slot" + to_string(slot + 1)) {
				end_pos = i;
				break;
			}
		}
	} else if (slot == 2) {
		for (int i = 25; i < lines.size(); i++) {
			if (lines[i].substr(0, 7) == "@slot" + to_string(slot)) {
				init_pos = i;
			}
			if (lines[i].substr(0, 7) == "@slot" + to_string(slot + 1)) {
				end_pos = i;
				break;
			}
		}
	} else if (slot == 3) {
		for (int i = 50; i < lines.size(); i++) {
			if (lines[i].substr(0, 7) == "@slot" + to_string(slot)) {
				init_pos = i;
				end_pos = lines.size();
				break;
			}
		}
	}
	// change content of the save file
	//      delete
	if (command == 'd') {
		for (int i = init_pos; i < end_pos; i++) {
			if (lines[i].substr(0, 1) != "@") {
				lines[i] = "";
			}
		}

		// rewrite save file
		ofstream fout("../../data/savings/sav.txt");
		if (fout.fail()) {
			cout << "error: file not found" << endl;
		}
		for (int i = 0; i < lines.size(); i++) {
			if (i == lines.size() - 1) {
				fout << lines[i];
				break;
			}
			fout << lines[i] << "\n";
		}
		fout.close();

		return;
	}
	//      save
	for (int i = init_pos + 2; i < end_pos; i++) {
		if (i > init_pos + 1 && i < init_pos + 22) {
			lines[i] = to_string(save_parameters[i - init_pos - 2]);
		} else if (lines[i].substr(0, 5) == "@maze") {
			for (int j = 0; j < savemap.size(); j++) {
				if (lines[i + 1 + j].substr(0, 9) != "@username") {
					lines[i + 1 + j] = savemap[j];
				} else {
					lines.insert(lines.begin() + i + 1 + j, savemap[j]);
					end_pos++;
				}
			}
			i += savemap.size();
		} else if (lines[i].substr(0, 9) == "@username") {
			lines[i + 1] = username;
			i++;
		}
	}

	// rewrite save file
	ofstream fout("../../data/savings/sav.txt");
	if (fout.fail()) {
		cout << "error: file not found" << endl;
	}
	for (int i = 0; i < lines.size(); i++) {
		if (i == lines.size() - 1) {
			fout << lines[i];
			break;
		}
		fout << lines[i] << "\n";
	}
	fout.close();

	return;
}

void end() {
	bool quit = true;
	cout << "       Are you sure ?  Enter 1 (Yes) / 0 (No):    " << endl;
	cin >> quit;
	if (!quit) return;
	print_file("../../data/scripts/ascii_images/end.txt", 3, true);
	exit(1);
}

// Prints the start page and returns verdict of operation.
int print_start_page_helper() {
	// Show formatted options;
	vector<string> options = {"New Game", "Continue", "Edit Saves", "Tutorial",
							  "Exit"};
	int verdict = -1;
	int cursor = 0; // Which entry is the cursor pointing.

	auto printPadded = [](const string &s, int padding) {
		cout << string(padding, ' ') << s << endl;
	};

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
		}
	}

	return verdict;
}

void start_page() {
	int tmp_verdict = -1;
	while (tmp_verdict != 4) {
		tmp_verdict = print_start_page_helper();
		switch (tmp_verdict) {
		case 0:
			new_game();
			break;
		case 1:
			continue_game();
			break;
		case 2:
			save(save_file());
			break;
		case 3:
			// tutorial();
			break;
		case 4:
			end();
			break;
		default:
			// Never reach here. LOL
			cout << "invalid choice, please try again" << endl;
			break;
		}
	}
}

void main_game(save_file s) {
	//
	return;
}

// void save(){
//     return;
// }
// void tutorial(){
//     return;
// }
// void main_game(int choice)
int main() { // for test
	print_start_page_helper();
	return 0;
}