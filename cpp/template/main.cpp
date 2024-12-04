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

  std::cout << "Part 1 Result: " << partone(lines) << '\n';
  std::cout << "Part 2 Result: " << parttwo(lines) << '\n';

  return 0;
}
