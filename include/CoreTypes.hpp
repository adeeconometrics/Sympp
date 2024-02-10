#ifndef __CORETYPES_H__
#define __CORETYPES_H__

#include "../include/CoreOps.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Int {
public:
  Int() = default;

  explicit Int(const std::string &s) {
    for (auto it = s.crbegin(); it != s.crend(); ++it) {
      if (*it >= '0' && *it <= '9') {
        num.emplace_back(*it - '0');
      }
    }
  }

  auto operator+(const Int &other) noexcept -> Int const {
    Int result;
    int carry = 0;
    const std::size_t size = std::max(num.size(), other.num.size());
    for (std::size_t i = 0; i < size || carry; ++i) {
      int sum = carry;
      if (i < num.size())
        sum += num[i];
      if (i < other.num.size())
        sum += other.num[i];
      carry = sum / base;
      sum %= base;
      result.num.emplace_back(sum);
    }
    return result;
  }

  auto operator+(int x) const noexcept -> Int {
    Int result;
    int carry = x;
    for (std::size_t i = 0; i < num.size() || carry; ++i) {
      int sum = carry;
      if (i < num.size())
        sum += num[i];
      carry = sum / base;
      sum %= base;
      result.num.emplace_back(sum);
    }
    return result;
  }

  auto operator-(const Int &other) noexcept -> Int const {
    Int result;
    int borrow = 0;
    for (std::size_t i = 0; i < num.size(); ++i) {
      int diff = num[i] - borrow;
      if (i < other.num.size())
        diff -= other.num[i];
      if (diff < 0) {
        diff += base;
        borrow = 1;
      } else {
        borrow = 0;
      }
      result.num.emplace_back(diff);
    }
    // Remove leading zeros
    while (result.num.size() > 1 && result.num.back() == 0) {
      result.num.pop_back();
    }
    return result;
  }

  auto operator-(int x) const noexcept -> Int { return *this + (-x); }

  auto operator*(const Int &other) noexcept -> Int const {
    Int result;
    for (std::size_t i = 0; i < num.size(); ++i) {
      result = result + (other * num[i]).shift_left(i);
    }
    return result;
  }

  auto operator*(int x) const noexcept -> Int {
    Int result;
    int carry = 0;
    for (int n : num) {
      int prod = n * x + carry;
      result.num.emplace_back(prod % base);
      carry = prod / base;
    }
    while (carry) {
      result.num.emplace_back(carry % base);
      carry /= base;
    }
    return result;
  }

  auto operator/(const Int &other) noexcept -> Int const {
    Int result, remainder;
    for (std::size_t i = num.size() - 1; i >= 0; --i) {
      remainder = remainder * base + num[i];
      int quotient = 0;
      while (remainder >= other) {
        remainder = remainder - other;
        quotient++;
      }
      result.num.emplace_back(quotient);
    }
    std::reverse(result.num.begin(), result.num.end());
    // Remove leading zeros
    while (result.num.size() > 1 && result.num.back() == 0) {
      result.num.pop_back();
    }
    return result;
  }

  auto operator/(int x) const noexcept -> Int {
    Int result;
    int remainder = 0;
    for (std::size_t i = num.size() - 1; i >= 0; --i) {
      int dividend = remainder * base + num[i];
      result.num.emplace_back(dividend / x);
      remainder = dividend % x;
    }
    std::reverse(result.num.begin(), result.num.end());
    // Remove leading zeros
    while (result.num.size() > 1 && result.num.back() == 0) {
      result.num.pop_back();
    }
    return result;
  }

  auto operator>=(const Int &other) const -> bool {
    if (num.size() != other.num.size())
      return num.size() >= other.num.size();
    for (std::size_t i = num.size() - 1; i >= 0; --i) {
      if (num[i] != other.num[i])
        return num[i] >= other.num[i];
    }
    return true; // Both are equal
  }

  friend auto operator<<(std::ostream &os, const Int &bi) -> std::ostream & {
    for (auto it = bi.num.rbegin(); it != bi.num.rend(); ++it) {
      os << *it;
    }
    return os;
  }

private:
  auto shift_left(std::size_t places) const noexcept -> Int {
    Int result(*this);
    result.num.insert(result.num.begin(), places, 0);
    return result;
  }

private:
  std::vector<int> num;
  static constexpr int base = 10;
};

// class Decimal {};

#endif // __CORETYPES_H__