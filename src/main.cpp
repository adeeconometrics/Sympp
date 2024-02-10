#include "../include/CoreTypes.hpp"
#include "../include/Polynomials.hpp"
#include "../include/Utils.hpp"

#include <iostream>
#include <string>

auto main() -> int {
  Int a("12345678901234567890");
  Int b("98765432109876543210");

  std::cout << "a + b = " << a + b << std::endl;
  std::cout << "a - b = " << a - b << std::endl;
  std::cout << "a * b = " << a * b << std::endl;

  std::vector<Term> polynomial = {{3, 2}, {2, 1}, {5, 2}, {-4, 3}, {7, 1}};

  std::cout << polynomial;
  return 0;
}