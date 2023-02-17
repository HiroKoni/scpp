/* This is a sample program of SCPP. */

#include "scpp/scpp_ast.hpp"
#include "scpp/scpp_evaluater.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    using std::cin;
    using std::cout;
    using namespace SCPP;

    auto expression = tAdd(tInt(1),tInt(5)); /* 1+5 */
    cout << evaluate(expression) << std::endl; /* evaluate the expression */

    auto program = tProgram(
        FunctionList(
            tFunction(
                "isOdd",
                ParamList("a"),
                tIf(tEq(tMod(tIdent("a"), tInt(2)), tInt(0)), tInt(0), tInt(1))),
            tFunction(
                "isEven",
                ParamList("a"),
                tIf(tEq(tMod(tIdent("a"), tInt(2)), tInt(0)), tInt(1), tInt(0)))),
        tAssign("a", tInt(231)),
        tAssign("b", tInt(150)),
        tAssign("c", tCall("isOdd", tIdent("a"))),
        tAssign("d", tCall("isEven", tIdent("b"))),
        tAnd(tIdent("c"), tIdent("d"))); /* function isOdd(a){if(a%2==0) return 0; else return 1;} function isEven(a){if(a%2==0) return 1; else return 0;} a = 231; b = 150; c = isOdd(a); d = isEven(b); c && d; */

    cout << evaluateProgram(program) << std::endl;/* evaluate the program */

    return 0;
}
