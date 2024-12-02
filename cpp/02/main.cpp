#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> toStrVector(std::string in, const std::string &sep);
std::vector<int> toIntVector(std::string in, const std::string &sep);
std::vector<long> toLongVector(std::string in, const std::string &sep);

bool isSafe(std::vector<int> report) {
  int k = report[0] - report[1];
  for (int i : report) {
    std::cout << i << ' ';
  }
  std::cout << '\n';
  for (int i = 1; i < report.size(); i++) {
    int diff = report[i - 1] - report[i];
    if (k < 0) {
      if (diff > 0) {
        std::cout << report[i - 1] << '<' << report[i] << '\n';
        return false;
      }
    } else if (k > 0) {
      if (diff < 0) {
        std::cout << report[i - 1] << '>' << report[i] << '\n';
        return false;
      }
    } else {
      return false;
    }
    if (!(1 <= abs(diff) && abs(diff) <= 3)) {
      std::cout << "diff: " << diff << '\n';
      return false;
    }
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
      for (int i = 0; i < report.size(); i++) {
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
