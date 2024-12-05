#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../UtilsLib/UtilsLib.h"

std::pair<int, int>
get_rule_break(std::vector<int> update,
               std::unordered_map<int, std::vector<int>> rules) {
  std::vector<int> curr_rule;
  for (size_t i = 0; i < update.size(); i++) {
    curr_rule = rules[update[i]];
    for (size_t j = i + 1; j < update.size(); j++) {
      if (std::find(curr_rule.begin(), curr_rule.end(), update[j]) ==
          curr_rule.end()) {

        return {i, j};
      }
    }
  }
  return {-1, -1};
}

void get_updates_rules(std::vector<std::string> lines,
                       std::unordered_map<int, std::vector<int>> &rules,
                       std::vector<std::vector<int>> &updates) {

  std::vector<int> matches;
  bool at_rules = true;
  for (std::string line : lines) {
    if (!(line == "")) {
      if (at_rules) {
        matches = toIntVector(line, "|");
        rules[matches[0]].push_back(matches[1]);
      } else {
        updates.push_back(toIntVector(line, ","));
      }
    } else {
      at_rules = false;
      continue;
    }
  }
}

void swap_elements(std::vector<int> &vec, int i, int j) {
  int temp = vec[i];
  vec[i] = vec[j];
  vec[j] = temp;
}

int partone(std::vector<std::string> lines) {
  int res = 0;
  std::unordered_map<int, std::vector<int>> rules;
  std::vector<std::vector<int>> updates;
  std::vector<int> matches;
  get_updates_rules(lines, rules, updates);
  for (std::vector<int> update : updates) {
    std::pair<int, int> rule_break = get_rule_break(update, rules);
    if (rule_break.first != -1 && rule_break.second != -1) {
      res += update[update.size() / 2];
    }
  }
  return res;
}

int parttwo(std::vector<std::string> lines) {
  int res = 0;
  std::unordered_map<int, std::vector<int>> rules;
  std::vector<std::vector<int>> updates;
  std::pair<int, int> rule_break;
  get_updates_rules(lines, rules, updates);
  for (std::vector<int> update : updates) {
    rule_break = get_rule_break(update, rules);
    if (rule_break.first == -1 && rule_break.second == -1) {
      continue;
    }
    while (rule_break.first != -1 && rule_break.second != -1) {
      rule_break = get_rule_break(update, rules);
      swap_elements(update, rule_break.first, rule_break.second);
    }
    res += update[update.size() / 2];
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
