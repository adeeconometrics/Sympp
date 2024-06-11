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

struct AndOp {
  static auto get_name() -> const std::string { return "&&"; }
};

template <typename Lhs, typename Rhs>
auto operator&&(const Lhs &lhs, const Rhs &rhs) -> BinaryExpr<AndOp, Lhs, Rhs> {
  return BinaryExpr<AndOp, Lhs, Rhs>(lhs, rhs);
}

struct OrOp {
  static auto get_name() -> const std::string { return "||"; }
};

template <typename Lhs, typename Rhs>
auto operator||(const Lhs &lhs, const Rhs &rhs) -> BinaryExpr<OrOp, Lhs, Rhs> {
  return BinaryExpr<OrOp, Lhs, Rhs>(lhs, rhs);
}
struct NegOp {
  static auto get_name() -> const std::string { return "-"; }
};

template <typename Arg>
auto operator-(const Arg &arg) -> UnaryExpr<NegOp, Arg> {
  return UnaryExpr<NegOp, Arg>(arg);
}

struct NotOp {
  static auto get_name() -> const std::string { return "!"; }
};

template <typename Arg>
auto operator!(const Arg &arg) -> UnaryExpr<NotOp, Arg> {
  return UnaryExpr<NotOp, Arg>(arg);
}

struct SinOp {
  static auto get_name() -> const std::string { return "sin"; }
};

template <typename Arg>
auto sin(const Arg &arg) -> UnaryExpr<SinOp, Arg> {
  return UnaryExpr<SinOp, Arg>(arg);
}

struct CosOp {
  static auto get_name() -> const std::string { return "cos"; }
};

template <typename Arg>
auto cos(const Arg &arg) -> UnaryExpr<CosOp, Arg> {
  return UnaryExpr<CosOp, Arg>(arg);
}

struct TanOp {
  static auto get_name() -> const std::string { return "tan"; }
};

template <typename Arg>
auto tan(const Arg &arg) -> UnaryExpr<TanOp, Arg> {
  return UnaryExpr<TanOp, Arg>(arg);
}
#endif // __COREOPS_H__