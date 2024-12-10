#include "UtilsLib.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

std::vector<std::smatch> findMatches(const std::string &input,
                                     const std::vector<std::string> &exps) {
  std::vector<std::smatch> matches;

  for (std::string exp : exps) {
    std::regex pattern(exp);
    std::sregex_iterator begin(input.begin(), input.end(), pattern);
    std::sregex_iterator end;
    for (std::sregex_iterator it = begin; it != end; ++it) {
      matches.push_back(*it);
    }
  }

  sort(matches.begin(), matches.end(),
       [](const std::smatch &a, const std::smatch &b) {
         return a.position() < b.position();
       });

  return matches;
}

std::vector<std::string> toStrVector(std::string in, const std::string &sep) {
  std::vector<std::string> out;
  auto pos = in.find(sep);

  while (pos != std::string::npos) {
    out.push_back(in.substr(0, pos));
    in.erase(0, pos + sep.length());
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
std::vector<unsigned long long> toULongLongVector(std::string in,
                                                  const std::string &sep) {
  std::vector<std::string> strVector = toStrVector(in, sep);
  std::vector<unsigned long long> out;
  for (std::string str : strVector) {
    out.push_back(std::stoll(str));
  }
  return out;
}

std::vector<std::string> readFile(std::string file_string) {
  std::ifstream file(file_string);
  std::vector<std::string> lines;
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      lines.push_back(line);
    }
    file.close();
  } else {
    std::cerr << "File \"" << file_string << "\" could not be found!"
              << std::endl;
    return {};
  }
  return lines;
}
