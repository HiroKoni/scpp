# SCPP
SCPP(SCripting language in c Plus Plus) は、C++で動作する、抽象構文木を用いた簡単なプログラミング言語のインタプリタです。

このプログラムは、筑波大学2022年度GB27001「ソフトウェアサイエンス特別講義A」の提出課題です。

## 環境
C++17で動作します。

付属するテストは、Google Testを用いたものです。
`CMakeList.txt`を用いて、バージョン3.14以降のCmakeによりビルドすることで、テスト環境を容易に準備することができます。
（[参考リンク](https://google.github.io/googletest/quickstart-cmake.html#create-and-run-a-binary)）

### 開発に用いた環境
- Ubuntu 20.04.5 LTS on WSL2
- CMake 3.16.3
- g++ 9.4.0

## 仕様
- 実行環境におけるC++の`int`型の範囲で動作します。
- 0除算は未定義動作です。
- 除算において、小数点以下は切り捨てられます。
- 宣言されていない変数を参照しようとした場合、その変数が宣言され、0で初期化されます。