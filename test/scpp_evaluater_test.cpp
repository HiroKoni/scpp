
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

// Tests for Comparisons
TEST(SCPPTest, tEq)
{
  using namespace SCPP;
  Expr i = tEq(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(i), 1); /* (1==1)==1 */

  Expr j = tEq(tInt(1), tInt(2));
  EXPECT_EQ(evaluate(j), 0); /* (1==2)==0 */

  Expr k = tEq(tInt(-100), tInt(100));
  EXPECT_EQ(evaluate(k), 0); /* ((-100)==100)==0 */

  Expr l = tEq(tInt(1), tAdd(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(l), 0); /* (1==(2+3))==0 */
}
TEST(SCPPTest, tNeq)
{
  using namespace SCPP;
  Expr i = tNeq(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(i), 0); /* (1!=1)==0 */

  Expr j = tNeq(tInt(1), tInt(2));
  EXPECT_EQ(evaluate(j), 1); /* (1!=2)==1 */

  Expr k = tNeq(tInt(-100), tInt(100));
  EXPECT_EQ(evaluate(k), 1); /* ((-100)!=100)==1 */

  Expr l = tNeq(tInt(1), tAdd(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(l), 1); /* (1!=(2+3))==1 */
}
TEST(SCPPTest, tLt)
{
  using namespace SCPP;
  Expr i = tLt(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(i), 0); /* (1<1)==0 */

  Expr j = tLt(tInt(1), tInt(2));
  EXPECT_EQ(evaluate(j), 1); /* (1<2)==1 */

  Expr k = tLt(tInt(-100), tInt(100));
  EXPECT_EQ(evaluate(k), 1); /* ((-100)<100)==1 */

  Expr l = tLt(tInt(1), tAdd(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(l), 1); /* (1<(2+3))==1 */

  Expr m = tLt(tInt(1), tInt(0));
  EXPECT_EQ(evaluate(m), 0); /* (1<0)==0 */
}
TEST(SCPPTest, tGt)
{
  using namespace SCPP;
  Expr i = tGt(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(i), 0); /* (1>1)==0 */

  Expr j = tGt(tInt(1), tInt(2));
  EXPECT_EQ(evaluate(j), 0); /* (1>2)==0 */

  Expr k = tGt(tInt(-100), tInt(100));
  EXPECT_EQ(evaluate(k), 0); /* ((-100)>100)==0 */

  Expr l = tGt(tInt(1), tAdd(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(l), 0); /* (1>(2+3))==0 */

  Expr m = tGt(tInt(1), tInt(0));
  EXPECT_EQ(evaluate(m), 1); /* (1>0)==1 */
}
TEST(SCPPTest, tLeq)
{
  using namespace SCPP;
  Expr i = tLeq(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(i), 1); /* (1<=1)==1 */

  Expr j = tLeq(tInt(1), tInt(2));
  EXPECT_EQ(evaluate(j), 1); /* (1<=2)==1 */

  Expr k = tLeq(tInt(-100), tInt(100));
  EXPECT_EQ(evaluate(k), 1); /* ((-100)<=100)==1 */

  Expr l = tLeq(tInt(1), tAdd(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(l), 1); /* (1<=(2+3))==1 */

  Expr m = tLeq(tInt(1), tInt(0));
  EXPECT_EQ(evaluate(m), 0); /* (1<=0)==0 */
}
TEST(SCPPTest, tGeq)
{
  using namespace SCPP;
  Expr i = tGeq(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(i), 1); /* (1>=1)==1 */

  Expr j = tGeq(tInt(1), tInt(2));
  EXPECT_EQ(evaluate(j), 0); /* (1>=2)==0 */

  Expr k = tGeq(tInt(-100), tInt(100));
  EXPECT_EQ(evaluate(k), 0); /* ((-100)>=100)==0 */

  Expr l = tGeq(tInt(1), tAdd(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(l), 0); /* (1>=(2+3))==0 */

  Expr m = tGeq(tInt(1), tInt(0));
  EXPECT_EQ(evaluate(m), 1); /* (1>=0)==1 */
}


// Test for If Expression
TEST(SCPPTest, tIf)
{
  using namespace SCPP;
  Expr i = tIf(tInt(1), tInt(1), tInt(2));
  EXPECT_EQ(evaluate(i), 1); /* if(1) 1 else 2 */

  Expr j = tIf(tInt(0), tInt(1), tInt(2));
  EXPECT_EQ(evaluate(j), 2); /* if(0) 1 else 2 */

  Expr k = tIf(tLeq(tInt(1), tInt(2)), tInt(1), tInt(2));
  EXPECT_EQ(evaluate(k), 1); /* if(1<=2) 1 else 2 */

  Expr l = tAdd(tInt(1), tIf(tLeq(tInt(1), tInt(2)), tInt(1), tInt(2))); /* 1 + if(1<=2) 1 else 2 */
}

// Test for While Expression
TEST(SCPPTest, tWhile)
{
  using namespace SCPP;
  Expr i = tWhile(tLeq(tIdent("a"), tInt(10)), tAssign("a", tAdd(tIdent("a"), tInt(1))));
  EXPECT_EQ(evaluate(i), 11); /* while(a<=10) a = a + 1 */
}

// Test for Sequence
TEST(SCPPTest, tSeq)
{
  using namespace SCPP;
  Expr i = tSeq(tAssign("a", tInt(1)), tAssign("b", tInt(2)),tAssign("c", tAdd(tIdent("a"), tIdent("b"))));
  EXPECT_EQ(evaluate(i), 3); /* a = 1; b = 2; c = a + b; */
}
