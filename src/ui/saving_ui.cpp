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
	while (fin >> tmp_id >> tmp_info) {
		this->addEntry(tmp_id, tmp_info);
	}
}

// Add a new saving entry.
void SavingsUI::addEntry(int id, std::string info) {
	// Add a new saving entry.
	if (entries.size() >= kMaxSavings) {
		std::cerr << "Error: Exceeding maximum number of savings." << std::endl;
		return;
	}
	entries.emplace_back(id, info);
}

// TODO A better/centered UI.
void SavingsUI::display() {
#ifdef __unix__
	system("clear");
#endif

	// Display the UI.
	bool confirmed = false;
	int cursorAt = 0; // Cursor at the first entry by default.
	while (!confirmed) {
		std::cout << std::setw(14) << std::right << "Savings" << std::endl;
		std::cout << "     ID | Brief Info" << std::endl;
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
		}
		// Clear to output updated cursor.
		system("clear");
	}
}

// TESTING
int main() {
	SavingsUI ui;
	ui.loadEntries();
	ui.display();
}