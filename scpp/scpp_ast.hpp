/**
 * @file scpp_ast.hpp
 * @author Konishi, Hiroto
 * @brief Abstract Syntax Tree for SCPP
 */
#pragma once
#include <string>
#include <list>
#include <map>
namespace SCPP
{
    using std::list;
    using std::map;
    using std::string;

    /**
     * @brief 式の種別を表す列挙体
     *
     */
    enum class ExprType
    {
        Int,    /// 整数型
        Bin,    /// 二項演算
        Seq,    /// 連接
        Assign, /// 代入
        Ident,  /// 参照
        If,     /// 条件分岐
        While,  /// 繰り返し
        For,    /// 繰り返し
        Call,   /// 関数呼び出し
    };

    /**
     * @brief 式を表す構造体
     *
     */
    struct Expr
    {
        enum ExprType type;
        union
        {
            struct SInt *i;
            struct SBin *b;
            struct SSeq *s;
            struct SAssign *a;
            struct SIdent *id;
            struct SIf *if_;
            struct SWhile *w;
            struct SFor *f;
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

    /* Binominal Operations */
    /**
     * @brief 二項演算の演算子を表す列挙体
     *
     */
    enum class Op
    {
        Add, // +
        Sub, // -
        Mul, // *
        Div, // /
        Mod, // %
        And, // &&
        Or,  // ||
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

    /* For */
    struct SFor
    {
        struct Expr init;
        struct Expr condition;
        struct Expr update;
        struct Expr body;
        SFor(struct Expr init, struct Expr condition, struct Expr update, struct Expr body);
    };
    SFor::SFor(struct Expr init, struct Expr condition, struct Expr update, struct Expr body) : init(init), condition(condition), update(update), body(body)
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
    /**
     * @brief 整数型の式を作成する
     *
     * @param value 整数値
     * @return struct Expr valueを値としてもつ整数型の式
     */
    struct Expr tInt(int value)
    {
        struct Expr expr;
        expr.type = ExprType::Int;
        expr.u.i = new SInt(value);
        return expr;
    }

    /**
     * @brief 加算の式を作成する
     *
     * @param left 第1項の式
     * @param right 第2項の式
     * @return struct Expr 2項の加算を表す式
     */
    struct Expr tAdd(struct Expr left, struct Expr right)
    {
        struct Expr expr;
        expr.type = ExprType::Bin;
        expr.u.b = new SBin(left, right, Op::Add);
        return expr;
    }

    /**
     * @brief 減算の式を作成する
     *
     * @param left 第1項の式
     * @param right 第2項の式
     * @return struct Expr 2項の減算(第1項-第2項)を表す式
     */
    struct Expr tSub(struct Expr left, struct Expr right)
    {
        struct Expr expr;
        expr.type = ExprType::Bin;
        expr.u.b = new SBin(left, right, Op::Sub);
        return expr;
    }

    /**
     * @brief 乗算の式を作成する
     *
     * @param left 第1項の式
     * @param right 第2項の式
     * @return struct Expr 2項の乗算を表す式
     */
    struct Expr tMul(struct Expr left, struct Expr right)
    {
        struct Expr expr;
        expr.type = ExprType::Bin;
        expr.u.b = new SBin(left, right, Op::Mul);
        return expr;
    }

    /**
     * @brief 除算の式を作成する
     *
     * @param left 第1項の式
     * @param right 第2項の式
     * @return struct Expr 2項の除算(第1項/第2項)を表す式
     * @note SCPPの除算において、小数点以下は0に近くなるように切り捨てられる。
     * @note SCPPにおいて、0除算は未定義動作である。
     */
    struct Expr tDiv(struct Expr left, struct Expr right)
    {
        struct Expr expr;
        expr.type = ExprType::Bin;
        expr.u.b = new SBin(left, right, Op::Div);
        return expr;
    }

    /**
     * @brief 剰余の式を作成する
     *
     * @param left 第1項の式
     * @param right 第2項の式
     * @return struct Expr 2項の剰余(第1項%第2項)を表す式
     */
    struct Expr tMod(struct Expr left, struct Expr right)
    {
        struct Expr expr;
        expr.type = ExprType::Bin;
        expr.u.b = new SBin(left, right, Op::Mod);
        return expr;
    }

    /**
     * @brief 論理ANDの式を作成する
     *
     * @param left 第1項の式
     * @param right 第2項の式
     * @return struct Expr 2項の論理ANDを表す式
     * @note 非ゼロを真、ゼロを偽と評価する。
     */
    struct Expr tAnd(struct Expr left, struct Expr right)
    {
        struct Expr expr;
        expr.type = ExprType::Bin;
        expr.u.b = new SBin(left, right, Op::And);
        return expr;
    }

