/**
 * @file scpp_evaluater.hpp
 * @author Konishi, Hiroto
 * @brief Evaluater for SCPP
 */
#pragma once
#include "scpp_ast.hpp"
#include <iostream>
#include <string>
#include <map>

namespace SCPP
{
    using std::map;
    using std::string;
    map<string, int> globalVars = {};
    map<string, struct SFunction> globalFuncs = {};

    /**
     * @brief 与えられた式を評価する
     *
     * @param expr 評価する式
     * @param env 変数を格納する連想配列。省略時はグローバル変数
     * @param functions 関数を格納する連想配列。省略時はグローバル関数
     * @return int Result 評価結果
     */
    int evaluate(struct Expr &expr, map<string, int> &env = globalVars, map<string, struct SFunction> &functions = globalFuncs)
    {
        switch (expr.type)
        {
        case ExprType::Int:
            return expr.u.i->value;
            case ExprType::Not:
                return !evaluate(expr.u.n->expr, env, functions);
        case ExprType::Bin:
            switch (expr.u.b->op)
            {
            case Op::Add:
                return evaluate(expr.u.b->left, env, functions) + evaluate(expr.u.b->right, env, functions);
            case Op::Sub:
                return evaluate(expr.u.b->left, env, functions) - evaluate(expr.u.b->right, env, functions);
            case Op::Mul:
                return evaluate(expr.u.b->left, env, functions) * evaluate(expr.u.b->right, env, functions);
            case Op::Div:
                return evaluate(expr.u.b->left, env, functions) / evaluate(expr.u.b->right, env, functions);
            case Op::Mod:
                return evaluate(expr.u.b->left, env, functions) % evaluate(expr.u.b->right, env, functions);
            case Op::And:
                return evaluate(expr.u.b->left, env, functions) && evaluate(expr.u.b->right, env, functions);
            case Op::Or:
                return evaluate(expr.u.b->left, env, functions) || evaluate(expr.u.b->right, env, functions);
            case Op::Nor:
                return !(evaluate(expr.u.b->left, env, functions) || evaluate(expr.u.b->right, env, functions));
            case Op::Nand:
                return !(evaluate(expr.u.b->left, env, functions) && evaluate(expr.u.b->right, env, functions));
            case Op::Xor:
                return (evaluate(expr.u.b->left, env, functions) || evaluate(expr.u.b->right, env, functions)) && !(evaluate(expr.u.b->left, env, functions) && evaluate(expr.u.b->right, env, functions));
            case Op::Lt:
                return evaluate(expr.u.b->left, env, functions) < evaluate(expr.u.b->right, env, functions);
            case Op::Leq:
                return evaluate(expr.u.b->left, env, functions) <= evaluate(expr.u.b->right, env, functions);
            case Op::Gt:
                return evaluate(expr.u.b->left, env, functions) > evaluate(expr.u.b->right, env, functions);
            case Op::Geq:
                return evaluate(expr.u.b->left, env, functions) >= evaluate(expr.u.b->right, env, functions);
            case Op::Eq:
                return evaluate(expr.u.b->left, env, functions) == evaluate(expr.u.b->right, env, functions);
            case Op::Neq:
                return evaluate(expr.u.b->left, env, functions) != evaluate(expr.u.b->right, env, functions);
            default:
                break;
            }
        case ExprType::Seq:
        {
            int result = 0;
            for (auto &&i : expr.u.s->exprs)
            {
                result = evaluate(i, env, functions);
            }
            return result;
        }
        case ExprType::Assign:
            env.insert_or_assign(expr.u.a->name, evaluate(expr.u.a->value, env, functions));
            return env[expr.u.a->name];
        case ExprType::Ident:
            return env[expr.u.id->name]; /* 存在しない場合は0が生成される */
        case ExprType::If:
            if (evaluate(expr.u.if_->condition, env, functions))
            {
                return evaluate(expr.u.if_->thenClause, env, functions);
            }
            else
            {
                return evaluate(expr.u.if_->elseClause, env, functions);
            }
        case ExprType::While:
        {
            int result = 0;
            while (evaluate(expr.u.w->condition, env, functions))
            {
                result = evaluate(expr.u.w->body, env, functions);
            }
            return result;
        }
        case ExprType::For:
        {
            int result = 0;
            evaluate(expr.u.f->init, env, functions);
            while (evaluate(expr.u.f->condition, env, functions))
            {
                result = evaluate(expr.u.f->body, env, functions);
                evaluate(expr.u.f->update, env, functions);
            }
            return result;
        }
        case ExprType::Call:
        {
            try
            {
                struct SFunction function = functions.at(expr.u.c->name);
                map<string, int> newEnv = {};
                for (struct Expr i : expr.u.c->args)
                {
                    // newEnv.insert_or_assign(i.u.a->name, evaluate(i.u.a->value, env, functions));
                    newEnv.insert_or_assign(function.args.front(), evaluate(i, env, functions));
                    function.args.pop_front();
                }
                return evaluate(function.body, newEnv);
            }
            catch (const std::out_of_range &e)
            {
                std::cerr << "Error Out of Range in Function Call" << e.what() << std::endl;
                break;
            }
        }

        default:
            std::cerr << "Something went wrong." << std::endl;
            break;
        }
        return 0;
    }

    /**
     * @brief プログラムを評価する
     *
     * @param program 評価するプログラム
     * @return int Result 評価結果
     */
    int evaluateProgram(struct SProgram &program)
    {
        map<string, int> vars = {};
        map<string, struct SFunction> funcs = {};
        for (struct SFunction function : program.functions)
        {
            funcs.insert_or_assign(function.name, function);
        }
        int result = 0;
        for (struct Expr expr : program.bodies)
        {
            result = evaluate(expr, vars, funcs);
        }
        return result;
    }
} // namespace SCPP
