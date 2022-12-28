/*
    Part of the C++ Sudoku Solver codebase
    https://github.com/mohaps/Sudoku
    License: Apache 2.0

    Author: Saurav Mohapatra (mohaps@gmail.com)
 */
#pragma once
#include "sudoku/Board.h"
#include <queue>
namespace sudoku {
class Board;
class Solver {
public:
  using Coord = std::pair<int, int>;
  Solver() = default;
  virtual ~Solver() = default;
  bool solve(Board& b);
protected:
  bool solveWithCandidates(Board& b, std::vector<Coord>& candidates, size_t offset);
};
}