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
        Ident,  // 参照
        If,     // 条件分岐
        While,  // 繰り返し
        Call,   // 関数呼び出し
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
            struct SIf *if_;
            struct SWhile *w;
            struct SCall *c;
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

    /* If */
    struct SIf
    {
        struct Expr condition;
        struct Expr thenClause;
        struct Expr elseClause;
        SIf(struct Expr condition, struct Expr thenClause, struct Expr elseClause);
    };
    SIf::SIf(struct Expr condition, struct Expr thenClause, struct Expr elseClause) : condition(condition), thenClause(thenClause), elseClause(elseClause)
    {
    }

    /* While */
    struct SWhile
    {
        struct Expr condition;
        struct Expr body;
        SWhile(struct Expr condition, struct Expr body);
    };
    SWhile::SWhile(struct Expr condition, struct Expr body) : condition(condition), body(body)
    {
    }

    /* Function */
    struct SProgram
    {
        list<struct SFunction> functions;
        list<struct Expr> bodies;
        SProgram(list<struct SFunction> functions, list<struct Expr> bodies);
    };
    SProgram::SProgram(list<struct SFunction> functions, list<struct Expr> bodies) : functions(functions), bodies(bodies)
    {
    }

    struct SFunction
    {
        string name;
        list<string> args;
        // list<struct Expr> body;
        struct Expr body;
        SFunction(string name, list<string> args, struct Expr body);
    };
    SFunction::SFunction(string name, list<string> args, struct Expr body) : name(name), args(args), body(body)
    {
    }

    struct SCall
    {
        string name;
        list<struct Expr> args;
        SCall(string name, list<struct Expr> args);
    };
    SCall::SCall(string name, list<struct Expr> args) : name(name), args(args)
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

    struct Expr createIf(struct Expr condition, struct Expr thenClause, struct Expr elseClause = createInt(0)) /* conditionが満たされずelseClauseが与えられていない場合、0を返す */
    {
        struct Expr *expr = new Expr();
        expr->type = Node_Type::If;
        expr->u.if_ = new SIf(condition, thenClause, elseClause);
        return *expr;
    }

    struct Expr createWhile(struct Expr condition, struct Expr body)
    {
        struct Expr *expr = new Expr();
        expr->type = Node_Type::While;
        expr->u.w = new SWhile(condition, body);
        return *expr;
    }

    template <class... Args>
    struct SProgram createProgram(list<struct SFunction> functions, Args... bodies)
    {
        list<struct Expr> exprs;
        for (struct Expr expr : std::initializer_list<struct Expr>{bodies...})
        {
            exprs.push_back(expr);
        }
        return SProgram(functions, exprs);
    }

    template <class... Args>
    list<struct SFunction> createFunctionList(Args... functions)
    {
        list<struct SFunction> funcList;
        for (struct SFunction func : std::initializer_list<struct SFunction>{functions...})
        {
            funcList.push_back(func);
        }
        return funcList;
    }

    template <class... Args>
    struct SFunction createFunction(string name, list<string> args, Args... bodies)
    {

        // list<struct Expr> exprs;
        // for (struct Expr expr : std::initializer_list<struct Expr>{bodies...})
        // {
        //     exprs.push_back(expr);
        // }
        // struct Expr *expr = new Expr();
        // expr->type = Node_Type::Seq;
        // expr.u.s = new SSeq(exprs);
        return SFunction(name, args, createSeq(bodies...));
    }

    template <class... Args>
    list<string> createParamList(Args... args)
    {
        list<string> argList;
        for (string arg : std::initializer_list<string>{args...})
        {
            argList.push_back(arg);
        }
        return argList;
    } /* 何も与えられなかったら空のリストを返す */

    template <class... Args>
    struct Expr createCall(string name, Args... args)
    {
        list<struct Expr> exprs;
        for (struct Expr expr : std::initializer_list<struct Expr>{args...})
        {
            exprs.push_back(expr);
        }
        struct Expr *expr = new Expr();
        expr->type = Node_Type::Call;
        expr->u.c = new SCall(name, exprs);
        return *expr;
    }

} // namespace SCPP
