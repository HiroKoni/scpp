#pragma once
#include <string>
#include <list>
#include <map>
namespace SCPP
{
    using std::list;
    using std::map;
    using std::string;

    enum class Node_Type
    {
        Int,    // 整数型
        Bin,    // 二項演算
        Seq,    // 連接
        Assign, // 代入
        Ident  // 参照
    };

    struct Expr
    {
        enum Node_Type type;
        union
        {
            struct SInt *i;
            struct SBin *b;
            struct SSeq *s;
            struct SAssign *a;
            struct SIdent *id;
        } u;
        Expr() {}
    };

    /* Int */
    struct SInt
    {
        int value;
        SInt(int value);
    };
    SInt::SInt(int value) : value(value)
    {
    }

    /* Bin */
    enum class Op
    {
        Add, // +
        Sub, // -
        Mul, // *
        Div, // /
        Lt,  // <
        Leq, // <=
        Gt,  // >
        Geq, // >=
        Eq,  // ==
        Neq, // !=
    };

    struct SBin
    {
        struct Expr left;
        struct Expr right;
        enum Op op;
        SBin(struct Expr left, struct Expr right, enum Op op);
    };
    SBin::SBin(struct Expr left, struct Expr right, enum Op op) : left(left), right(right), op(op)
    {
    }

    /* Sequence */
    struct SSeq
    {
        list<struct Expr> exprs;
        SSeq(list<struct Expr> exprs);
    };
    SSeq::SSeq(list<struct Expr> exprs) : exprs(exprs)
    {
    }

    /* Variables */
    struct SAssign
    {
        string name;
        struct Expr value;
        SAssign(string name, struct Expr value);
    };
    SAssign::SAssign(string name, struct Expr value) : name(name), value(value)
    {
    }

    struct SIdent
    {
        string name;
        SIdent(string name);
    };
    SIdent::SIdent(string name) : name(name)
    {
    }

    /* Supporting functions */
    struct Expr createInt(int value)
    {
        struct Expr *expr = new Expr();
        expr->type = Node_Type::Int;
        expr->u.i = new SInt(value);
        return *expr;
    }

    struct Expr createAdd(struct Expr left, struct Expr right)
    {
        struct Expr *expr = new Expr();
        expr->type = Node_Type::Bin;
        expr->u.b = new SBin(left, right, Op::Add);
        return *expr;
    }

    struct Expr createSub(struct Expr left, struct Expr right)
    {
        struct Expr *expr = new Expr();
        expr->type = Node_Type::Bin;
        expr->u.b = new SBin(left, right, Op::Sub);
        return *expr;
    }

    struct Expr createMul(struct Expr left, struct Expr right)
    {
        struct Expr *expr = new Expr();
        expr->type = Node_Type::Bin;
        expr->u.b = new SBin(left, right, Op::Mul);
        return *expr;
    }

    struct Expr createDiv(struct Expr left, struct Expr right)
    {
        struct Expr *expr = new Expr();
        expr->type = Node_Type::Bin;
        expr->u.b = new SBin(left, right, Op::Div);
        return *expr;
    }

    struct Expr createLt(struct Expr left, struct Expr right)
    {
        struct Expr *expr = new Expr();
        expr->type = Node_Type::Bin;
        expr->u.b = new SBin(left, right, Op::Lt);
        return *expr;
    }

    struct Expr createLeq(struct Expr left, struct Expr right)
    {
        struct Expr *expr = new Expr();
        expr->type = Node_Type::Bin;
        expr->u.b = new SBin(left, right, Op::Leq);
        return *expr;
    }

    struct Expr createGt(struct Expr left, struct Expr right)
    {
        struct Expr *expr = new Expr();
        expr->type = Node_Type::Bin;
        expr->u.b = new SBin(left, right, Op::Gt);
        return *expr;
    }

    struct Expr createGeq(struct Expr left, struct Expr right)
    {
        struct Expr *expr = new Expr();
        expr->type = Node_Type::Bin;
        expr->u.b = new SBin(left, right, Op::Geq);
        return *expr;
    }

    struct Expr createEq(struct Expr left, struct Expr right)
    {
        struct Expr *expr = new Expr();
        expr->type = Node_Type::Bin;
        expr->u.b = new SBin(left, right, Op::Eq);
        return *expr;
    }

    struct Expr createNeq(struct Expr left, struct Expr right)
    {
        struct Expr *expr = new Expr();
        expr->type = Node_Type::Bin;
        expr->u.b = new SBin(left, right, Op::Neq);
        return *expr;
    }

    template <class... Args>
    struct Expr createSeq(Args... args)
    {
        list<struct Expr> exprs;
        for (struct Expr expr : std::initializer_list<struct Expr>{args...})
        {
            exprs.push_back(expr);
        }
        struct Expr *expr = new Expr();
        expr->type = Node_Type::Seq;
        expr->u.s = new SSeq(exprs);
        return *expr;
    }

    struct Expr createAssign(string name, struct Expr value)
    {
        struct Expr *expr = new Expr();
        expr->type = Node_Type::Assign;
        expr->u.a = new SAssign(name, value);
        return *expr;
    }

    struct Expr createIdent(string name)
    {
        struct Expr *expr = new Expr();
        expr->type = Node_Type::Ident;
        expr->u.id = new SIdent(name);
        return *expr;
    }

} // namespace SCPP
