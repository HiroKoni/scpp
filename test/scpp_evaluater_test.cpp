
#include <gtest/gtest.h>
#include "../scpp/scpp_ast.hpp"
#include "../scpp/scpp_evaluater.hpp"

// Test for tInt
TEST(SCPPTest, tInt)
{
  using namespace SCPP;
  auto i = tInt(3);
  EXPECT_EQ(i.type, ExprType::Int);
  EXPECT_EQ(evaluate(i), 3); /* 3==3 */

  auto j = tInt(4);
  EXPECT_EQ(j.type, ExprType::Int);
  EXPECT_EQ(evaluate(j), 4); /* 4==4 */
}

// Tests for Binominal Operations
TEST(SCPPTest, tAdd)
{
  using namespace SCPP;
  auto i = tAdd(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(i), 2); /* 1+1==2 */

  auto j = tAdd(tInt(1), tInt(2));
  EXPECT_EQ(evaluate(j), 3); /* 1+2==3 */

  auto k = tAdd(tInt(-100), tInt(100));
  EXPECT_EQ(evaluate(k), 0); /* (-100)+100==0 */

  auto l = tAdd(tInt(1), tAdd(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(l), 6); /* 1+(2+3)==6 */
}
TEST(SCPPTest, tSub)
{
  using namespace SCPP;
  auto i = tSub(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(i), 0); /* 1-1==0 */

  auto j = tSub(tInt(1), tInt(2));
  EXPECT_EQ(evaluate(j), -1); /* 1-2==-1 */

  auto k = tSub(tInt(-100), tInt(100));
  EXPECT_EQ(evaluate(k), -200); /* (-100)-100==-200 */

  auto l = tSub(tInt(1), tSub(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(l), 2); /* 1-(2-3)==2 */
}
TEST(SCPPTest, tMul)
{
  using namespace SCPP;
  auto i = tMul(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(i), 1); /* 1*1==1 */

  auto j = tMul(tInt(1), tInt(2));
  EXPECT_EQ(evaluate(j), 2); /* 1*2==2 */

  auto k = tMul(tInt(-100), tInt(100));
  EXPECT_EQ(evaluate(k), -10000); /* (-100)*100==-10000 */

  auto l = tMul(tInt(10), tMul(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(l), 60); /* 10*(2*3)==6 */

  auto m = tMul(tInt(1), tInt(0));
  EXPECT_EQ(evaluate(m), 0); /* 1*0==0 */
}
TEST(SCPPTest, tDiv)
{
  using namespace SCPP;
  auto i = tDiv(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(i), 1); /* 1/1==1 */

  auto j = tDiv(tInt(6), tInt(2));
  EXPECT_EQ(evaluate(j), 3); /* 6/2==0 */

  auto k = tDiv(tInt(-100), tInt(100));
  EXPECT_EQ(evaluate(k), -1); /* (-100)/100==-1 */

  auto l = tDiv(tInt(2), tInt(3));
  EXPECT_EQ(evaluate(l), 0); /* 2/3==0 */
}
TEST(SCPPTest, ComplexBin)
{
  using namespace SCPP;
  auto i = tAdd(tInt(1), tMul(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(i), 7); /* 1+(2*3)==7 */

  auto j = tMul(tInt(10), tDiv(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(j), 0); /* 10*(2/3)==0 */
}
TEST(SCPPTest, tMod){
  using namespace SCPP;
  auto i = tMod(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(i), 0); /* (1%1)==0 */

  auto j = tMod(tInt(1), tInt(2));
  EXPECT_EQ(evaluate(j), 1); /* (1%2)==1 */

  auto k = tMod(tInt(-100), tInt(100));
  EXPECT_EQ(evaluate(k), 0); /* ((-100)%100)==0 */

  auto l = tMod(tInt(500), tInt(95));
  EXPECT_EQ(evaluate(l), 25); /* (500%95)==25 */
}
TEST(SCPPTest, tEq)
{
  using namespace SCPP;
  auto i = tEq(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(i), 1); /* (1==1)==1 */

  auto j = tEq(tInt(1), tInt(2));
  EXPECT_EQ(evaluate(j), 0); /* (1==2)==0 */

  auto k = tEq(tInt(-100), tInt(100));
  EXPECT_EQ(evaluate(k), 0); /* ((-100)==100)==0 */

  auto l = tEq(tInt(1), tAdd(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(l), 0); /* (1==(2+3))==0 */
}
TEST(SCPPTest, tNeq)
{
  using namespace SCPP;
  auto i = tNeq(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(i), 0); /* (1!=1)==0 */

  auto j = tNeq(tInt(1), tInt(2));
  EXPECT_EQ(evaluate(j), 1); /* (1!=2)==1 */

  auto k = tNeq(tInt(-100), tInt(100));
  EXPECT_EQ(evaluate(k), 1); /* ((-100)!=100)==1 */

  auto l = tNeq(tInt(1), tAdd(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(l), 1); /* (1!=(2+3))==1 */
}
TEST(SCPPTest, tLt)
{
  using namespace SCPP;
  auto i = tLt(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(i), 0); /* (1<1)==0 */

  auto j = tLt(tInt(1), tInt(2));
  EXPECT_EQ(evaluate(j), 1); /* (1<2)==1 */

  auto k = tLt(tInt(-100), tInt(100));
  EXPECT_EQ(evaluate(k), 1); /* ((-100)<100)==1 */

  auto l = tLt(tInt(1), tAdd(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(l), 1); /* (1<(2+3))==1 */

  auto m = tLt(tInt(1), tInt(0));
  EXPECT_EQ(evaluate(m), 0); /* (1<0)==0 */
}
TEST(SCPPTest, tGt)
{
  using namespace SCPP;
  auto i = tGt(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(i), 0); /* (1>1)==0 */

  auto j = tGt(tInt(1), tInt(2));
  EXPECT_EQ(evaluate(j), 0); /* (1>2)==0 */

  auto k = tGt(tInt(-100), tInt(100));
  EXPECT_EQ(evaluate(k), 0); /* ((-100)>100)==0 */

  auto l = tGt(tInt(1), tAdd(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(l), 0); /* (1>(2+3))==0 */

  auto m = tGt(tInt(1), tInt(0));
  EXPECT_EQ(evaluate(m), 1); /* (1>0)==1 */
}
TEST(SCPPTest, tLeq)
{
  using namespace SCPP;
  auto i = tLeq(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(i), 1); /* (1<=1)==1 */

  auto j = tLeq(tInt(1), tInt(2));
  EXPECT_EQ(evaluate(j), 1); /* (1<=2)==1 */

  auto k = tLeq(tInt(-100), tInt(100));
  EXPECT_EQ(evaluate(k), 1); /* ((-100)<=100)==1 */

  auto l = tLeq(tInt(1), tAdd(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(l), 1); /* (1<=(2+3))==1 */

  auto m = tLeq(tInt(1), tInt(0));
  EXPECT_EQ(evaluate(m), 0); /* (1<=0)==0 */
}
TEST(SCPPTest, tGeq)
{
  using namespace SCPP;
  auto i = tGeq(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(i), 1); /* (1>=1)==1 */

  auto j = tGeq(tInt(1), tInt(2));
  EXPECT_EQ(evaluate(j), 0); /* (1>=2)==0 */

  auto k = tGeq(tInt(-100), tInt(100));
  EXPECT_EQ(evaluate(k), 0); /* ((-100)>=100)==0 */

  auto l = tGeq(tInt(1), tAdd(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(l), 0); /* (1>=(2+3))==0 */

  auto m = tGeq(tInt(1), tInt(0));
  EXPECT_EQ(evaluate(m), 1); /* (1>=0)==1 */
}

// Test for If Expression
TEST(SCPPTest, tIf)
{
  using namespace SCPP;
  auto i = tIf(tInt(1), tInt(1), tInt(2));
  EXPECT_EQ(evaluate(i), 1); /* if(1) 1 else 2 */

  auto j = tIf(tInt(0), tInt(1), tInt(2));
  EXPECT_EQ(evaluate(j), 2); /* if(0) 1 else 2 */

  auto k = tIf(tLeq(tInt(1), tInt(2)), tInt(1), tInt(2));
  EXPECT_EQ(evaluate(k), 1); /* if(1<=2) 1 else 2 */

  auto l = tAdd(tInt(1), tIf(tLeq(tInt(1), tInt(2)), tInt(1), tInt(2))); /* 1 + if(1<=2) 1 else 2 */
}

// Test for While Expression
TEST(SCPPTest, tWhile)
{
  using namespace SCPP;
  auto i = tWhile(tLeq(tIdent("a"), tInt(10)), tAssign("a", tAdd(tIdent("a"), tInt(1))));
  EXPECT_EQ(evaluate(i), 11); /* while(a<=10) a = a + 1 */
}

// Test for Sequence
TEST(SCPPTest, tSeq)
{
  using namespace SCPP;
  auto i = tSeq(tAssign("a", tInt(1)), tAssign("b", tInt(2)), tAssign("c", tAdd(tIdent("a"), tIdent("b"))));
  EXPECT_EQ(evaluate(i), 3); /* a = 1; b = 2; c = a + b; */
}

// Test for Programs
TEST(SCPPTest, tProgram)
{
  using namespace SCPP;
  auto program = tProgram(FunctionList(), tAssign("a", tInt(1)), tAssign("b", tInt(2)), tAssign("c", tAdd(tIdent("a"), tIdent("b"))));
  EXPECT_EQ(evaluateProgram(program), 3); /* a = 1; b = 2; c = a + b; */

  auto program2 = tProgram(
      FunctionList(
          tFunction(
              "max",
              ParamList("a", "b"),
              tIf(tGt(tIdent("a"), tIdent("b")), tIdent("a"), tIdent("b")))),
      tAssign("a", tInt(1)),
      tAssign("b", tInt(2)),
      tAssign("c", tCall("max", tIdent("a"), tIdent("b"))));
  EXPECT_EQ(evaluateProgram(program2), 2); /* function max(a, b){if(a>b) return a; else return b;} a = 1; b = 2; c = max(a, b); */
}