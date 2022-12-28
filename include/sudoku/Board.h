/*
    Part of the C++ Sudoku Solver codebase
    https://github.com/mohaps/Sudoku
    License: Apache 2.0

    Author: Saurav Mohapatra (mohaps@gmail.com)

 */
#pragma once
#include "sudoku/Check9.h"

namespace sudoku {
class Board {
public:
  Board();
  Board(const Board& other);
  virtual ~Board() = default;

  const Board& operator = (const Board& other);
  bool canSet(int x, int y, int val) const;
  bool set(int x, int y, int val);
  bool unset(int x, int y);
  int get(int x, int y) const;
  Board& clear();
  
  bool solved() const;

  // helper methods
  std::ostream& print(std::ostream& os) const;
  static int xy2Index(int x, int y);
  static int xy2BlockIndex(int x, int y);
  static char numberToChar(uint8_t num);
  static bool validCoord(int x) { return x >= 0 && x < 9; }
  static bool validCoord(int x, int y) { return validCoord(x) && validCoord(y); }
  static bool validValue(int v) { return v >= 1 && v <= 9; }
private:
  uint8_t numbers_[81];
  Check9 rowChecks_[9];
  Check9 colChecks_[9];
  Check9 blockChecks_[9];
};
}