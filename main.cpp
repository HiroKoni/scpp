#include "scpp/scpp_ast.hpp"
#include "scpp/scpp_evaluater.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    using std::cin;
    using std::cout;
    using namespace SCPP;
    Expr i = createInt(3);
    Expr j = createInt(4);
    Expr k = createAdd(i, j);
    Expr l = createSub(k, j);
    Expr m = createAdd(
        createMul(
            i,
            createInt(4)),
        createDiv(
            createInt(5),
            createInt(6)));
    Expr n = createLt(
        createInt(3),
        createAdd(
            createInt(4),
            createInt(5)));
    // Expr o = createAssign(
    //     "a",
    //     createInt(3));
    // Expr p = createSeq(createAssign("a", createInt(3)), createAssign("b", createInt(4)), createAssign("a", createAdd(createIdent("a"), createIdent("b"))), createIdent("a"));
    Expr q = createIf(
        createLt(
            createInt(1650),
            createAdd(
                createInt(4),
                createInt(5))),
        createAssign(
            "a",
            createInt(3)));
    Expr r = createWhile(
        createLt(
            createIdent("a"),
            createInt(3)),
        createSeq(
            createAssign(
                "a",
                createAdd(
                    createIdent("a"),
                    createInt(1))),
            createAssign(
                "b",
                createAdd(
                    createIdent("b"),
                    createInt(15)))));
    auto Program = createProgram(
        createFunctionList(
            createFunction(
                "add",
                createParamList("a", "b"),
                createAdd(
                    createIdent("a"),
                    createIdent("b"))) /* add(a,b){return a+b} */
            ),
        createAssign("a", createInt(3)),                                          /* a=3 */
        createAssign("b", createInt(4)),                                          /* b=4 */
        createAssign("a", createCall("add", createIdent("a"), createIdent("b"))), /* a=add(a,b) */
        createAssign("c", createInt(10)),                                         /* c=10 */
        createCall("add", createIdent("a"), createIdent("c"))/* add(a,c) */);

    cout << evaluate(i) << evaluate(j) << std::endl;
    // cout << evaluate(k) << evaluate(l) << evaluate(m) << evaluate(n) << evaluate(o) << std::endl;
    // cout << evaluate(p) << std::endl;
    cout << evaluate(q) << std::endl;
    cout << evaluate(r) << std::endl;
    cout << evaluateProgram(Program) << std::endl;

    return 0;
}
