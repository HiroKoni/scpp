#pragma once
#include "scpp_ast.h"
#include <string>
#include <map>
namespace SCPP
{
    using std::map;
    using std::string;
    map<string, int> global = {};
    int evaluate(struct Expr &expr, map<string, int> &env = global)
    {
        switch (expr.type)
        {
        case Node_Type::Int:
            return expr.u.i->value;
        case Node_Type::Bin:
            switch (expr.u.b->op)
            {
            case Op::Add:
                return evaluate(expr.u.b->left) + evaluate(expr.u.b->right);
            case Op::Sub:
                return evaluate(expr.u.b->left) - evaluate(expr.u.b->right);
            case Op::Mul:
                return evaluate(expr.u.b->left) * evaluate(expr.u.b->right);
            case Op::Div:
                return evaluate(expr.u.b->left) / evaluate(expr.u.b->right);
            case Op::Lt:
                return evaluate(expr.u.b->left) < evaluate(expr.u.b->right);
            case Op::Leq:
                return evaluate(expr.u.b->left) <= evaluate(expr.u.b->right);
            case Op::Gt:
                return evaluate(expr.u.b->left) > evaluate(expr.u.b->right);
            case Op::Geq:
                return evaluate(expr.u.b->left) >= evaluate(expr.u.b->right);
            case Op::Eq:
                return evaluate(expr.u.b->left) == evaluate(expr.u.b->right);
            case Op::Neq:
                return evaluate(expr.u.b->left) != evaluate(expr.u.b->right);
            default:
                break;
            }
        case Node_Type::Seq:
        {
            int result = 0;
            for (auto &&i : expr.u.s->exprs)
            {
                result = evaluate(i, env);
            }
            return result;
        }
        case Node_Type::Assign:
            env.insert_or_assign(expr.u.a->name, evaluate(expr.u.a->value));
            return env[expr.u.a->name];
        case Node_Type::Ident:
            return env[expr.u.id->name]; /* 存在しない場合は0が生成される */
        default:
            break;
        }
        return 0;
    }
} // namespace SCPP
