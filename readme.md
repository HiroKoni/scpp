# SCPP
SCPP(SCripting language in c Plus Plus) は、C++で動作する、抽象構文木を用いた簡単なプログラミング言語のインタプリタです。

このプログラムは、筑波大学2022年度GB27001「ソフトウェアサイエンス特別講義A」の提出課題です。


## 仕様
0除算は未定義動作です。
除算において、小数点以下は切り捨てられます。
宣言されていない変数を参照しようとした場合、その変数が宣言され、0で初期化されます。