#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../UtilsLib/UtilsLib.h"

int partone(std::vector<std::string> lines) {
  int res = 0;
  std::vector<int> left;
  std::vector<int> right;
  for (std::string line : lines) {
    std::vector<int> split = toIntVector(line, "   ");
    left.push_back(split[0]);
    right.push_back(split[1]);
  }
  std::sort(left.begin(), left.end());
  std::sort(right.begin(), right.end());
  for (size_t i = 0; i < left.size(); i++) {
    res += abs(left[i] - right[i]);
  }
  return res;
}

int parttwo(std::vector<std::string> lines) {
  std::unordered_map<int, int> counts;
  int res = 0;
  std::vector<int> left;
  for (std::string line : lines) {
    std::vector<int> split = toIntVector(line, "   ");
    left.push_back(split[0]);
    counts[split[1]]++;
  }
  for (size_t i = 0; i < left.size(); i++) {
    res += left[i] * counts[left[i]];
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
