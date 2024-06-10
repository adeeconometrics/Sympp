#ifndef __COREOPS_H__
#define __COREOPS_H__

#include "../include/Expr.hpp"
#include "../include/CodeGen.hpp"
#include <string>

struct AddOp {
  static auto get_name() -> const std::string { return "+"; }
};

template <typename Lhs, typename Rhs>
auto operator+(const Lhs &lhs, const Rhs &rhs) -> BinaryExpr<AddOp, Lhs, Rhs> {
  return BinaryExpr<AddOp, Lhs, Rhs>(lhs, rhs);
}

struct SubOp {
  static auto get_name() -> const std::string { return "-"; }
};

template <typename Lhs, typename Rhs>
auto operator-(const Lhs &lhs, const Rhs &rhs) -> BinaryExpr<SubOp, Lhs, Rhs> {
  return BinaryExpr<SubOp, Lhs, Rhs>(lhs, rhs);
}

struct MulOp {
  static auto get_name() -> const std::string { return "*"; }
};

template <typename Lhs, typename Rhs>
auto operator*(const Lhs &lhs, const Rhs &rhs) -> BinaryExpr<MulOp, Lhs, Rhs> {
  return BinaryExpr<MulOp, Lhs, Rhs>(lhs, rhs);
}

struct DivOp {
  static auto get_name() -> const std::string { return "/"; }
};

template <typename Lhs, typename Rhs>
auto operator/(const Lhs &lhs, const Rhs &rhs) -> BinaryExpr<DivOp, Lhs, Rhs> {
  return BinaryExpr<DivOp, Lhs, Rhs>(lhs, rhs);
}

struct NegOp {
  static auto get_name() -> const std::string { return "-"; }
};

template <typename Arg>
auto operator-(const Arg &arg) -> UnaryExpr<NegOp, Arg> {
  return UnaryExpr<NegOp, Arg>(arg);
}

struct SinOp {
  static auto get_name() -> const std::string { return "sin"; }
};

template <typename Arg>
auto sin(const Arg &arg) -> UnaryExpr<SinOp, Arg> {
  return UnaryExpr<SinOp, Arg>(arg);
}

#endif // __COREOPS_H__