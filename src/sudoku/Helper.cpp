/*
    Part of the C++ Sudoku Solver codebase
    https://github.com/mohaps/Sudoku
    License: Apache 2.0

    Author: Saurav Mohapatra (mohaps@gmail.com)
 */
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>

#include "sudoku/Helper.h"
#include "sudoku/Board.h"
namespace sudoku {
Board& Helper::load(Board& b, const std::vector<std::string>& rows) {
  b.clear();
  if (rows.size() != 9) {
    throw std::invalid_argument("need 9 rows");
  }
  int y = 0;
  for (const auto& row : rows) {
    if (y >= 9) { break; }
    if (row.size() != 9) {
      std::cerr << "Invalid Row Size (row="<<y<<") => "<< row.size() << std::endl;
      throw std::invalid_argument("need 9 columns");
    }
    int x = 0;
    for (auto c : row) {
      if (c == '.') {
        b.unset(x, y);
      } else if (c >= '1' || c <= '9') {
        if (b.canSet(x, y, c - '0')) {
          b.set(x, y, c - '0');
        } else {
          std::invalid_argument("not a valid partial or full sudoku board");
        }
      } else {
        throw std::invalid_argument("invalid character. only [1-9] or . allowed");
      }
      x++;
    }
    y++;
  }
  return b;
}
std::vector<std::string> Helper::save(const Board& b) {
  std::vector<std::string> results;
  for (int y = 0; y < 9; y++) {
    std::ostringstream os;
    for (int x = 0; x < 9; x++) {
      int val = b.get(x, y);
      if (val == 0) {
        os << '.';
      } else {
        os << (char)(val + '0'); 
      }
    }
    results.push_back(os.str());
  }
  return results;
}


void Helper::saveToFile(const Board& b, const std::string& fileName) {
  std::ofstream out(fileName);
  auto results = Helper::save(b);
  out << "#$$sudoku-file$$" << std::endl;
  for (auto r : results) {
    out << r << std::endl;
  }
  out.close();
}

void Helper::loadFromFile(Board& b, const std::string& fileName) {
  std::ifstream in(fileName);
  b.clear();
  std::string line;
  std::getline(in, line);
  if (line != "#$$sudoku-file$$") { throw std::invalid_argument("not a valid sudoku board file"); }
  std::vector<std::string> rows(9);
  for (auto& r : rows) {
    std::getline(in, r);
  }
  load(b, rows);
}
inline uint64_t microsSinceEpoch() {
  return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
uint64_t StopWatch::elapsedMicros() const {
  uint64_t cur = microsSinceEpoch();
  return cur - startMicros_;

}
uint64_t StopWatch::lapMicros() const {
  uint64_t cur = microsSinceEpoch();
  return cur - lapStartMicros_;
}

uint64_t StopWatch::resetLap()  {
  uint64_t cur = microsSinceEpoch();
  uint64_t delta = cur - lapStartMicros_;
  lapStartMicros_ = cur;
  return delta;
}
StopWatch& StopWatch::reset() {
  startMicros_ = microsSinceEpoch();
  lapStartMicros_ = startMicros_;
  return *this;
}

}