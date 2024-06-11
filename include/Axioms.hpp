#ifndef __AXIOMS_H__
#define __AXIOMS_H__

#include <memory>
#include <string>

class Expr {
public:
    virtual ~Expr() = default;
};

class Var : public Expr {
public:
    std::string name;
    Var(std::string name) : name(std::move(name)) {}
};

class Not : public Expr {
public:
    std::shared_ptr<Expr> arg;
    Not(std::shared_ptr<Expr> arg) : arg(std::move(arg)) {}
};

class And : public Expr {
public:
    std::shared_ptr<Expr> lhs, rhs;
    And(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : lhs(std::move(lhs)), rhs(std::move(rhs)) {}
};

class Or : public Expr {
public:
    std::shared_ptr<Expr> lhs, rhs;
    Or(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : lhs(std::move(lhs)), rhs(std::move(rhs)) {}
};
#endif // __AXIOMS_H__