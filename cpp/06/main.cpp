#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "../UtilsLib/UtilsLib.h"

std::vector<std::pair<int, int>> directions = {
    {0, -1}, {1, 0}, {0, 1}, {-1, 0}};

std::vector<std::string> toMatrix(std::vector<std::string> lines) {
  std::vector<std::string> matrix;
  for (std::string line : lines) {
    matrix.push_back(line);
  }
  return matrix;
}

bool test_loop_matrix(std::vector<std::string> matrix) {
  std::set<std::pair<int, int>> positions;
  int x = -1;
  int y = 0;
  int curr_dir = 0;
  std::pair<std::set<std::pair<int, int>>::iterator, bool> ptr;
  int count = 0;

  for (y = 0; y < matrix.size(); y++) {
    auto it = std::find(matrix[y].begin(), matrix[y].end(), '^');
    if (it != matrix[y].end()) {
      x = it - matrix[y].begin();
      break;
    }
  }

  while (x >= 0 && x < matrix[0].size() && y >= 0 && y < matrix.size()) {
    if (matrix[y][x] == '#') {
      x -= directions[curr_dir].first;
      y -= directions[curr_dir].second;
      curr_dir = (curr_dir + 1) % 4;
      count--;
      continue;
    }
    ptr = positions.insert({x, y});
    if (ptr.second) {
      count = 0;
    } else {
      count++;
    }
    if (count == positions.size()) {
      return true;
    }

    x += directions[curr_dir].first;
    y += directions[curr_dir].second;
  }

  return false;
}

int partone(std::vector<std::string> lines) {
  std::vector<std::string> matrix = toMatrix(lines);
  std::set<std::pair<int, int>> positions;
  int x = -1;
  int y = 0;
  int curr_dir = 0;

  for (y = 0; y < matrix.size(); y++) {
    auto it = std::find(matrix[y].begin(), matrix[y].end(), '^');
    if (it != matrix[y].end()) {
      x = it - matrix[y].begin();
      break;
    }
  }

  while (x >= 0 && x < matrix[0].size() && y >= 0 && y < matrix.size()) {
    if (matrix[y][x] == '#') {
      x -= directions[curr_dir].first;
      y -= directions[curr_dir].second;
      curr_dir = (curr_dir + 1) % 4;
    }
    positions.insert({x, y});

    x += directions[curr_dir].first;
    y += directions[curr_dir].second;
  }

  return positions.size();
}

int parttwo(std::vector<std::string> lines) {
  std::vector<std::string> matrix = toMatrix(lines);
  std::vector<std::string> obs_matrix = matrix;
  std::set<std::pair<int, int>> positions;
  int x = -1;
  int y = 0;
  int curr_dir = 0;
  int res = 0;

  for (y = 0; y < matrix.size(); y++) {
    auto it = std::find(matrix[y].begin(), matrix[y].end(), '^');
    if (it != matrix[y].end()) {
      x = it - matrix[y].begin();
      break;
    }
  }

  while (x >= 0 && x < matrix[0].size() && y >= 0 && y < matrix.size()) {
    if (matrix[y][x] == '#') {
      x -= directions[curr_dir].first;
      y -= directions[curr_dir].second;
      curr_dir = (curr_dir + 1) % 4;
    }
    positions.insert({x, y});

    x += directions[curr_dir].first;
    y += directions[curr_dir].second;
  }

  for (std::pair<int, int> obs : positions) {
    if (obs_matrix[obs.second][obs.first] == '^') {
      continue;
    }
    obs_matrix[obs.second][obs.first] = '#';
    if (test_loop_matrix(obs_matrix)) {
      res++;
    }
    obs_matrix[obs.second][obs.first] = '.';
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

  std::cout << "Part 1 Result: " << partone(lines) << '\n';
  std::cout << "Part 2 Result: " << parttwo(lines) << '\n';

  return 0;
}
