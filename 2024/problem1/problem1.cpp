#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <vector>
#include "input.h"

struct problem_input {
  std::vector<int> left;
  std::vector<int> right;
};

problem_input get_problem_input() {
  std::istringstream input(download_input("2024", "1"));
  std::vector<int> left;
  std::vector<int> right;
  std::string line;
  int val1, val2;
  while (std::getline(input, line)) {
    sscanf(line.c_str(), "%d   %d", &val1, &val2);
    left.push_back(val1);
    right.push_back(val2);
  }

  return {left, right};
}

int part1(problem_input p) {
  auto [left, right] = p;
  std::sort(left.begin(), left.end());
  std::sort(right.begin(), right.end());
 
  int total_difference = 0;
  for (size_t i = 0; i < left.size(); i++) {
    total_difference += std::abs(left[i] - right[i]);
  }
  return total_difference;
}

int part2(problem_input p) {
  auto [left, right] = p;
  
  int similarity_score = 0;
  for (int &r: right) {
    if (std::find(left.begin(), left.end(), r) != left.end()) {
      similarity_score += r;
    }
  }
  return similarity_score;
}


int main() {
  problem_input p = get_problem_input();
  std::cout << part1(p) << std::endl;
  std::cout << part2(p) << std::endl;
}
