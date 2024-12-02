#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::string> toStrVector(std::string in, const std::string &sep);
std::vector<int> toIntVector(std::string in, const std::string &sep);
std::vector<long> toLongVector(std::string in, const std::string &sep);

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
  for (int i = 0; i < left.size(); i++) {
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
  for (int i = 0; i < left.size(); i++) {
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
  std::ifstream file(file_string);
  std::vector<std::string> lines;
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      lines.push_back(line);
    }
    file.close();
  } else {
    std::cerr << "Unable to open file" << std::endl;
  }

  int res1 = partone(lines);
  std::cout << "Part 1 Result: " << res1 << '\n';
  int res2 = parttwo(lines);
  std::cout << "Part 2 Result: " << res2 << '\n';

  return 0;
}

std::vector<std::string> toStrVector(std::string in, const std::string &sep) {
  std::vector<std::string> out;

  // Find first occurrence of the delimiter
  auto pos = in.find(sep);

  // While there are still delimiters in the
  // string
  while (pos != std::string::npos) {

    // Extracting the substring up to the
    // delimiter
    out.push_back(in.substr(0, pos));

    // Erase the extracted part from the
    // original string
    in.erase(0, pos + sep.length());

    // Find the next occurrence of the
    // delimiter
    pos = in.find(sep);
  }
  out.push_back(in);
  return out;
}
std::vector<int> toIntVector(std::string in, const std::string &sep) {
  std::vector<std::string> strVector = toStrVector(in, sep);
  std::vector<int> out;
  for (std::string str : strVector) {
    out.push_back(std::stoi(str));
  }
  return out;
}
std::vector<long> toLongVector(std::string in, const std::string &sep) {
  std::vector<std::string> strVector = toStrVector(in, sep);
  std::vector<long> out;
  for (std::string str : strVector) {
    out.push_back(std::stol(str));
  }
  return out;
}
