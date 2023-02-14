#pragma once
#include"scpp_ast.h"
#include <string>
#include <map>
namespace SCPP
{
    using std::string;
    using std::map;

    int evaluate(struct Expr &expr){
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
        case Node_Type::Assign:
            break;
        case Node_Type::Ident:
            break;


        default:
            break;
        }
        return 0;
    }
}// namespace SCPP