    /**
     * @brief 論理ORの式を作成する
     *
     * @param left 第1項の式
     * @param right 第2項の式
     * @return struct Expr 2項の論理ORを表す式
     * @note 非ゼロを真、ゼロを偽と評価する。
     */
    struct Expr tOr(struct Expr left, struct Expr right)
    {
        struct Expr expr;
        expr.type = ExprType::Bin;
        expr.u.b = new SBin(left, right, Op::Or);
        return expr;
    }

    /**
     * @brief 比較演算（未満）の式を作成する
     *
     * @param left 第1項の式
     * @param right 第2項の式
     * @return struct Expr 2項の比較演算(未満; 第1項<第2項)を表す式
     * @note 真の場合1、偽の場合0と評価される。
     */
    struct Expr tLt(struct Expr left, struct Expr right)
    {
        struct Expr expr;
        expr.type = ExprType::Bin;
        expr.u.b = new SBin(left, right, Op::Lt);
        return expr;
    }

    /**
     * @brief 比較演算（以下）の式を作成する
     *
     * @param left 第1項の式
     * @param right 第2項の式
     * @return struct Expr 2項の比較演算(以下; 第1項<=第2項)を表す式
     * @note 真の場合1、偽の場合0と評価される。
     */
    struct Expr tLeq(struct Expr left, struct Expr right)
    {
        struct Expr expr;
        expr.type = ExprType::Bin;
        expr.u.b = new SBin(left, right, Op::Leq);
        return expr;
    }

    /**
     * @brief 比較演算（より大きい）の式を作成する
     *
     * @param left 第1項の式
     * @param right 第2項の式
     * @return struct Expr 2項の比較演算(より大きい; 第1項>第2項)を表す式
     * @note 真の場合1、偽の場合0と評価される。
     */
    struct Expr tGt(struct Expr left, struct Expr right)
    {
        struct Expr expr;
        expr.type = ExprType::Bin;
        expr.u.b = new SBin(left, right, Op::Gt);
        return expr;
    }

    /**
     * @brief 比較演算（以上）の式を作成する
     *
     * @param left 第1項の式
     * @param right 第2項の式
     * @return struct Expr 2項の比較演算(以上; 第1項>=第2項)を表す式
     * @note 真の場合1、偽の場合0と評価される。
     */
    struct Expr tGeq(struct Expr left, struct Expr right)
    {
        struct Expr expr;
        expr.type = ExprType::Bin;
        expr.u.b = new SBin(left, right, Op::Geq);
        return expr;
    }

    /**
     * @brief 比較演算（等しい）の式を作成する
     *
     * @param left 第1項の式
     * @param right 第2項の式
     * @return struct Expr 2項の比較演算(等しい; 第1項==第2項)を表す式
     * @note 真の場合1、偽の場合0と評価される。
     */
    struct Expr tEq(struct Expr left, struct Expr right)
    {
        struct Expr expr;
        expr.type = ExprType::Bin;
        expr.u.b = new SBin(left, right, Op::Eq);
        return expr;
    }

    /**
     * @brief 比較演算（等しくない）の式を作成する
     *
     * @param left 第1項の式
     * @param right 第2項の式
     * @return struct Expr 2項の比較演算(等しくない; 第1項!=第2項)を表す式
     * @note 真の場合1、偽の場合0と評価される。
     */
    struct Expr tNeq(struct Expr left, struct Expr right)
    {
        struct Expr expr;
        expr.type = ExprType::Bin;
        expr.u.b = new SBin(left, right, Op::Neq);
        return expr;
    }

    /**
     * @brief 連接式を作成する
     *
     * @tparam Args struct Exprの可変長引数
     * @param args 式を実行したい順に並べる
     * @return struct Expr 連接式
     */
    template <class... Args>
    struct Expr tSeq(Args... args)
    {
        list<struct Expr> exprs;
        for (struct Expr expr : std::initializer_list<struct Expr>{args...})
        {
            exprs.push_back(expr);
        }
        struct Expr expr;
        expr.type = ExprType::Seq;
        expr.u.s = new SSeq(exprs);
        return expr;
    }

    /**
     * @brief 変数代入式を作成する
     *
     * @param name 変数名
     * @param value 代入する値を表す式
     * @return struct Expr 変数代入式
     * @note 変数が存在しない場合、新たに変数を作成し、valueで初期化することを意味する。
     * @note 既に存在する変数の場合は、valueで上書きすることを意味する。
     */
    struct Expr tAssign(string name, struct Expr value)
    {
        struct Expr expr;
        expr.type = ExprType::Assign;
        expr.u.a = new SAssign(name, value);
        return expr;
    }

    /**
     * @brief 変数参照式を作成する
     *
     * @param name 変数名
     * @return struct Expr 変数参照式
     * @note 変数が存在しない場合、新たに変数を作成し、0で初期化する。
     */
    struct Expr tIdent(string name)
    {
        struct Expr expr;
        expr.type = ExprType::Ident;
        expr.u.id = new SIdent(name);
        return expr;
    }

