/*
    Part of the C++ Sudoku Solver codebase
    https://github.com/mohaps/Sudoku
    License: Apache 2.0

    Author: Saurav Mohapatra (mohaps@gmail.com)
 */
#include "sudoku/Check9.h"
#include "sudoku/Board.h"
#include "sudoku/Solver.h"
#include "sudoku/Helper.h"
#include <stdexcept>

namespace sudoku {
class App {
public:
  static void run(int argc, char** argv) {
    if (argc < 2) {
      std::cerr << "usage: sudoku_solver <input-board-file>" << std::endl;
      throw std::invalid_argument("need board file name");
    }
    std::string boardFile = argv[1];
    std::cout << "[Loading] File="<<boardFile<<" ..." << std::endl;
    Board b;
    Helper::loadFromFile(b, boardFile);
    b.print(std::cout << "[Loaded Sudoku Board]=> " << std::endl);
    Solver s;
    StopWatch sw;
    if (s.solve(b)) {
      b.print(std::cout << "[Solution] => (time taken: "<<sw.elapsedMicros()<<" us)"<<std::endl);
    } else {
      b.print(std::cout << "[Could not Solve] => (time taken: "<<sw.elapsedMicros()<<" us)" << std::endl);
    }
  }
  static void testChecks() {
    Check9 c9;
    std::cout << "initial: " << c9 << std::endl;
    c9.set(2).set(7).set(1).set(5);
    std::cout << "changed 1: " << c9 << std::endl;
    c9.set(3).set(4).set(6).set(9).set(8);
    std::cout << "changed 2: " << c9 << std::endl;
    if (c9.allSet()) {
      std::cout << "all set" << std::endl;
    }
    c9.clear();
    std::cout << "cleared: " << c9 << std::endl;
  }
};
}

int main(int argc, char** argv) {
  try {
    sudoku::App::run(argc, argv);
  } catch (std::exception& ex) {
    std::cerr << "error: " << ex.what() << std::endl;
    return -1;
  }
  return 0;
}