#include <type_traits>
#include <string>
#include <iostream>

template <typename Ops, typename Lhs, typename Rhs> struct BinaryExpr {

  BinaryExpr(const Lhs &lhs, const Rhs &rhs) : lhs(lhs), rhs(rhs), ops(Ops(lhs, rhs)) {}


  auto simp() const {
    auto lhs_simp = lhs.simp();
    auto rhs_simp = rhs.simp();
    
    return BinaryExpr<Ops, Lhs, Rhs>(lhs_simp, rhs_simp);
  }

  friend bool operator!=(const BinaryExpr &lhs, const BinaryExpr &rhs) {
    // Implement your comparison logic here
    // For example, you might compare the operands and the operation
    return !(lhs.ops == rhs.ops && lhs.lhs == rhs.lhs && lhs.rhs == rhs.rhs);
  }
  Lhs lhs;
  Rhs rhs;
  Ops ops;
};

template <typename Op, typename Arg> struct UnaryExpr {

  UnaryExpr(const Arg &arg) : arg(arg), ops(Op(arg)) {}

  auto simp() const {
    auto arg_simp = arg.simp();
    return UnaryExpr<Op, Arg>(arg_simp);
  }

  Arg arg;
  Op ops;
};


template <typename Derived> struct Expr {
  constexpr auto expand() const {
    return static_cast<const Derived &>(*this).expand();
  }
  constexpr auto simp() const {
    return static_cast<const Derived &>(*this).simp();
  }
};

struct Sym : Expr<Sym> {
  constexpr Sym(const char* name) : name(name) {}
  constexpr auto expand() -> Sym const { return *this; }
  constexpr auto simp() const -> Sym const { return *this; }
  constexpr auto get_name() const -> const char* { return name; }
  static auto parse(const Sym &sym) -> std::string { return static_cast<std::string>(sym.get_name()); }
private:
  const char* name;
};

// PARSER ----
template <typename Expr> struct Parser {
  static std::string parse(const Expr &expr) { return Expr::parse(expr); }
};

template <typename Op, typename Lhs, typename Rhs>
struct Parser<BinaryExpr<Op, Lhs, Rhs>> {
  static std::string parse(const BinaryExpr<Op, Lhs, Rhs> &expr) {
    return Parser<Lhs>::parse(expr.lhs) + " " + Op::get_name() + " " +
           Parser<Rhs>::parse(expr.rhs);
  }
};

template <typename Op, typename Arg> struct Parser<UnaryExpr<Op, Arg>> {
  static std::string parse(const UnaryExpr<Op, Arg> &expr) {
    return static_cast<std::string>(Op::get_name()) + "(" + Parser<Arg>::parse(expr.arg) + ")";
  }
};

// OPERATORS ----

template <typename Lhs, typename Rhs> struct AndOp : Expr<AndOp<Lhs, Rhs>> {
  Lhs lhs;
  Rhs rhs;
  constexpr AndOp(Lhs lhs, Rhs rhs) : lhs(lhs), rhs(rhs) {}
  constexpr auto expand() const {
    return AndOp<decltype(lhs.expand()), decltype(rhs.expand())>(lhs.expand(),
                                                               rhs.expand());
  }
  constexpr auto simp() const { return expand(); }

  static auto get_name() -> const char* { return "&&"; }
};

template <typename Lhs, typename Rhs>
auto operator&&(const Lhs &lhs, const Rhs &rhs) -> BinaryExpr<AndOp<Lhs,Rhs>, Lhs, Rhs> {
  return BinaryExpr<AndOp<Lhs,Rhs>, Lhs, Rhs>(lhs, rhs);
}

template <typename Lhs, typename Rhs> struct OrOp : Expr<OrOp<Lhs, Rhs>> {
  Lhs lhs;
  Rhs rhs;
  constexpr OrOp(Lhs lhs, Rhs rhs) : lhs(lhs), rhs(rhs) {}
  constexpr auto expand() const {
    if constexpr (std::is_same_v<Rhs, AndOp<Rhs, Rhs>>) {
      return AndOp<OrOp<Lhs, Rhs>, OrOp<Lhs, Rhs>>(
          OrOp<Lhs, Rhs>(lhs, rhs.lhs),
          OrOp<Lhs, Rhs>(lhs, rhs.rhs)); // distributive
    } else {
      return OrOp<decltype(lhs.expand()), decltype(rhs.expand())>(lhs.expand(),
                                                                rhs.expand());
    }
  }
  constexpr auto simp() const { return expand(); }

  static auto get_name() -> const char * { return "||"; }
};

template <typename Lhs, typename Rhs>
auto operator||(const Lhs &lhs,
                const Rhs &rhs) -> BinaryExpr<OrOp<Lhs, Rhs>, Lhs, Rhs> {
  return BinaryExpr<OrOp<Lhs, Rhs>, Lhs, Rhs>(lhs, rhs);
}


template <typename Arg> struct NotOp : Expr<NotOp<Arg>> {
  Arg arg;
  constexpr NotOp(Arg arg) : arg(arg) {}
  constexpr auto expand() const {
    if constexpr (std::is_same_v<Arg, NotOp<Arg>>) {
      return arg.arg; // double negation
    } 
    if constexpr (std::is_same_v<Arg, AndOp<Arg, Arg>>) {
      return OrOp<NotOp<Arg>, NotOp<Arg>>(NotOp<Arg>(arg.lhs),
                                    NotOp<Arg>(arg.rhs)); // demorgan 1
    } 
    if constexpr (std::is_same_v<Arg, OrOp<Arg, Arg>>) {
      return AndOp<NotOp<Arg>, NotOp<Arg>>(NotOp<Arg>(arg.lhs),
                                     NotOp<Arg>(arg.rhs)); // demorgan 2
    } else {
      return NotOp<Arg>(arg.expand());
    }
  }
  constexpr auto simp() const { return expand(); }

  static auto get_name() -> const char * { return "!"; }
};

template <typename Arg>
auto operator!(const Arg &arg) -> UnaryExpr<NotOp<Arg>, Arg> {
  return UnaryExpr<NotOp<Arg>, Arg>(arg);
}

template <typename Expr> constexpr auto expand(const Expr &expr) {
  return expr.expand();
}

template <typename Expr> constexpr auto simp(const Expr &expr) {
  auto base_expr = expr;
  auto reduced_expr = expr.simp();
  while (reduced_expr != base_expr) {
    base_expr = reduced_expr;
    reduced_expr = reduced_expr.simp();
  }
  return reduced_expr;
}

template <typename Expr> auto parse(Expr t_expr) -> std::string {
  return Parser<Expr>::parse(t_expr);
}

auto main() -> int {

    Sym x("x");
    Sym y("y");
    Sym z("z");
    
    auto expr = x && y || !z;
    std::cout << parse(simp(expr)) << std::endl;
}