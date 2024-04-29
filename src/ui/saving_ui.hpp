#pragma once

#include "start_endpage.h"
#include <string>
#include <vector>

class Savingentry {
  private:
	int id_;
	int level_;

  public:
	std::string brief_info_;
	Savingentry(int id, std::string briefInfo, int lv)
		: id_(id), brief_info_(briefInfo), level_(lv) {}
	int getId() const { return id_; }
	std::string getBriefInfo() const {
		return brief_info_ + "(level: " + std::to_string(level_) + ")";
	}
	std::string getUsername() const {
		return brief_info_;
	}
	int getLevel() const { return level_; }
};

class SavingsUI {
  private:
	std::vector<std::string> ui_grid_;
	save_file *sf;

  public:
	std::vector<Savingentry> entries;
	// Show all existing savings within TUI
	void showAllEntries();
	// Confirmation before deleting a saving.
	void confirmAndDelete(int);
	void renameSlot(int);
	void loadEntries();
	void loadSavingfile(save_file &);
	void saveEntries();
	void addEntry(int, std::string, int);

	// Display UI.
	void display();
};
