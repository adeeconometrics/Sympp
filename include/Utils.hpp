#ifndef __UTILS_H__
#define __UTILS_H__

#include "../include/CoreTypes.hpp"
#include "../include/Polynomials.hpp"

#include <iostream>
#include <ostream>
#include <vector>

auto operator<<(std::ostream &os, const std::vector<Term> &t_expr)
    -> std::ostream & {
  for (std::size_t i = 0; i < t_expr.size(); i++) {
    if (i != 0) {
      os << " + ";
    }
    os << t_expr[i].coefficient << "x^" << t_expr[i].exponent << " ";
  }
  return os << "\n";
}

#endif // __UTILS_H__