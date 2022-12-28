/*
    Part of the C++ Sudoku Solver codebase
    https://github.com/mohaps/Sudoku
    License: Apache 2.0

    Author: Saurav Mohapatra (mohaps@gmail.com)
 */
#include "sudoku/Board.h"
#include <cstring>

namespace sudoku {

Board::Board() {
  clear();
}

Board::Board(const Board& other) {
  *this = other;
}

const Board& Board::operator = (const Board& other) {
  memcpy(numbers_, other.numbers_, 81 * sizeof(bool));
  return *this;
}
bool Board::canSet(int x, int y, int val) const {
  if (!validCoord(x, y)) {
    std::cerr << "("<<x<<","<<y<<") is invalid!" << std::endl;
  }
  int idx = xy2Index(x, y);
  int block = xy2BlockIndex(x, y);
  if (numbers_[idx] != 0) { return false; }
  if (numbers_[idx] == val) { return true; }
  if (blockChecks_[block].check(val)) { return false; }
  if (rowChecks_[y].check(val)) { return false; }
  if (colChecks_[x].check(val)) { return false; }
  return true;
}

bool Board::set(int x, int y, int val) {
  if (!canSet(x, y, val)) {
    return false;
  }
  int idx = xy2Index(x, y);
  int block = xy2BlockIndex(x, y);
  numbers_[idx] = val;
  rowChecks_[y].set(val);
  colChecks_[x].set(val);
  blockChecks_[block].set(val);
  return true;
}
bool Board::unset(int x, int y) {
  if (!validCoord(x, y)) {
    return false;
  }
  int idx = xy2Index(x, y);
  int val = numbers_[idx];
  numbers_[idx] = 0;
  // update set/counts in checks
  if (val >= 1 && val <= 9) {
    rowChecks_[y].unset(val);
    colChecks_[x].unset(val);
    int block = xy2BlockIndex(x, y);
    blockChecks_[block].unset(val);
  }
  return true;
}

int Board::get(int x, int y) const {
  if (!validCoord(x, y)) {
    std::cerr << "("<<x<<","<<y<<") is invalid!" << std::endl;
  }
  return numbers_[xy2Index(x, y)];
}

Board& Board::clear() {
  memset(numbers_, 0, 81);
  for (auto& c : rowChecks_) { c.clear(); }
  for (auto& c : colChecks_) { c.clear(); }
  for (auto& c : blockChecks_) { c.clear(); }
  return *this;
}

bool Board::solved() const {
  for (auto& c : blockChecks_) { if (!c.allSet()) { return false; } }
  for (auto& c : rowChecks_) { if (!c.allSet()) { return false; } }
  for (auto& c : colChecks_) { if (!c.allSet()) { return false; } }
  return true;
}

char Board::numberToChar(uint8_t num) {
  if (num >= 1 && num <= 9) {
    return '0'+num;
  } else {
    return '.';
  }
}

int Board::xy2Index(int x, int y)  {
  return y * 9 + x;
}

int Board::xy2BlockIndex(int x, int y)  {
  int bX = x / 3;
  int bY = y / 3;
  return 3 * bY + bX;
}

std::ostream& Board::print(std::ostream& os)  const {
  os <<"    => ";
  for (int x = 0; x < 9; x++) {
    os <<"("<<x<<")";
    if (x % 3 == 2) { os << " "; }
  }
  os << std::endl;

  for (int y = 0; y < 9; y++) {
    os << "("<<y<<") => ";
    for (int x = 0; x < 9; x++) {
      os << "["<<numberToChar(numbers_[xy2Index(x,y)])<<"]";
      if (x % 3 == 2) { os << " "; }
    }
    if (y % 3 == 2) {
      os << std::endl;
    }
    os << std::endl;
  }
  return os << std::endl;
}
}