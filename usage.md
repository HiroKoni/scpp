## SCPPの使い方
[Webドキュメント「SCPPの使い方」](https://hirokoni.github.io/scpp/md_usage.html)で、名前空間や関数の解説ページへのリンクが貼られたドキュメントを閲覧できます。

[TOC]

### セットアップ
SCPPは、C++17で動作します。
SCPPを使用するためには、`scpp_ast.hpp`と`scpp_evaluater.hpp`の2ファイルをincludeしなければいけません。
```cpp
#include "scpp_ast.hpp"
#include "scpp_evaluater.hpp"
```

### SCPPの構文
SCPPは、整数型を用い、プログラムは式（の組み合わせ）によって記述されます。
式は、`SCPP::Expr` 構造体のインスタンスとして表現されます。

プログラムの記述に用いる関数は、名前空間`SCPP`に定義されています。
```cpp
using namespace SCPP;
```

### 式の記述

#### 整数型
整数型は、C++の`int`型と同様に、16ビット以上の符号付き整数です。
整数型は、 tInt()関数を用いて記述します。
整数型は、式の一種です。

```cpp
tInt(1); // 1
tInt(0); // 0
tInt(-1); // -1
```

#### 四則演算
四則演算（加算`+`、減算`-`、乗算`*`、除算`/`）は、 tAdd(), tSub(), tMul(), tDiv()関数を用いて記述します。
これらの関数は、2つの式`SCPP::Expr`を引数にとります。

```cpp
tAdd(tInt(1), tInt(2)); // 1 + 2
tSub(tInt(1), tInt(2)); // 1 - 2
tMul(tInt(1), tInt(2)); // 1 * 2
tDiv(tInt(1), tInt(2)); // 1 / 2
```

- 0除算は未定義動作です。
- 除算において、小数点以下は0に近づくように切り捨てられます。

#### mod式
mod式は、 tMod()関数を用いて記述します。
これは、2つの式`SCPP::Expr`を引数にとります。

```cpp
tMod(tInt(1), tInt(2)); // 1 % 2
```

#### 比較演算
比較演算（`==`、`!=`、`<`、`<=`、`>`、`>=`）は、 tEq(), tNe(), tLt(), tLe(), tGt(), tGe()関数を用いて記述します。
これらの関数は、2つの式`SCPP::Expr`を引数にとります。

真の場合は1、偽の場合は0として評価されます。

```cpp
tEq(tInt(1), tInt(2)); // 1 == 2
tNe(tInt(1), tInt(2)); // 1 != 2
tLt(tInt(1), tInt(2)); // 1 < 2
tLe(tInt(1), tInt(2)); // 1 <= 2
tGt(tInt(1), tInt(2)); // 1 > 2
tGe(tInt(1), tInt(2)); // 1 >= 2
```

#### 論理演算
##### 単項論理演算
否定`!`は、SCPPに存在する唯一の単項論理演算です。
tNot()関数を用いて記述します。
これは、1つの式`SCPP::Expr`を引数にとります。

評価する式が真（非ゼロ）の場合は0、偽（ゼロ）の場合は1として評価されます。

```cpp
tNot(tInt(1)); // !1
```

##### 二項論理演算
二項論理演算（論理積`AND`、論理和`OR`、排他的論理和`XOR`、論理否定`NAND`、論理否定`NOR`）は、 tAnd(), tOr(), tXor(), tNand(), tNor()関数を用いて記述します。
これらの関数は、2つの式`SCPP::Expr`を引数にとります。

評価する式は、非ゼロの場合真、ゼロの場合偽として評価します。
演算結果が真の場合は1、偽の場合は0として評価されます。

```cpp
tAnd(tInt(1), tInt(2)); // 1 AND 2
tOr(tInt(1), tInt(2)); // 1 OR 2
tXor(tInt(1), tInt(2)); // 1 XOR 2
tNand(tInt(1), tInt(2)); // 1 NAND 2
tNor(tInt(1), tInt(2)); // 1 NOR 2
```

#### 条件分岐式
条件分岐は、 tIf()関数を用いて記述します。
これは、3つの式 `SCPP::Expr` `condition`, `thenClause`, `elseClause`を引数にとります。

`condition`が真の場合は、`thenClause`が評価され、偽の場合は`elseClause`が評価されます。

```cpp
tIf(tEq(tInt(1), tInt(2)), tInt(3), tInt(4)); // (1 == 2) ? 3 : 4
```

#### 変数
変数は、代入及び参照することができます。

##### 変数代入式
変数の代入は、 tAssign()関数を用いて記述します。
この関数は、第1引数として、変数名を表す文字列　`string name`を、第2引数として、代入する式 `SCPP::Expr value`を、それぞれとります。

第1引数として与えられた名前の変数が存在しない場合、新たに変数が宣言され、第2引数の式が代入されます。

変数の代入は、式の一種であり、評価される際は、代入された値、すなわち、第2引数の式の評価結果が返されます。

```cpp
tAssign("x", tInt(1)); // x = 1
```

##### 変数参照式
変数の参照は、 tIdent()関数を用いて記述します。
この関数は、変数名を表す文字列を引数にとります。

与えられた名前の変数が存在しない場合、新たに変数が宣言され、0が代入されます。

```cpp
tIdent("x"); // x
```

#### 連接式
複数の式を連続して実行する、連接式は、 tSeq()関数を用いて記述します。
この関数は、任意の個数の式`SCPP::Expr`を引数にとり、それらを左から順に評価します。
一番最後の式の評価結果が、連接式の評価結果となります。

なお、引数が0個の場合は、0として評価されます。

```cpp
tSeq(tAssign("x", tInt(1)), tAssign("y", tInt(2)), tAdd(tIdent("x"), tIdent("y"))); // x = 1; y = 2; x + y
```

#### 繰り返し
繰り返しは、while式及びfor式の2種類があります。

繰り返しの本体や初期化式ではじめて代入された変数も、グローバル変数として扱われ、繰り返しの外側からも参照可能になります。

##### while式
while式は、 tWhile()関数を用いて記述します。
この関数は、第1引数として、繰り返し条件を表す式`SCPP::Expr condition`を、第2引数として、繰り返し本体を表す式`SCPP::Expr body`を、それぞれとります。

`condition`が真の間、`body`を繰り返し実行します。
`condition`が偽になった時点で、while式の評価結果となります。

初期状態で`condition`が偽の場合、while式の評価結果は0となります。

```cpp
tWhile(tLt(tIdent("x"), tInt(10)), tAssign("x", tAdd(tIdent("x"), tInt(1)))); // while (x < 10) { x = x + 1; }
```
この例において、`tIdent()`が初めて呼ばれた際、変数`x`が宣言され、0が代入されていることに注意してください。

##### for式
for式は、 tFor()関数を用いて記述します。
この関数は、第1引数として、初期化式`SCPP::Expr init`を、第2引数として、繰り返し条件を表す式`SCPP::Expr condition`を、第3引数として、繰り返し後の処理を表す式`SCPP::Expr step`を、第4引数として、繰り返し本体を表す式`SCPP::Expr body`を、それぞれとります。

`init`を実行し、`condition`が真の間、`body`と`step`を続けて実行します。
`condition`が偽になった時点で、for式の評価結果となります。

初期状態で`condition`が偽の場合、for式の評価結果は0となります。

```cpp
tFor(tAssign("x", tInt(0)), tLt(tIdent("x"), tInt(10)), tAssign("x", tAdd(tIdent("x"), tInt(1))), tAssign("y", tAdd(tIdent("y"), tIdent("x")))); // for (x = 0; x < 10; x = x + 1) { y = y + x; }
```

#### 関数呼び出し式
関数呼び出し式は、 tCall()関数を用いて記述します。
この関数は、第1引数として、関数名を表す文字列`string name`を、第2引数として、任意の個数の引数を表す式`SCPP::Expr`を、それぞれとります。

宣言されていない関数を呼び出した場合、エラーとなり、その旨が標準エラー出力に出力されます。式は、0として評価されます。

関数の定義については、後述します。

```cpp
tCall("f", tInt(1), tInt(2), tInt(3)); // f(1, 2, 3)
```

### 式の評価
式は、`evaluate()`関数を用いて評価することができます。

evaluate()関数に、評価したい式を引数として渡すと、その式の評価結果がC++の`int`型として返されます。

```cpp
SCPP::Expr expr = tAdd(tInt(1), tInt(2));
int result = evaluate(expr);
```

### プログラムの記述
プログラム機能を用いると、独自の関数を定義し、それを用いたプログラムを記述することができます。

プログラム内で宣言された変数・関数のスコープは、そのプログラム内です。

#### プログラム構造体の作成
プログラムは、構造体 `SCPP::SFunction`のインスタンスとして表現されます。
実用上、`tProgram()`関数を用いて記述することができます。

この関数は、第1引数として、関数の構造体のリスト `list<struct SCPP::SFunction> functions`をとり、第2引数以降は、0個以上の任意の個数の式`SCPP::Expr`をとります。
`functions`で定義された関数は、プログラムの中で呼び出すことができます。

関数の構造体のリスト`list<struct SCPP::SFunction>`は、`FunctionList()`関数を用いて作成することができます。（後述）
リストは、空であってもよく、複数の同名関数が定義された場合は、最後に定義された関数が優先されます。

評価時には、第2引数から前から順に評価され、最後の式の評価結果が、プログラムの評価結果となります。

```cpp
  auto program = tProgram(FunctionList(), tAssign("a", tInt(1)), tAssign("b", tInt(2)), tAssign("c", tAdd(tIdent("a"), tIdent("b")))); /* a = 1; b = 2; c = a + b; */
```

#### 関数の定義
関数は、構造体 `SCPP::SFunction`のインスタンスとして表現されます。
実用上、`tFunction()`関数を用いて記述することができます。

この関数は、第1引数として、関数名を表す文字列 `string name`を、第2引数として、引数のリスト `list<string> args`を、第3引数以降は、0個以上の任意の個数関数の本体を表す式 `SCPP::Expr`を、それぞれとります。

引数のリスト `list<string> args`は、`ParamList()`関数を用いて作成することができます。
`ParamList`は、0個以上の任意個数の`string`引数名を引数としてとり、それらをリストにして返します。
ParamListの引数として、定義する関数の仮引数の名前を全て指定します。

リストは、空であってもよいですが、同名の仮引数がある場合の動作は未定義です。

```cpp
tFunction(
              "isOdd",
              ParamList("a"),
              tIf(tEq(tMod(tIdent("a"), tInt(2)), tInt(0)), tInt(0), tInt(1))
); // function isOdd(a) { if (a % 2 == 0) { return 0; } else { return 1; } }
```

プログラム構造体の作成の際は、`FunctionList()`関数を用いて、関数の構造体のリストを作成しなくてはなりません。
この関数は、0個以上の任意個数の`SCPP::SFunction`を引数としてとり、それらをリストにして返します。

```cpp
FunctionList(
          tFunction(
              "isOdd",
              ParamList("a"),
              tIf(tEq(tMod(tIdent("a"), tInt(2)), tInt(0)), tInt(0), tInt(1))),
          tFunction(
              "isEven",
              ParamList("a"),
              tIf(tEq(tMod(tIdent("a"), tInt(2)), tInt(0)), tInt(1), tInt(0)))
); // function isOdd(a) { if (a % 2 == 0) { return 0; } else { return 1; } } function isEven(a) { if (a % 2 == 0) { return 1; } else { return 0; } }
```

### プログラムの実行
プログラムは、`evaluateProgram()`関数を用いて実行・評価することができます。

`evaluateProgram()`関数に、実行したいプログラムを引数として渡すと、そのプログラムの評価結果がC++の`int`型として返されます。


```cpp
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
      tAnd(tIdent("c"), tIdent("d"))
);/* function isOdd(a){if(a%2==0) return 0; else return 1;} function isEven(a){if(a%2==0) return 1; else return 0;} a = 231; b = 150; c = isOdd(a); d = isEven(b); c && d; */
int result = evaluateProgram(program);
```


