#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include "input.h"

using problem_input = std::string;

problem_input get_problem_input() {
  return download_input("2024", "3");
}

struct control_expr {
  bool enable;
};

struct mul_expr {
  int left;
  int right;
};

enum expr_type_tag { mul, control };

struct expr {
  size_t position;
  expr_type_tag tag;
  union {
    control_expr ctrl;
    mul_expr mul;
  };
};

int problem1(problem_input p) {
  // Find valid multiplication expressions
  std::regex pattern("mul\\((\\d{1,3}),(\\d{1,3})\\)", std::regex_constants::ECMAScript);
  std::sregex_iterator begin(p.begin(), p.end(), pattern);
  std::sregex_iterator end;

  int total = 0;
  for (std::sregex_iterator it = begin; it != end; ++it) {
    std::smatch match = *it;
    total += std::stoi(match[1]) * std::stoi(match[2]);
  }
  return total;
}

int problem2(problem_input p) {
  // Find valid expressions (either mul(), do(), or don't() instructions)
  // do() and don't() enable and disable subsequent mul() instructions respectively
  std::regex pattern1("mul\\((\\d{1,3}),(\\d{1,3})\\)", std::regex_constants::ECMAScript);
  std::regex pattern2("do\\(\\)", std::regex_constants::ECMAScript);
  std::regex pattern3("don't\\(\\)", std::regex_constants::ECMAScript);
  std::sregex_iterator mul_begin(p.begin(), p.end(), pattern1);
  std::sregex_iterator mul_end;
  std::sregex_iterator do_begin(p.begin(), p.end(), pattern2);
  std::sregex_iterator do_end;
  std::sregex_iterator dont_begin(p.begin(), p.end(), pattern3);
  std::sregex_iterator dont_end;
  
  std::vector<expr> exprs;
  mul_expr mul_expr;
  control_expr control_expr;
  // Append all expressions to a vector
  for (std::sregex_iterator it = mul_begin; it != mul_end; ++it) {
    std::smatch match = *it;
    expr expr;
    mul_expr.left = std::stoi(match[1]);
    mul_expr.right = std::stoi(match[2]);
    expr.position = match.position();
    expr.tag = mul;
    expr.mul = mul_expr;
    exprs.push_back(expr);
  }
  for (std::sregex_iterator it = do_begin; it != do_end; ++it) {
    std::smatch match = *it;
    expr expr;
    control_expr.enable = true;
    expr.position = match.position();
    expr.tag = control;
    expr.ctrl = control_expr;
    exprs.push_back(expr);
  }
  for (std::sregex_iterator it = dont_begin; it != dont_end; ++it) {
    std::smatch match = *it;
    expr expr;
    control_expr.enable = false;
    expr.position = match.position();
    expr.tag = control;
    expr.ctrl = control_expr;
    exprs.push_back(expr);
  }
  // Sort the vector of expressions by their appearance in the input string
  std::sort(exprs.begin(), exprs.end(),
	    [](expr e1, expr e2) { return e1.position < e2.position; });

  // Execute the sequence of control and mul expressions of the input program storing the output in `total`
  int total = 0;
  bool enabled = true;
  for (expr &expr: exprs) {
    switch (expr.tag) {
    case mul: {
      if (enabled) {
	total += expr.mul.left * expr.mul.right;
      }
      break;
    }
    case control: {
      enabled = expr.ctrl.enable;
      break;
    }
    }
  }
  return total;
}

int main() {
  auto p = get_problem_input();
  std::cout << "Part 1: " << problem1(p) << std::endl;
  std::cout << "Part 2: " << problem2(p) << std::endl;
}
