#ifndef __EXPR_H__
#define __EXPR_H__

template <typename Ops, typename Lhs, typename Rhs> struct BinaryExpr {

  BinaryExpr(const Lhs &lhs, const Rhs &rhs) : lhs(lhs), rhs(rhs) {}

// private:
  Lhs lhs;
  Rhs rhs;
  Ops ops;
};

template <typename Op, typename Arg> struct UnaryExpr {

  UnaryExpr(const Arg &arg) : arg(arg) {}

// private:
  Arg arg;
  Op ops;
};

#endif // __EXPR_H__