CC=g++
EXE=bin/sudoko_solver
SRC=src/sudoku/*.cpp src/Main.cpp

all: build

build:
	$(CC) -o $(EXE) -O2 -std=c++1z -Iinclude -Wall $(SRC)
clean:
	rm -rf $(EXE)
run: build
	$(EXE) $(BOARD_FILE)
rebuild: clean build
