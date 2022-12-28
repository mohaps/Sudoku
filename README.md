# Sudoku Solver (C++)
A C++ Sudoku Solver with no dependencies.
Weekend hack and programming practice. 
Solves the sudoku puzzle via Depth First Search / Backtracking.

## Algorithm
* create a queue of all empty cells in the board as candidates
* initiate offset into the candidates list as 0
* for each permissible value that can be set in the first candidate
   * offset is incremented by 1
   * try each permissible value in next candidate
   * loop till out of candidates or puzzle solved

The implementation is in ```src/sudoku/Solver.cpp``` in the ```solveWithCandidates()``` method

Implemented a ```Check9``` class to check if 1-9 is set in row/column or 3x3 grid

## TODO
* implement board generator
* implement interactive console game

## Build
to compile:
```
make
```
this will provide ```bin/sudoku_solver``` if everything goes well

to compile and run:
```
make run BOARD_FILE=<board-file-name>
```

e.g
```
make run BOARD_FILE=data/expert2.sudoku
```

## Usage
general usage:
```
bin/sudoku_solver <board-file-name>
```
sample board files included in ```data/```
```
data/empty_board.sudoku
data/board1.sudoku
data/expert1.sudoku
data/expert2.sudoku
```

## Board File Format
begins with magic header ```#$$sudoku-file$$#``` as the first line and then 9 lines each with a row of the sudoku board
(digits 1-9 or ```.``` for 0/blank cell)
```
#$$sudoku-file$$
53..7....
6..195...
.98....6.
8...6...3
4..8.3..1
7...2...6
.6....28.
...419..5
....8..79
```

# Credits
Saurav Mohapatra (mohaps@gmail.com)
License: Apache 2.0
