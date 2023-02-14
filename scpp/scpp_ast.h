#pragma once
namespace SCPP
{
    enum class Node_Type
    {
        Int,
        Bin
    };

    struct Expr
    {
        enum Node_Type type;
        union{
            struct SInt *i;
            struct Bin *b;
        } u;
        Expr();
    };
    Expr::Expr()
    {
    }


    struct SInt{
        int value;
        SInt(int value);
    };
    SInt::SInt(int value) : value(value)
    {
    }

    enum class Op{
        Add,
        Sub,
        Mul,
        Div
    };

    struct Bin{
        struct Expr left;
        struct Expr right;
        enum Op op;
        Bin(struct Expr left, struct Expr right, enum Op op);
    };
    Bin::Bin(struct Expr left, struct Expr right, enum  Op op) : left(left), right(right), op(op)
    {
    }


    struct Expr createInt(int value){
        struct Expr *expr = new Expr();
        expr->type = Node_Type::Int;
        expr->u.i = new SInt(value);
        return *expr;
    }

    struct Expr createAdd(struct Expr left, struct Expr right){
        struct Expr *expr = new Expr();
        expr->type = Node_Type::Bin;
        expr->u.b = new Bin(left, right, Op::Add);
        return *expr;
    }

    struct Expr createSub(struct Expr left, struct Expr right){
        struct Expr *expr = new Expr();
        expr->type = Node_Type::Bin;
        expr->u.b = new Bin(left, right, Op::Sub);
        return *expr;
    }

    struct Expr createMul(struct Expr left, struct Expr right){
        struct Expr *expr = new Expr();
        expr->type = Node_Type::Bin;
        expr->u.b = new Bin(left, right, Op::Mul);
        return *expr;
    }

    struct Expr createDiv(struct Expr left, struct Expr right){
        struct Expr *expr = new Expr();
        expr->type = Node_Type::Bin;
        expr->u.b = new Bin(left, right, Op::Div);
        return *expr;
    }

} // namespace SCPP
