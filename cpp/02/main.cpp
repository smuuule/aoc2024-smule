#include <iostream>
#include <string>
#include <vector>

#include "../UtilsLib/UtilsLib.h"

bool isSafe(std::vector<int> report) {
  int k = report[0] - report[1];
  for (size_t i = 1; i < size(report); i++) {
    int diff = report[i - 1] - report[i];
    if (k < 0 && diff > 0)
      return false;
    if (k > 0 && diff < 0)
      return false;
    if (k == 0)
      return false;
    if (abs(diff) < 1 || abs(diff) > 3)
      return false;
  }
  return true;
}

int partone(std::vector<std::string> lines) {
  int count = 0;
  for (std::string line : lines) {
    std::vector<int> report = toIntVector(line, " ");
    if (isSafe(report)) {
      count++;
    }
  }
  return count;
}

int parttwo(std::vector<std::string> lines) {
  int count = 0;
  for (std::string line : lines) {
    std::vector<int> report = toIntVector(line, " ");
    if (isSafe(report)) {
      count++;
    } else {
      for (size_t i = 0; i < size(report); i++) {
        std::vector<int> new_report = report;
        new_report.erase(new_report.begin() + i);
        if (isSafe(new_report)) {
          count++;
          break;
        }
      }
    }
  }
  return count;
}

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
