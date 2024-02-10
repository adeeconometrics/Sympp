#ifndef __POLYNOMIALS_H__
#define __POLYNOMIALS_H__

#include <algorithm>
#include <vector>

struct Term {
  int coefficient{};
  int exponent{};
};

// todo
// - [ ] rules for multiply and divide
// - [ ] power and exponentials
auto simplify(std::vector<Term> &t_expr) -> std::vector<Term> {
  std::vector<Term> simplified;
  std::sort(t_expr.begin(), t_expr.end(),
            [](const Term &a, const Term &b) -> bool {
              return a.exponent > b.exponent;
            });

  // combine like terms
  for (const Term &term : t_expr) {
    if (simplified.empty() || term.exponent != simplified.back().exponent) {
      simplified.emplace_back(term);
    } else {
      simplified.back().coefficient += term.coefficient;
    }
  }

  return simplified;
}

#endif // __POLYNOMIALS_H__