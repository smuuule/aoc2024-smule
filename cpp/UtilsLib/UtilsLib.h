#pragma once

#include <regex>
#include <vector>

std::vector<std::smatch> findMatches(const std::string &input,
                                     const std::vector<std::string> &exps);
std::vector<std::string> toStrVector(std::string in, const std::string &sep);
std::vector<int> toIntVector(std::string in, const std::string &sep);
std::vector<long> toLongVector(std::string in, const std::string &sep);
std::vector<unsigned long long> toULongLongVector(std::string in,
                                                  const std::string &sep);
std::vector<std::string> readFile(std::string file_string);
