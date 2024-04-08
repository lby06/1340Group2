FLAG=-pedantic-errors -std=c++11

SRC=./src
CHARAC_DIR=$(SRC)/character

UTILS=$(SRC)/utils/utils.cpp
MAZE=$(SRC)/maze/maze.cpp
MAIN=$(SRC)/main/main.cpp
BATTLE=$(SRC)/battle/battle.cpp
MONSTER=$(CHARAC_DIR)/monster.cpp
BOSS=$(CHARAC_DIR)/boss.cpp
CHARACTER=$(CHARAC_DIR)/character.cpp


utils.o: $(UTILS)
	g++ $(FLAG) -c $(UTILS) -o utils.o

# Seperate Testing (utils)
utils: utils.o
	g++ $(FLAG) utils.o -o utils.out

maze.o: $(MAZE)
	g++ $(FLAG) -c $(MAZE) -o maze.o

# Seperate Testing (maze)
maze: maze.o
	g++ $(FLAG) maze.o -o maze.out

main.o: $(MAIN)
	g++ $(FLAG) -c $(MAIN) -o main.o

.PHONY: clean

clean:
	rm -f *.o *.out
	rm -f game