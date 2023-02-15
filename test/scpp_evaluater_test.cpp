
#include <gtest/gtest.h>
#include "../scpp/scpp_ast.hpp"
#include "../scpp/scpp_evaluater.hpp"

// Test for createInt
TEST(SCPPTest, createInt) {
  using namespace SCPP;
  Expr i = createInt(3);
  EXPECT_EQ(i.type, Node_Type::Int);
  EXPECT_EQ(evaluate(i), 3);

  Expr j = createInt(4);
  EXPECT_EQ(j.type, Node_Type::Int);
  EXPECT_EQ(evaluate(j), 4);
}