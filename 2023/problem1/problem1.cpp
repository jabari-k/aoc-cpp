#include <cstddef>
#include <cstdio>
#include <map>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

#include "input.h"
#include "problem1.h"

const std::map<std::string, size_t> numerals = {{"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

// TODO: Move to util file
std::vector<std::string> split_lines(std::string s) {
  std::vector<std::string> lines;
  std::string line;
  for (char &c: s) {
    if (c == '\n') {
      lines.push_back(line);
      line.clear();
    }
    else {
      line.push_back(c);
    }
  }
  return lines;
}

template <typename T>
struct parse_result {
  string_parse_tree<T> *node;
  size_t string_pos;
};

template <typename T>
struct string_parse_tree {
  char head;
  bool terminal;
  T value;
  std::map<char, string_parse_tree<T>> next;

  string_parse_tree() {}
  
  string_parse_tree(std::map<std::string, T> m) {
    for (auto &p: m) {
      this->extend(p.first, p.second);
    }
  }

  // Return the node at the largest populated prefix of the input string
  parse_result<T> parse(std::string s) {
    string_parse_tree *current_node = this;
    size_t pos = 0;
    
    while (current_node->next.find(s[pos]) != current_node->next.end()) {
      current_node = &current_node->next.at(s[pos]);
      pos++;
    }
    return {current_node, pos};
  }

  // Extend the parse tree with a path from the root to the end of the input string, filling in any missing intermediate nodes
  void extend(std::string s, T value) {
    parse_result<T> res = this->parse(s);
    string_parse_tree *current_node = res.node;
    for (char &c: std::string(s.begin() + res.string_pos, s.end())) {
      // std::string parent_head = current_node->head;
      current_node->next[c] = {};
      // TODO: Define operator[] on string_parse_tree so that we can automatically set head and value of a node when accessing it from .next for the first time
      current_node = &current_node->next[c];
      current_node->head = c;
      current_node->value = 0;
      current_node->terminal = false;
    }
    current_node->value = value;
    current_node->terminal = true;
  }

  // String representation of the parse tree
  std::string str(size_t depth) {
    // Example output:
    // ('a', 5):
    //   ('b', 6)
    //   ('c', 7)
    // ('d', 8):
    //   ('a', 5)
    std::string indent(depth * 2, ' ');
    std::stringstream sstr;
    sstr << indent << "(\'" << this->head << "\', " << this->value << "):\n";
    for (auto &p : this->next) {
      // char c = p.first;
      string_parse_tree<T> sub_t = p.second;
      std::string sub_t_str = sub_t.str(depth + 1);
      sstr << sub_t_str;
    }
    return sstr.str();
  }
};

size_t extract_two_digit_number(std::string s) {
  std::vector<size_t> ret;
  for (size_t i = 0; i < s.size(); i++) {
    char c = s[i];
    if (c >= '0' && c <= '9') {
      ret.push_back((size_t) c - '0');
    }
  }
  return ret.front() * 10 + ret.back();
}

size_t extract_two_digit_number_with_numerals(std::string s) {
  string_parse_tree t(numerals);
  std::vector<size_t> numbers;
  size_t pos = 0;
  while (pos < s.size()) {
    char c = s[pos];
    if (c >= '0' && c <= '9') {
      numbers.push_back((size_t) c - '0');
    }
    else {
      size_t pos_tmp = pos;
      string_parse_tree current_node = t;
      while (current_node.next.find(s[pos_tmp]) != current_node.next.end()) {
	current_node = current_node.next[s[pos_tmp]];
	if (current_node.terminal) {
	  numbers.push_back(current_node.value);
	  break;
	}
	pos_tmp += 1;
      }
    }
    pos++;
  }
  return numbers.front() * 10 + numbers.back();
}

size_t part1() {
  std::string input = download_input("2023", "1");
  std::vector<std::string> lines = split_lines(input);
  size_t total = 0;
  for (std::string &line: lines) {
    total += extract_two_digit_number(line);
  }
  return total;
}

size_t part2() {
  std::string input = download_input("2023", "1");
  std::vector<std::string> lines = split_lines(input);
  size_t total = 0;
  for (std::string &line: lines) {
    total += extract_two_digit_number_with_numerals(line);
  }
  return total;
}

int main() {
  // string_parse_tree<int> t({{"abc", 1}, {"abd", 2}, {"def", 3}, {"acg", 4}});
  string_parse_tree<size_t> t(numerals);
  std::cout << "Part 1: " << part1() << std::endl;
  std::cout << "Part 2: " << part2() << std::endl;
}
