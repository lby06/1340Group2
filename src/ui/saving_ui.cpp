#include "saving_ui.hpp"
#include "../utils/utils.hpp"

#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>

static constexpr int kMaxSavings = 3;

static const std::string sav_info_path = "./data/savings/sav.dat";

void SavingsUI::loadEntries() {
	// Load all existing savings from file.
	std::ifstream fin(sav_info_path);

	if (!fin.is_open()) {
		std::cerr << "Error: Failed to open file." << std::endl;
		return;
	}

	// Read entries from file.
	int tmp_id;
	std::string tmp_info;
	int tmp_lv;
	while (fin >> tmp_id >> tmp_info >> tmp_lv) {
		// std::cin.ignore();
		// std::getline(std::cin, tmp_info);
		this->addEntry(tmp_id, tmp_info, tmp_lv);
	}

	fin.close();
}

// Add a new saving entry.
void SavingsUI::addEntry(int id, std::string info, int lv) {
	// Add a new saving entry.
	if (entries.size() >= kMaxSavings) {
		std::cerr << "Error: Exceeding maximum number of savings." << std::endl;
		return;
	}
	entries.emplace_back(id, info, lv);
}

void SavingsUI::loadSavingfile(save_file &sf) {
	// Load saving file.
	this->sf = &sf;
}

// TODO A better/centered UI.
void SavingsUI::display() {
	system("clear");
	// Display the UI.
	bool confirmed = false;
	int cursorAt = 0; // Cursor at the first entry by default.
	while (!confirmed) {
		// upper padding
		for (int i = 0; i <= 15; i++) std::cout << std::endl;
		std::cout << "Press [s] to move down, [w] to move up, [c] to confirm, "
					 "[q] to go back, [r] to rename."
				  << std::endl;
		std::cout << std::setw(14) << std::right << "Savings" << std::endl;
		std::cout << "   ID   | Brief Info" << std::endl;
		std::cout << "--------------------" << std::endl;
		for (const auto &entry : entries) {
			if (cursorAt + 1 == entry.getId())
				std::cout << std::setw(5) << std::right << ">>>";
			else
				std::cout << std::setw(5) << std::right << "   ";
			std::cout << std::setw(2) << entry.getId() << " | "
					  << entry.getBriefInfo() << std::endl;
		}

		int key = readKeyboard();
		// respond to key.
		if (key == 's' || key == 'S') { // Move cursor down.
			cursorAt = (cursorAt + 1) % (kMaxSavings);
		} else if (key == 'w' || key == 'W') { // Move cursor up.
			cursorAt = (cursorAt - 1 + kMaxSavings) % (kMaxSavings);
		} else if (key == 'c' || key == 'C') { // Confirm.
			confirmed = true;
			entries[cursorAt].brief_info_ = sf->username;
			save(*sf, cursorAt + 1);
		} else if (key == 'q' || key == 'Q') { // Quit saving mode.
			// exit(0);
			return;
		} else if (key == 'd' || key == 'D') { // Delete.
			// entries.erase(entries.begin() + cursorAt);
		} else if (key == 'r' || key == 'R') {
			renameSlot(cursorAt);
		}
		// Clear to output updated cursor.
		system("clear");
	}
}

void SavingsUI::renameSlot(int slot) {
	// Rename the slot.
	std::string new_name;
	std::cout << "Enter new name (There should be no [space]): ";
	std::cin >> new_name;

	sf->username = entries[slot].brief_info_ = new_name;
}

void SavingsUI::saveEntries() {
	// Save all entries to file.
	std::ofstream fout(sav_info_path);
	for (auto &entry : entries) {
		fout << entry.getId() << std::endl
			 << entry.brief_info_ << std::endl
			 << sf->level << std::endl;
	}
	fout.close();
}

// TESTING
// int main() {
// 	SavingsUI ui;
// 	ui.loadEntries();
// 	ui.display();
// }