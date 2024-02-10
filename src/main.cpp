#include "../include/CoreTypes.hpp"

#include <iostream>
#include <string>

auto main() -> int {
  Int a("12345678901234567890");
  Int b("98765432109876543210");

  std::cout << "a + b = " << a + b << std::endl;
  std::cout << "a - b = " << a - b << std::endl;
  std::cout << "a * b = " << a * b << std::endl;

  return 0;
}