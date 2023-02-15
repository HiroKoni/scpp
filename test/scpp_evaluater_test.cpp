
#include <gtest/gtest.h>
#include "../scpp/scpp_ast.hpp"
#include "../scpp/scpp_evaluater.hpp"

// Test for tInt
TEST(SCPPTest, tInt)
{
  using namespace SCPP;
  Expr i = tInt(3);
  EXPECT_EQ(i.type, Node_Type::Int);
  EXPECT_EQ(evaluate(i), 3); /* 3==3 */

  Expr j = tInt(4);
  EXPECT_EQ(j.type, Node_Type::Int);
  EXPECT_EQ(evaluate(j), 4); /* 4==4 */
}

// Tests for Binominal Operations
TEST(SCPPTest, tAdd)
{
  using namespace SCPP;
  Expr i = tAdd(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(i), 2); /* 1+1==2 */

  Expr j = tAdd(tInt(1), tInt(2));
  EXPECT_EQ(evaluate(j), 3); /* 1+2==3 */

  Expr k = tAdd(tInt(-100), tInt(100));
  EXPECT_EQ(evaluate(k), 0); /* (-100)+100==0 */

  Expr l = tAdd(tInt(1), tAdd(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(l), 6); /* 1+(2+3)==6 */
}
TEST(SCPPTest, tSub)
{
  using namespace SCPP;
  Expr i = tSub(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(i), 0); /* 1-1==0 */

  Expr j = tSub(tInt(1), tInt(2));
  EXPECT_EQ(evaluate(j), -1); /* 1-2==-1 */

  Expr k = tSub(tInt(-100), tInt(100));
  EXPECT_EQ(evaluate(k), -200); /* (-100)-100==-200 */

  Expr l = tSub(tInt(1), tSub(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(l), 2); /* 1-(2-3)==2 */
}
TEST(SCPPTest, tMul)
{
  using namespace SCPP;
  Expr i = tMul(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(i), 1); /* 1*1==1 */

  Expr j = tMul(tInt(1), tInt(2));
  EXPECT_EQ(evaluate(j), 2); /* 1*2==2 */

  Expr k = tMul(tInt(-100), tInt(100));
  EXPECT_EQ(evaluate(k), -10000); /* (-100)*100==-10000 */

  Expr l = tMul(tInt(10), tMul(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(l), 60); /* 10*(2*3)==6 */

  Expr m = tMul(tInt(1),tInt(0));
  EXPECT_EQ(evaluate(m), 0); /* 1*0==0 */
}
TEST(SCPPTest, tDiv)
{
  using namespace SCPP;
  Expr i = tDiv(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(i), 1); /* 1/1==1 */

  Expr j = tDiv(tInt(6), tInt(2));
  EXPECT_EQ(evaluate(j), 3); /* 6/2==0 */

  Expr k = tDiv(tInt(-100), tInt(100));
  EXPECT_EQ(evaluate(k), -1); /* (-100)/100==-1 */

  Expr l = tDiv(tInt(2), tInt(3));
  EXPECT_EQ(evaluate(l), 0); /* 2/3==0 */
}
TEST(SCPPTest, ComplexBin){
  using namespace SCPP;
  Expr i = tAdd(tInt(1), tMul(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(i), 7); /* 1+(2*3)==7 */

  Expr j = tMul(tInt(10), tDiv(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(j), 0); /* 10*(2/3)==0 */
}
