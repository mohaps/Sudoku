/*
    Part of the C++ Sudoku Solver codebase
    https://github.com/mohaps/Sudoku
    License: Apache 2.0

    Author: Saurav Mohapatra (mohaps@gmail.com)
 */
#pragma once
#include <vector>
#include <string>
#include "sudoku/Board.h"
namespace sudoku {
class Board;
class StopWatch {
public:
  StopWatch() { reset(); }
  virtual ~StopWatch() = default;
  uint64_t elapsedMicros() const;
  uint64_t lapMicros() const;
  uint64_t resetLap();
  StopWatch& reset();
private:
  uint64_t startMicros_;
  uint64_t lapStartMicros_;
};
class Helper {
public:
  static std::vector<std::string> save(const Board& b);
  static Board& load(Board& b, const std::vector<std::string>& rows);
  static void saveToFile(const Board& b, const std::string& fileName);
  static void loadFromFile(Board& b, const std::string& fileName);
private:
  Helper() = delete;
  ~Helper() = delete;
};
}