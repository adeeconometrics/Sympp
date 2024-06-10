#ifndef __LAZYPARSER_H__
#define __LAZYPARSER_H__

#include "../include/Expr.hpp"
#include <string>

struct Sym {
  Sym() { m_name = "X"; }
  Sym(std::string name) : m_name(std::move(name)) { }

private:
  std::string m_name;

public:
  auto get_name() const -> std::string { return m_name; }
};

/**
 * @brief Base template for parsing expressions
 *
 * @tparam T type of expression
 */
template <typename Expr> struct Parser {
  static std::string parse(const Expr &expr) { return Expr::parse(expr); }
};

/**
 * @brief Parser specialization for binary expressions
 * 
 * @tparam Op binary operator
 * @tparam Lhs 
 * @tparam Rhs 
 */
template <typename Op, typename Lhs, typename Rhs>
struct Parser<BinaryExpr<Op, Lhs, Rhs>> {
  static std::string parse(const BinaryExpr<Op, Lhs, Rhs> &expr) {
    return Parser<Lhs>::parse(expr.lhs) + " " + Op::get_name() + " " +
           Parser<Rhs>::parse(expr.rhs);
  }
};

/**
 * @brief Parser specialization for unary expressions
 *
 * @tparam Op unary operator
 * @tparam Arg argument
 */
template <typename Op, typename Arg> struct Parser<UnaryExpr<Op, Arg>> {
  static std::string parse(const UnaryExpr<Op, Arg> &expr) {
    return Op::symbol.get_name() + "(" + Parser<Arg>::parse(expr.arg) + ")";
  }
};

/**
 * @brief specialization for Sym
 * 
 * @tparam Sym instance
 */
template <> struct Parser<Sym> {
  static std::string parse(const Sym &symbol) { return symbol.get_name(); }
};

#endif // __LAZYPARSER_H__