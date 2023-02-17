# SCPP

- [GitHub リポジトリ](https://github.com/HiroKoni/scpp)
- [Webドキュメント](https://hirokoni.github.io/scpp/)

SCPP(SCripting language in c Plus Plus) は、C++で動作する、抽象構文木を用いた簡単なプログラミング言語のインタプリタです。

このプログラムは、2022年度筑波大学GB27001「ソフトウェアサイエンス特別講義A」の提出課題です。同授業内で解説された、[minis](https://github.com/kmizu/minis)を参考にして作成されています。

使用方法の解説は、[SCPPの使い方](https://hirokoni.github.io/scpp/md_usage.html)をご覧ください。

## 機能
整数型を用いた、
- 四則演算
- mod式
- 主要な比較式(`==`, `!=`, `>`, `<`, `>=`, `<=`)
- 論理演算式(`AND`, `OR`, `NOR`, `XOR`, `NAND`, `NOT`)
- `if`式
- `while`式
- `for`式
- 変数の定義・代入・参照
- 連接式

をサポートします。関数定義を行い、関数呼び出し式を用いて呼び出すこともできます。

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
- 真偽を評価する際、ゼロは偽、非ゼロは真として扱われます。
- `While`式及び`For`式において、条件式が満たされることがない場合、その式は0と評価されます。
- 変数と関数は、別の環境で管理されるため、同名の変数と関数を同時に定義することができます。
- プログラム`SProgram`内で定義された変数のスコープは、そのプログラム全体です。それ以外の変数は、全てグローバル変数です。
    - プログラム内では、グローバル変数を参照することはできません