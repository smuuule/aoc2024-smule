#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "../UtilsLib/UtilsLib.h"

int partone(std::vector<std::string> lines) {
  std::vector<std::string> exps = {R"(mul\((\d{1,3}),(\d{1,3})\))"};
  std::vector<std::smatch> matches = findMatches(lines[0], exps);
  int res = 0;

  for (std::smatch match : matches) {
    res += std::stoi(match[1]) * std::stoi(match[2]);
  }

  return res;
}

int parttwo(std::vector<std::string> lines) {
  std::vector<std::string> exps = {R"(mul\((\d{1,3}),(\d{1,3})\))", R"(do\(\))",
                                   R"(don't\(\))"};
  std::vector<std::smatch> matches = findMatches(lines[0], exps);
  bool do_next = true;
  int res = 0;

  for (std::smatch match : matches) {
    if (match.size() > 1 && do_next) {
      res += std::stoi(match[1]) * std::stoi(match[2]);
    } else {
      if (match[0] == (do_next ? "don't()" : "do()")) {
        do_next = !do_next;
      }
    }
  }

  return res;
}

int main(int argc, char *argv[]) {
  std::string file_string{"ex.txt"};
  if (argc > 1) {
    file_string = argv[1];
  } else {
    std::cout << "Input file not supplied! Using ex.txt\n";
  }

  std::vector<std::string> lines = readFile(file_string);

  int res1 = partone(lines);
  std::cout << "Part 1 Result: " << res1 << '\n';
  int res2 = parttwo(lines);
  std::cout << "Part 2 Result: " << res2 << '\n';

  return 0;
}
