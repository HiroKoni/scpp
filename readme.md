# SCPP
SCPP(SCripting language in c Plus Plus) は、C++で動作する、抽象構文木を用いた簡単なプログラミング言語のインタプリタです。

整数型の四則演算式、mod式、主要な比較式(`==`, `!=`, `>`, `<`, `>=`, `<=`, `&&`, `||`)、`if`式、`while`式、`for`式、変数の定義・代入・参照、連接式をサポートし、関数定義も行えます。

このプログラムは、筑波大学2022年度GB27001「ソフトウェアサイエンス特別講義A」の提出課題です。同授業内で解説された、[minis](https://github.com/kmizu/minis)を参考にして作成されています。

[Webドキュメント](https://hirokoni.github.io/scpp/)が利用可能です。

## 環境
C++17で動作します。

付属するテストは、[Google Test](https://github.com/google/googletest)を用いたものです。
`CMakeLists.txt`を用いて、バージョン3.14以降のCmakeによりビルドすることで、テスト環境を容易に準備することができます。
（[参考リンク](https://google.github.io/googletest/quickstart-cmake.html#create-and-run-a-binary)）

### 開発に用いた環境
- Ubuntu 20.04.5 LTS on WSL2
- CMake 3.16.3
- g++ 9.4.0

## 主要な仕様
- 実行環境におけるC++の`int`型の範囲で動作します。
- 0除算は未定義動作です。
- 除算において、小数点以下は切り捨てられます。
- 宣言されていない変数を参照しようとした場合、その変数が宣言され、0で初期化されます。
- `While`式及び`For`式において、条件式が満たされることがない場合、その式は0と評価されます。
- 変数と関数は、別の環境で管理されるため、同名の変数と関数を同時に定義することができます。