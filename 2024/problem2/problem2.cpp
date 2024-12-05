#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "input.h"

using problem_input = std::vector<std::vector<int>>;

problem_input get_problem_input() {
  problem_input lines;
  std::string line_str;
  std::string num_str;
  std::vector<int> line_vect;
  std::stringstream input(download_input("2024", "2"));
  while (std::getline(input, line_str)) {
    std::stringstream s(line_str);
    while (std::getline(s, num_str, ' ')) {
      line_vect.push_back(std::stoi(num_str));
    }
    lines.push_back(line_vect);
    line_vect.clear();
  }
  return lines;
}

std::vector<int> differences(std::vector<int> levels) {
  std::vector<int> differences;
  differences.reserve(levels.size() - 1);
  for (int i = 0; i < levels.size() - 1; i++) {
    differences.push_back(levels[i+1] - levels[i]);
  }
  return differences;
}

bool line_is_safe(std::vector<int> line) {
  auto diffs = differences(line);
  auto pred = [&](int d) {return 1 <= std::abs(d) && std::abs(d) <= 3 && std::signbit(d) == std::signbit(diffs[0]);};
  return std::all_of(diffs.begin(), diffs.end(), pred);
}

size_t part_1(problem_input p) {
  size_t safe_lines = 0;
  for (auto &line: p) {
    if (line_is_safe(line)) { safe_lines += 1; }
  }
  return safe_lines;
}

size_t part_2(problem_input p) {
  size_t safe_lines = 0;
  for (auto &line: p) {
    if (line_is_safe(line)) {
      safe_lines += 1;
    }
    else {
      std::vector<int> tmp;
      tmp.resize(line.size() - 1);
      for (size_t i = 0; i < line.size(); ++i) {
	std::copy(line.begin(), line.begin() + i, tmp.begin());
	std::copy(line.begin() + i + 1, line.end(), tmp.begin() + i);
	if (line_is_safe(tmp)) {
	  safe_lines += 1;
	  break;
	}
      }
    }
  }
  return safe_lines;
}

int main() {
  problem_input p = get_problem_input();
  std::cout << "Part 1: " << part_1(p) << std::endl;
  std::cout << "Part 2: " << part_2(p) << std::endl;
  return 0;
}
