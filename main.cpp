#include "scpp/scpp_ast.h"
#include "scpp/scpp_evaluater.h"
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
    cout << evaluate(i) << evaluate(j) << std::endl;
    cout << evaluate(k) << evaluate(l) << evaluate(m) << evaluate(n) << std::endl;

    return 0;
}
