#include <iostream>
#include <string>
#include <vector>

#include "../UtilsLib/UtilsLib.h"

int partone(std::vector<std::string> lines) { return -1; }

int parttwo(std::vector<std::string> lines) { return -1; }

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
