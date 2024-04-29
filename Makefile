FLAG=-std=c++11 -g -fsanitize=address -fsanitize=undefined -fsanitize=leak 
compiler=g++

SRC=./src
CHARAC_DIR=$(SRC)/character

UTILS_HEADER=$(SRC)/utils/utils.hpp
UTILS=$(SRC)/utils/utils.cpp

MAZE_HEADER=$(SRC)/maze/maze.hpp
MAZE=$(SRC)/maze/maze.cpp

START_HEADER=$(SRC)/ui/start_endpage.h
START=$(SRC)/ui/start.cpp

MAIN=$(SRC)/main/main.cpp

BATTLE_HEADER=$(SRC)/battle/battle_upgrade.h
BATTLE=$(SRC)/battle/battle_upgrade.cpp
UPGRADE=$(SRC)/battle/upgrade.cpp
WIN=$(SRC)/battle/win.cpp

BATTLE_MAIN=$(SRC)/battle/battle.cpp
BATTLE_MAIN_HEADER=$(SRC)/battle/battle.h

PRINT_FEATURES=$(SRC)/battle/print_features.cpp

MONSTER_HEADRER=$(CHARAC_DIR)/monster.h
MONSTER=$(CHARAC_DIR)/monster.cpp

BOSS_HEADER=$(CHARAC_DIR)/boss.h
BOSS=$(CHARAC_DIR)/boss.cpp

CHARACTER_HEADER=$(CHARAC_DIR)/character.h
CHARACTER=$(CHARAC_DIR)/character.cpp

SAVING_UI_HEADER=$(SRC)/ui/saving_ui.hpp
SAVING_UI=$(SRC)/ui/saving_ui.cpp

# MAZE
maze.o: $(MAZE) $(MAZE_HEADER) $(CHARACTER) $(MONSTER)
	$(compiler) $(FLAG) -c $<

maze: maze.o character.o monster.o utils.o
	$(compiler) $(FLAG) $^ -o maze.out

# MONSTER
monster.o: $(MONSTER) $(MONSTER_HEADRER)
	$(compiler) $(FLAG) -c $<
monster: monster.o
	$(compiler) $(FLAG) $^ -o monster.out

# CHARACTER
character.o: $(CHARACTER) $(CHARACTER_HEADER)
	$(compiler) $(FLAG) -c $<
character: character.o
	$(compiler) $(FLAG) $^ -o character.out

# UTILS
utils.o: $(UTILS) ${UTILS_HEADER} $(MAZE)
	$(compiler) $(FLAG) -c $<

utils: utils.o maze.o
	$(compiler) $(FLAG) utils.o maze.o -o utils.out

# START
start.o: $(START) $(START_HEADER)
	$(compiler) $(FLAG) -c $< -o start.o
start: start.o utils.o maze.o character.o
	$(compiler) $(FLAG) $^ -o start.out


# SAVING_UI
saving_ui.o: $(SAVING_UI)
	$(compiler) $(FLAG) -c $^ -o saving_ui.o

saving_ui: saving_ui.o utils.o maze.o start.o character.o monster.o
	$(compiler) $(FLAG) $^ -o saving_ui.out


# PRINT_FEATURES
print_features.o: $(PRINT_FEATURES)
	$(compiler) $(FLAG) -c $< -o print_features.o

print_features: print_features.o
	$(compiler) $(FLAG) $^ -o print_features.out

# Battle
battle.o: $(BATTLE_MAIN) $(PRINT_FEATURES) $(CHARACTER) $(MONSTER) $(BATTLE_MAIN_HEADER) $(UTILS)
	$(compiler) $(FLAG) -c $< -o battle.o

battle: battle.o character.o monster.o print_features.o utils.o
	$(compiler) $(FLAG) $^ -o battle.out
# BATTLE_UPGRADE

battle_upgrade.o: $(BATTLE)  $(CHARACTER) $(UTILS)
	$(compiler) $(FLAG) -c $< -o battle_upgrade.o
upgrade.o:  $(UPGRADE)
	$(compiler) $(FLAG) -c $< -o upgrade.o
win.o: $(WIN)
	$(compiler) $(FLAG) -c $< -o win.o
battle_upgrade: battle_upgrade.o character.o upgrade.o
	$(compiler) $(FLAG) $^ -o battle_upgrade.out


# GAME (Main entrance)
game: game.cpp start.o utils.o maze.o character.o monster.o saving_ui.o battle.o print_features.o battle_upgrade.o upgrade.o win.o
	$(compiler) $(FLAG) $^ -o game

# MISC
.PHONY: clean

clean:
	rm -f *.o *.out
	rm -f game
