#include <iostream>
#include <string>
#include <vector>

#include "../UtilsLib/UtilsLib.h"

std::vector<std::string> toMatrix(std::vector<std::string> lines) {
  std::vector<std::string> matrix;
  for (std::string line : lines) {
    matrix.push_back(line);
  }
  return matrix;
}

int followXmas(std::vector<std::string> matrix, size_t x, size_t y,
               std::string word, bool diag_only) {
  int hits = 0;
  int k;

  for (int j = -1; j <= 1; j++) {
    for (int i = -1; i <= 1; i++) {
      size_t curr_x = x;
      size_t curr_y = y;

      for (k = 0; k < word.size(); k++) {
        if (!(curr_x < matrix[0].size() && curr_y < matrix.size()) ||
            matrix[curr_y][curr_x] != word[k]) {

          break;
        }
        if (diag_only && (i == 0 || j == 0)) {
          break;
        }
        curr_x += i;
        curr_y += j;
      }
      if (k == word.size()) {
        hits += 1;
      }
    }
  }
  return hits;
}

int partone(std::vector<std::string> lines) {
  std::vector<std::string> matrix = toMatrix(lines);
  int res = 0;
  for (size_t y = 0; y < matrix.size(); y++) {
    for (size_t x = 0; x < matrix[y].size(); x++) {
      if (matrix[y][x] == 'X') {
        res += followXmas(matrix, x, y, "XMAS", false);
      }
    }
  }
  return res;
}

int parttwo(std::vector<std::string> lines) {
  std::vector<std::string> matrix = toMatrix(lines);
  std::vector<std::string> sub_matrix;
  int res = 0;
  int curr_res = 0;
  for (size_t y = 0; y < matrix.size() - 2; y++) {
    for (size_t x = 0; x < matrix[y].size() - 2; x++) {
      sub_matrix = {matrix[y].substr(x, 3), matrix[y + 1].substr(x, 3),
                    matrix[y + 2].substr(x, 3)};
      curr_res = 0;
      for (size_t i = 0; i < sub_matrix.size(); i++) {
        for (size_t j = 0; j < sub_matrix[i].size(); j++) {
          if (!(i == 1 || j == 1) &&
              followXmas(sub_matrix, i, j, "MAS", true)) {
            curr_res++;
          }
        }
      }
      if (curr_res == 2) {
        res++;
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

  std::cout << "Part 1 Result: " << partone(lines) << '\n';
  std::cout << "Part 2 Result: " << parttwo(lines) << '\n';

  return 0;
}
