#ifndef INCLUDED_TOKEN_HPP
#define INCLUDED_TOKEN_HPP

/*
 * C言語の BNF 記法にしたがうものとする
 * https://cs.wmich.edu/~gupta/teaching/cs4850/sumII06/The%20syntax%20of%20C%20in%20Backus-Naur%20form.htm
 * とりあえず簡易版
 * 参考文献：http://sikakuisankaku.hatenablog.com/entry/2017/12/19/234459
 */

#include <string>
#include <vector>
#include <regex>
#include <memory>

struct Attribute {};

struct Keyword :          private Attribute {};
struct TypeKeyword :      private Keyword {};
struct StatementKeyword : private Keyword {};

struct Identifier :       private Attribute {};

struct Literal :                  private Attribute {};
struct CharLiteral :              private Literal {};
struct StringLiteral :            private Literal {};
struct NumberLiteral :            private Literal {};
struct BinaryNumberLiteral :      private NumberLiteral {};
struct OctalNumberLiteral :       private NumberLiteral {};
struct DecimalNumberLiteral :     private NumberLiteral {};
struct HexadecimalNumberLiteral : private NumberLiteral {};

struct Space : private Attribute {};

struct Simbol :    private Attribute {};
struct Assign :    private Simbol {};
struct Semicolon : private Simbol {};
struct Comma :     private Simbol {};
struct LParen :    private Simbol {};
struct RParen :    private Simbol {};
struct LBrace:     private Simbol {};
struct RBrace:     private Simbol {};
struct LBracket :  private Simbol {};
struct RBracket :  private Simbol {};
struct Comment:    private Simbol {};

struct Operator :           private Simbol {};
struct RelationalOperator : private Operator {};
struct SubscriptOperator :  private Operator {};
struct ArithmeticOperator : virtual private Operator {};
struct LogicalOperator :    virtual private Operator {};
struct BitwiseOperator :    virtual private Operator {};

struct UnaryOperator :   virtual private  Operator {};
struct BinaryOperator :  virtual private  Operator {};
struct CompoundOperator: virtual private  Operator {};

struct UnaryArithmeticOperator :    private UnaryOperator,    private ArithmeticOperator {};
struct BinaryArithmeticOperator :   private BinaryOperator,   private ArithmeticOperator {};
struct CompoundArithmeticOperator : private CompoundOperator, private ArithmeticOperator {};

struct UnaryLogicalOperator :    private UnaryOperator,    private LogicalOperator {};
struct BinaryLogicalOperator :   private BinaryOperator,   private LogicalOperator {};

struct UnaryBitwiseOperator :   private UnaryOperator,    private BitwiseOperator {};
struct BinaryBitwiseOperator :  private BinaryOperator,   private BitwiseOperator {};
struct CompoundBitwiseOperator: private CompoundOperator, private BitwiseOperator {};

struct Token
{
  std::unique_ptr<Attribute> attribute;
  std::string                content;
};

#endif  // INCLUDED_TOKEN_HPP
