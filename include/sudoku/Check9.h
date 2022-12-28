/*
    Part of the C++ Sudoku Solver codebase
    https://github.com/mohaps/Sudoku
    License: Apache 2.0

    Author: Saurav Mohapatra (mohaps@gmail.com)
 */
#pragma once
#include <array>
#include <iostream>
namespace sudoku {
class Check9 {
public:
  Check9();
  virtual ~Check9() = default;
  Check9& clear();
  Check9& set(int idx);
  Check9& unset(int idx);
  bool check(int idx) const;
  int setCount() const;
  bool allSet() const;
private:
  bool checks_[9];
  int setCount_;
};
}
inline std::ostream& operator << (std::ostream& os, const sudoku::Check9& c9) {
  os << "("<<c9.setCount()<<") [";
  for (int i = 1; i <= 9; i++) {
    if (i > 1) {
      os << ", ";
    }
    os << i<<":"<<(c9.check(i)?"+":"-");
  }
  return os << "]";
}