#include "../include/CodeGen.hpp"
#include "../include/CoreOps.hpp"

#include <iostream>
#include <string>

auto main() -> int {
  // Int a("12345678901234567890");
  // Int b("98765432109876543210");

  // std::cout << "a + b = " << a + b << std::endl;
  // std::cout << "a - b = " << a - b << std::endl;
  // std::cout << "a * b = " << a * b << std::endl;

  // std::vector<Term> polynomial = {{3, 2}, {2, 1}, {5, 2}, {-4, 3}, {7, 1}};

  // std::cout << polynomial;
  // return 0;
  Sym x("x");
  Sym y("y");
  Sym z("z");

  auto expr = x + y * z;
  std::cout << Parser<decltype(expr)>::parse(expr) << std::endl;
}