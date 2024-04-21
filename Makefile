FLAG=-std=c++11

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

BATTLE_MAIN=$(SRC)/battle/battle.cpp
BATTLE_MAIN_HEADER=$(SRC)/battle/battle.h

PRINT_FEATURES=$(SRC)/battle/printFeatures.cpp

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
	g++ $(FLAG) -c $<

maze: maze.o character.o monster.o utils.o
	g++ $(FLAG) $^ -o maze.out

# MONSTER
monster.o: $(MONSTER) $(MONSTER_HEADRER)
	g++ $(FLAG) -c $<
monster: monster.o
	g++ $(FLAG) $^ -o monster.out

# CHARACTER
character.o: $(CHARACTER) $(CHARACTER_HEADER)
	g++ $(FLAG) -c $<
character: character.o
	g++ $(FLAG) $^ -o character.out

# UTILS
utils.o: $(UTILS) ${UTILS_HEADER} $(MAZE)
	g++ $(FLAG) -c $<

utils: utils.o maze.o
	g++ $(FLAG) utils.o maze.o -o utils.out

# START
start.o: $(START) $(START_HEADER)
	g++ $(FLAG) -c $< -o start.o
start: start.o utils.o maze.o character.o
	g++ $(FLAG) $^ -o start.out


# SAVING_UI
saving_ui.o: $(SAVING_UI)
	g++ $(FLAG) -c $^ -o saving_ui.o

saving_ui: saving_ui.o utils.o maze.o
	g++ $(FLAG) $^ -o saving_ui.out

# BATTLE
battle.o: $(BATTLE_MAIN) $(BATTLE_MAIN_HEADER)
	g++ $(FLAG) -c $< -o battle.o
battle: battle.o character.o monster.o utils.o
	g++ $(FLAG) $^ -o battle.out

# GAME (Main entrance)
game: game.cpp start.o utils.o maze.o character.o monster.o battle.o
	g++ $(FLAG) $^ -o game

# MISC
.PHONY: clean

clean:
	rm -f *.o *.out
	rm -f game