FLAG=-pedantic-errors -std=c++11

SRC=./src
CHARAC_DIR=$(SRC)/character

UTILS_HEADER=$(SRC)/utils/utils.hpp
UTILS=$(SRC)/utils/utils.cpp

MAZE_HEADER=$(SRC)/maze/maze.hpp
MAZE=$(SRC)/maze/maze.cpp

MAIN=$(SRC)/main/main.cpp

BATTLE_HEADER=$(SRC)/battle/battle_upgrade.hpp
BATTLE=$(SRC)/battle/battle_upgrade.cpp

MONSTER_HEADRER=$(CHARAC_DIR)/monster.hpp
MONSTER=$(CHARAC_DIR)/monster.cpp

BOSS_HEADER=$(CHARAC_DIR)/boss.hpp
BOSS=$(CHARAC_DIR)/boss.cpp

CHARACTER_HEADER=$(CHARAC_DIR)/character.hpp
CHARACTER=$(CHARAC_DIR)/character.cpp

SAVING_UI_HEADER=$(SRC)/ui/saving_ui.hpp
SAVING_UI=$(SRC)/ui/saving_ui.cpp

# MAZE
maze.o: $(MAZE) $(MAZE_HEADER) $(CHARACTER) $(MONSTER)
	g++ $(FLAG) -c $< -o maze.o

maze: maze.o
	g++ $(FLAG) $< -o maze.out

# UTILS
utils.o: $(UTILS) ${UTILS_HEADER} $(MAZE)
	g++ $(FLAG) -c $< -o utils.o

utils: utils.o maze.o
	g++ $(FLAG) utils.o maze.o -o utils.out

# SAVING_UI
saving_ui.o: $(SAVING_UI)
	g++ $(FLAG) -c $^ -o saving_ui.o

saving_ui: saving_ui.o utils.o maze.o
	g++ $(FLAG) $^ -o saving_ui.out

# MISC
.PHONY: clean

clean:
	rm -f *.o *.out
	rm -f game