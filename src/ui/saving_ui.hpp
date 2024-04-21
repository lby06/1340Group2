#pragma once

#include "start_endpage.h"
#include <string>
#include <vector>

class Savingentry {
  private:
	int id_;

  public:
	std::string brief_info_;
	Savingentry(int id, std::string briefInfo)
		: id_(id), brief_info_(briefInfo) {}
	int getId() const { return id_; }
	std::string getBriefInfo() const { return brief_info_; }
};

class SavingsUI {
  private:
	std::vector<Savingentry> entries;
	std::vector<std::string> ui_grid_;
	save_file *sf;

  public:
	// Show all existing savings within TUI
	void showAllEntries();
	// Confirmation before deleting a saving.
	void confirmBeforeDeleting();
	void renameSlot(int);
	void loadEntries();
	void loadSavingfile(save_file &);
	void saveEntries();
	void addEntry(int, std::string);

	// Display UI.
	void display();
};
