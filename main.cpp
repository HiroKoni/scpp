#include "scpp/scpp_ast.hpp"
#include "scpp/scpp_evaluater.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    using std::cin;
    using std::cout;
    using namespace SCPP;
    Expr i = tInt(3);
    Expr j = tInt(4);
    Expr k = tAdd(i, j);
    Expr l = tSub(k, j);
    Expr m = tAdd(
        tMul(
            i,
            tInt(4)),
        tDiv(
            tInt(5),
            tInt(6)));
    Expr n = tLt(
        tInt(3),
        tAdd(
            tInt(4),
            tInt(5)));
    // Expr o = tAssign(
    //     "a",
    //     tInt(3));
    // Expr p = tSeq(tAssign("a", tInt(3)), tAssign("b", tInt(4)), tAssign("a", tAdd(tIdent("a"), tIdent("b"))), tIdent("a"));
    Expr q = tIf(
        tLt(
            tInt(1650),
            tAdd(
                tInt(4),
                tInt(5))),
        tAssign(
            "a",
            tInt(3)));
    Expr r = tWhile(
        tLt(
            tIdent("a"),
            tInt(3)),
        tSeq(
            tAssign(
                "a",
                tAdd(
                    tIdent("a"),
                    tInt(1))),
            tAssign(
                "b",
                tAdd(
                    tIdent("b"),
                    tInt(15)))));
    auto Program = tProgram(
        FunctionList(
            tFunction(
                "add",
                ParamList("a", "b"),
                tAdd(
                    tIdent("a"),
                    tIdent("b"))) /* add(a,b){return a+b} */
            ),
        tAssign("a", tInt(3)),                                          /* a=3 */
        tAssign("b", tInt(4)),                                          /* b=4 */
        tAssign("a", tCall("add", tIdent("a"), tIdent("b"))), /* a=add(a,b) */
        tAssign("c", tInt(10)),                                         /* c=10 */
        tCall("add", tIdent("a"), tIdent("c"))/* add(a,c) */);

    cout << evaluate(i) << evaluate(j) << std::endl;
    // cout << evaluate(k) << evaluate(l) << evaluate(m) << evaluate(n) << evaluate(o) << std::endl;
    // cout << evaluate(p) << std::endl;
    cout << evaluate(q) << std::endl;
    cout << evaluate(r) << std::endl;
    cout << evaluateProgram(Program) << std::endl;

    return 0;
}
