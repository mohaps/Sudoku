/*
    Part of the C++ Sudoku Solver codebase
    https://github.com/mohaps/Sudoku
    License: Apache 2.0

    Author: Saurav Mohapatra (mohaps@gmail.com)
 */
#include "sudoku/Solver.h"

namespace sudoku {
bool Solver::solve(Board& b) {
  if (b.solved()) { return true; }
  std::vector<Coord> candidates;
  for (int y = 0; y < 9; y++) {
    for (int x = 0; x < 9; x++) {
      if (b.get(x, y) == 0) {
        candidates.push_back({x, y});
      }
    }
  }
  return solveWithCandidates(b, candidates, 0);
}
bool Solver::solveWithCandidates(Board& b, std::vector<Coord>& candidates, size_t offset) {
  if (offset >= candidates.size()) { return b.solved(); }
  if (b.solved()) { return true; }
  auto p = candidates[offset]; int x = p.first; int y = p.second;
  for (int i = 1; i <= 9; i++) {
    if (b.set(x, y, i)) {
      if (solveWithCandidates(b, candidates, offset + 1)) { return true; }
      b.unset(x, y);
    }
  }
  return false;
}
}