    /**
     * @brief if式を作成する
     *
     * @param condition 評価するべき条件式
     * @param thenClause 条件式が真の場合に実行するべき式
     * @param elseClause 条件式が偽の場合に実行するべき式
     * @return struct Expr if式
     * @note elseClauseは省略可能であり、省略された場合は整数型式Int(0)として扱われる。
     */
    struct Expr tIf(struct Expr condition, struct Expr thenClause, struct Expr elseClause = tInt(0)) /* conditionが満たされずelseClauseが与えられていない場合、0を返す */
    {
        struct Expr expr;
        expr.type = ExprType::If;
        expr.u.if_ = new SIf(condition, thenClause, elseClause);
        return expr;
    }

    /**
     * @brief while式を作成する
     *
     * @param condition 評価するべき条件式
     * @param body 条件式が真の間に実行するべき式
     * @return struct Expr while式
     * @note 条件式が真にならない場合、0と評価される。
     */
    struct Expr tWhile(struct Expr condition, struct Expr body)
    {
        struct Expr expr;
        expr.type = ExprType::While;
        expr.u.w = new SWhile(condition, body);
        return expr;
    }

    /**
     * @brief for式を作成する
     *
     * @param init 初期化式
     * @param condition 評価するべき条件式
     * @param update 更新式
     * @param body 条件式が真の間に実行するべき式
     * @return struct Expr for式
     * @note 条件式が真にならない場合、0と評価される。
     */
    struct Expr tFor(struct Expr init, struct Expr condition, struct Expr update, struct Expr body)
    {
        struct Expr expr;
        expr.type = ExprType::For;
        expr.u.f = new SFor(init, condition, update, body);
        return expr;
    }

    /**
     * @brief  一つのプログラムを表す構造体を作成する
     *
     * @tparam Args struct Exprの可変長引数
     * @param functions 関数定義式のリスト。 @ref FunctionList "Function List" を用いて作成することを推奨する。
     * @param bodies 式を実行したい順に並べる
     * @return struct SProgram 一つのプログラムを表す構造体
     * @note 同名の関数を定義した場合、後に定義された関数が優先される。
     * @note 関数の評価は前から順に行われる。
     */
    template <class... Args>
    struct SProgram tProgram(list<struct SFunction> functions, Args... bodies)
    {
        list<struct Expr> exprs;
        for (struct Expr expr : std::initializer_list<struct Expr>{bodies...})
        {
            exprs.push_back(expr);
        }
        return SProgram(functions, exprs);
    }

    /**
     * @anchor FunctionList
     * @brief 関数定義式のリストを作成する
     *
     * @tparam Args struct SFunctionの可変長引数
     * @param functions 関数定義式を並べる。個々の関数定義式は、 @ref tFunction "tFunction" を用いて作成できる。
     * @return list<struct SFunction> 関数定義式のリスト
     * @note 引数が与えられない場合、空のリストを返す。
     */
    template <class... Args>
    list<struct SFunction> FunctionList(Args... functions)
    {
        list<struct SFunction> funcList;
        for (struct SFunction func : std::initializer_list<struct SFunction>{functions...})
        {
            funcList.push_back(func);
        }
        return funcList;
    }
    /**
     * @anchor tFunction
     * @brief 関数定義を作成する
     *
     * @param name 関数名
     * @param args 引数の変数名のリスト
     * @param body 関数本体が含む式を実行順に並べる
     * @return struct SFunction 関数定義の構造体
     * @note 関数定義は式ではないことに注意してください。
     */
    template <class... Args>
    struct SFunction tFunction(string name, list<string> args, Args... bodies)
    {
        return SFunction(name, args, tSeq(bodies...));
    }

    /**
     * @brief 引数のリストを作成する
     *
     * @tparam Args stringの可変長引数
     * @param args 引数の変数名を並べる
     * @return list<string> 引数のリスト
     * @note 引数が与えられなかった場合、空のリストが返される。
     */
    template <class... Args>
    list<string> ParamList(Args... args)
    {
        list<string> argList;
        for (string arg : std::initializer_list<string>{args...})
        {
            argList.push_back(arg);
        }
        return argList;
    }

    /**
     * @brief 関数呼び出し式を作成する
     *
     * @tparam Args struct Exprの可変長引数
     * @param name 呼び出す関数の名前
     * @param args 実引数として関数に与える式（仮引数の宣言順に並べる）
     * @return struct Expr 関数呼び出し式
     */
    template <class... Args>
    struct Expr tCall(string name, Args... args)
    {
        list<struct Expr> exprs;
        for (struct Expr expr : std::initializer_list<struct Expr>{args...})
        {
            exprs.push_back(expr);
        }
        struct Expr expr;
        expr.type = ExprType::Call;
        expr.u.c = new SCall(name, exprs);
        return expr;
    }

} // namespace SCPP
