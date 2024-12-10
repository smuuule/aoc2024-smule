#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../UtilsLib/UtilsLib.h"

struct hash {
  template <typename T, typename U>
  size_t operator()(const std::pair<T, U> &p) const {
    return std::hash<T>()(p.first) ^ std::hash<U>()(p.second);
  }
};

int partone(std::vector<std::string> lines) {
  std::vector<std::string> print_lines = lines;
  std::unordered_map<char, std::vector<std::pair<int, int>>> antennas;
  for (size_t r = 0; r < lines.size(); r++) {
    for (size_t c = 0; c < lines[r].size(); c++) {
      if (isalpha(lines[r][c]) || isdigit(lines[r][c])) {
        antennas[lines[r][c]].push_back(std::make_pair(r, c));
      }
    }
  }

  std::unordered_set<std::pair<int, int>, hash> antinodes;

  for (const auto &pair : antennas) {
    std::vector<std::pair<int, int>> positions = pair.second;
    for (size_t i = 0; i < positions.size(); i++) {
      for (size_t j = i + 1; j < positions.size(); j++) {
        // For every antenna pair
        std::pair<int, int> p1 = positions[i];
        std::pair<int, int> p2 = positions[j];

        int dy = p2.first - p1.first;
        int dx = p2.second - p1.second;
        int gcd = std::gcd(std::abs(dy), std::abs(dx));
        int step_dx = dx / gcd;
        int step_dy = dy / gcd;
        int mx1 = p2.second + step_dx * gcd;
        int my1 = p2.first + step_dy * gcd;
        int mx2 = p1.second - step_dx * gcd;
        int my2 = p1.first - step_dy * gcd;

        int cols = lines[0].size();
        int rows = lines.size();

        if (mx1 >= 0 && mx1 < rows && my1 >= 0 && my1 < cols) {
          print_lines[my1][mx1] = '#';
          antinodes.insert({mx1, my1});
        }
        if (mx2 >= 0 && mx2 < rows && my2 >= 0 && my2 < cols) {
          print_lines[my2][mx2] = '#';
          antinodes.insert({mx2, my2});
        }
      }
    }
  }
  std::cout << '\n';
  for (const auto &line : print_lines) {
    std::cout << line << '\n';
  }
  return antinodes.size();
}

int parttwo(std::vector<std::string> lines) {
  std::vector<std::string> print_lines = lines;
  std::unordered_map<char, std::vector<std::pair<int, int>>> antennas;
  for (size_t r = 0; r < lines.size(); r++) {
    for (size_t c = 0; c < lines[r].size(); c++) {
      if (isalpha(lines[r][c]) || isdigit(lines[r][c])) {
        antennas[lines[r][c]].push_back(std::make_pair(r, c));
      }
    }
  }

  std::unordered_set<std::pair<int, int>, hash> antinodes;

  for (const auto &pair : antennas) {
    std::vector<std::pair<int, int>> positions = pair.second;
    for (size_t i = 0; i < positions.size(); i++) {
      for (size_t j = i + 1; j < positions.size(); j++) {
        // For every antenna pair
        std::pair<int, int> p1 = positions[i];
        std::pair<int, int> p2 = positions[j];

        int dy = p2.first - p1.first;
        int dx = p2.second - p1.second;
        int gcd = std::gcd(std::abs(dy), std::abs(dx));
        int step_dx = dx / gcd;
        int step_dy = dy / gcd;
        int mx1 = p2.second;
        int my1 = p2.first;

        int cols = lines[0].size();
        int rows = lines.size();

        while (mx1 >= 0 && mx1 < rows && my1 >= 0 && my1 < cols) {
          print_lines[my1][mx1] = '#';
          antinodes.insert({mx1, my1});
          mx1 += step_dx * gcd;
          my1 += step_dy * gcd;
        }
        int mx2 = p1.second;
        int my2 = p1.first;
        while (mx2 >= 0 && mx2 < rows && my2 >= 0 && my2 < cols) {
          print_lines[my2][mx2] = '#';
          antinodes.insert({mx2, my2});
          mx2 -= step_dx * gcd;
          my2 -= step_dy * gcd;
        }
      }
    }
  }
  std::cout << '\n';
  for (const auto &line : print_lines) {
    std::cout << line << '\n';
  }
  return antinodes.size();
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
