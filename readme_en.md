# SCPP

SCPP (SCripting language in c Plus Plus) is an interpreter of simple programming language using AST (Abstract Syntax Tree) that runs on C++.

I developed this as a homework for "Special Lecture on Software and Computing Science A" (GB27001 in AY2022, 1 credit) at University of Tsukuba. The program is based on [minis](https://github.com/kmizu/minis), which was explained in class.

A brief introduction of usage is available in [the Web Doc](https://hirokoni.github.io/scpp/md_usage.html) (in Japanese).

## Features
It supports:
- Arithmetic operations
- mod expression
- Major comparison expressions(`==`, `!=`, `>`, `<`, `>=`, `<=`)
- Logical expressions(`AND`, `OR`, `NOR`, `XOR`, `NAND`, `NOT`)
- `if` expression
- `while` expression
- `for` expression
- Defining, assigning and referencing variables
- Sequence expression

You can also define function(s) and call them using function call expressions.

## Environment
Works on C++17.
