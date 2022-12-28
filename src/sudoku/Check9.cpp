/*
    Part of the C++ Sudoku Solver codebase
    https://github.com/mohaps/Sudoku
    License: Apache 2.0

    Author: Saurav Mohapatra (mohaps@gmail.com)
 */
#include "sudoku/Check9.h"
#include <cstring>

namespace sudoku {

Check9::Check9() {
  clear();
}

Check9& Check9::clear() {
  setCount_ = 0;
  memset(checks_, 0, sizeof(bool) * 9);
  return *this;
}

Check9& Check9::set(int idx) {
  if (idx > 0 && idx <= 9) {
    if (!checks_[idx - 1]) {
      checks_[idx - 1] = true;
      setCount_ += 1;
    }
  }
  return *this;
}

Check9& Check9::unset(int idx) {
  if (idx > 0 && idx <= 9) {
    if (checks_[idx - 1]) {
      checks_[idx - 1] = false;
      setCount_ -= 1;
    }
  }
  return *this;
}

bool Check9::check(int idx) const {
  if (idx > 0 && idx <= 9) {
    return checks_[idx-1];
  }
  return false;
}

int Check9::setCount() const {
  return setCount_;
}

bool Check9::allSet() const {
  return setCount_ == 9;
}

}