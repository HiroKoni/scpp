#pragma once
#include"scpp_ast.h"
namespace SCPP
{
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
            default:
                break;
            }
        default:
            break;
        }
        return 0;
    }
}// namespace SCPP
