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

// Test for Unaray Operation (which is, Not)
TEST(SCPPTest, tNot)
{
  using namespace SCPP;
  auto i = tNot(tInt(1));
  EXPECT_EQ(evaluate(i), 0); /* !1==0 */

  auto j = tNot(tInt(0));
  EXPECT_EQ(evaluate(j), 1); /* !0==1 */

  auto k = tNot(tInt(-1));
  EXPECT_EQ(evaluate(k), 0); /* !(-1)==0 */
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

  auto m = tDiv(tInt(-73), tInt(10));
  EXPECT_EQ(evaluate(m), -7); /* (-73)/10==-7 */
}
TEST(SCPPTest, ComplexBin)
{
  using namespace SCPP;
  auto i = tAdd(tInt(1), tMul(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(i), 7); /* 1+(2*3)==7 */

  auto j = tMul(tInt(10), tDiv(tInt(2), tInt(3)));
  EXPECT_EQ(evaluate(j), 0); /* 10*(2/3)==0 */
}
TEST(SCPPTest, tMod)
{
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
TEST(SCPPTest, tLogic)
{
  using namespace SCPP;
  auto i = tAnd(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(i), 1); /* (1&&1)==1 */

  auto j = tAnd(tInt(1), tInt(0));
  EXPECT_EQ(evaluate(j), 0); /* (1&&0)==0 */

  auto k = tAnd(tInt(0), tInt(1));
  EXPECT_EQ(evaluate(k), 0); /* (0&&1)==0 */

  auto l = tAnd(tInt(0), tInt(0));
  EXPECT_EQ(evaluate(l), 0); /* (0&&0)==0 */

  auto m = tAnd(tLeq(tInt(1), tInt(2)), tGt(tInt(1), tInt(0)));
  EXPECT_EQ(evaluate(m), 1); /* (1<=2 && 1>0)==1 */

  auto n = tOr(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(n), 1); /* (1||1)==1 */

  auto o = tOr(tInt(1), tInt(0));
  EXPECT_EQ(evaluate(o), 1); /* (1||0)==1 */

  auto p = tOr(tInt(0), tInt(1));
  EXPECT_EQ(evaluate(p), 1); /* (0||1)==1 */

  auto q = tOr(tInt(0), tInt(0));
  EXPECT_EQ(evaluate(q), 0); /* (0||0)==0 */

  auto r = tOr(tLeq(tInt(1), tInt(2)), tGt(tInt(1), tInt(0)));
  EXPECT_EQ(evaluate(r), 1); /* (1<=2 || 1>0)==1 */


  auto s = tNor(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(s), 0); /* !(1NOR1)==0 */

  auto t = tNor(tInt(1), tInt(0));
  EXPECT_EQ(evaluate(t), 0); /* !(1NOR0)==0 */

  auto u = tNor(tInt(0), tInt(1));
  EXPECT_EQ(evaluate(u), 0); /* !(0NOR1)==0 */

  auto v = tNor(tInt(0), tInt(0));
  EXPECT_EQ(evaluate(v), 1); /* !(0NOR0)==1 */

  auto w = tNand(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(w), 0); /* !(1NAND1)==0 */

  auto x = tNand(tInt(1), tInt(0));
  EXPECT_EQ(evaluate(x), 1); /* !(1NAND0)==1 */

  auto y = tNand(tInt(0), tInt(1));
  EXPECT_EQ(evaluate(y), 1); /* !(0NAND1)==1 */

  auto z = tNand(tInt(0), tInt(0));
  EXPECT_EQ(evaluate(z), 1); /* !(0NAND0)==1 */

  auto aa = tXor(tInt(1), tInt(1));
  EXPECT_EQ(evaluate(aa), 0); /* (1XOR1)==0 */

  auto ab = tXor(tInt(1), tInt(0));
  EXPECT_EQ(evaluate(ab), 1); /* (1XOR0)==1 */

  auto ac = tXor(tInt(0), tInt(1));
  EXPECT_EQ(evaluate(ac), 1); /* (0XOR1)==1 */

  auto ad = tXor(tInt(0), tInt(0));
  EXPECT_EQ(evaluate(ad), 0); /* (0XOR0)==0 */

  auto ae = tAnd(tNot(tGt(tInt(1), tInt(2))), tGt(tInt(1), tInt(0)));
  EXPECT_EQ(evaluate(ae), 1); /* !(1>2) && 1>0 == 1 */
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
  auto i = tWhile(tLeq(tIdent("a"), tInt(10)), tAssign("a", tAdd(tIdent("a"), tInt(1)))); /* while(a<=10) a = a + 1 */
  EXPECT_EQ(evaluate(i), 11);                                                             /* ==11 */
}

// Test for For Expression
TEST(SCPPTest, tFor)
{
  using namespace SCPP;
  auto i = tSeq(tFor(tAssign("a", tInt(0)), tLeq(tIdent("a"), tInt(10)), tAssign("a", tAdd(tIdent("a"), tInt(1))), tInt(0)),tIdent("a")); /* for(a=0; a<=10; a = a + 1) 0 */
  EXPECT_EQ(evaluate(i), 11);                                                                                           /* ==0 */

  auto j = tFor(tAssign("a", tInt(0)), tLeq(tIdent("a"), tInt(10)), tAssign("a", tAdd(tIdent("a"), tInt(1))), tAssign("b", tAdd(tIdent("b"), tIdent("a")))); /* for(a=0; a<=10; a = a + 1) b = b + a  */
  EXPECT_EQ(evaluate(j), 55);                                                                                                                                /* ==55 */

  auto k = tSeq(tAssign("b", tInt(1)), tFor(tAssign("a", tInt(1)), tLeq(tIdent("a"), tInt(10)), tAssign("a", tAdd(tIdent("a"), tInt(1))), tAssign("b", tMul(tIdent("b"), tIdent("a"))))); /* b = 1; for(a=1; a<=10; a = a + 1) b = b * a */
  EXPECT_EQ(evaluate(k), 3628800);                                                                                                                                                        /* ==3628800 */
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