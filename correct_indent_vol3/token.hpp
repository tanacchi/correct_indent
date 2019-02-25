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
#include <cassert>
#include <type_traits>

struct Attribute {
  Attribute(std::string name = "Attribute")
    : name{name}
  {}

  Attribute(Attribute&& attribute)
    : name{attribute.name}
  {}

  const std::string name{};
};

struct Keyword : public Attribute {
  Keyword(std::string name = "Keyword")
    : Attribute(name)
  {}
};
struct TypeKeyword : public Keyword {
  TypeKeyword(std::string name = "TypeKeyword")
    : Keyword(name)
  {}
};
struct StatementKeyword : public Keyword {
  StatementKeyword(std::string name = "StatementKeyword")
    : Keyword(name)
  {}
};

struct Identifier : public Attribute {
  Identifier(std::string name = "Identifier")
    : Attribute(name)
  {}
};

struct Literal : public Attribute {
  Literal(std::string name = "Literal")
    : Attribute(name)
  {}
};
struct CharLiteral : public Literal {
  CharLiteral(std::string name = "CharLiteral")
    : Literal(name)
  {}
};
struct StringLiteral : public Literal {
  StringLiteral(std::string name = "StringLiteral")
    : Literal(name)
  {}
};
struct NumberLiteral : public Literal {
  NumberLiteral(std::string name = "NumberLiteral")
    : Literal(name)
  {}
};
struct BinaryNumberLiteral : public NumberLiteral {
  BinaryNumberLiteral(std::string name = "BinaryNumberLiteral")
    : NumberLiteral(name)
  {}
};
struct OctalNumberLiteral : public NumberLiteral {
  OctalNumberLiteral(std::string name = "OctalNumberLiteral")
    : NumberLiteral(name)
  {}
};
struct DecimalNumberLiteral : public NumberLiteral {
  DecimalNumberLiteral(std::string name = "DecimalNumberLiteral")
    : NumberLiteral(name)
  {}
};
struct HexadecimalNumberLiteral : public NumberLiteral {
  HexadecimalNumberLiteral(std::string name = "HexadecimalNumberLiteral")
    : NumberLiteral(name)
  {}
};

struct Space : public Attribute {
  Space(std::string name = "Space")
    : Attribute(name)
  {}
};

struct Symbol : public Attribute {
  Symbol(std::string name = "Symbol")
    : Attribute(name)
  {}
};
struct Assign : public Symbol {
  Assign(std::string name = "Assign")
    : Symbol(name)
  {}
};
struct Semicolon : public Symbol {
  Semicolon(std::string name = "Semicolon")
    : Symbol(name)
  {}
};
struct Comma : public Symbol {
  Comma(std::string name = "Comma")
    : Symbol(name)
  {}
};
struct LParen : public Symbol {
  LParen(std::string name = "LParen")
    : Symbol(name)
  {}
};
struct RParen : public Symbol {
  RParen(std::string name = "RParen")
    : Symbol(name)
  {}
};
struct LBrace : public Symbol {
  LBrace(std::string name = "LBrac")
    : Symbol(name)
  {}
};
struct RBrace : public Symbol {
  RBrace(std::string name = "RBrace")
    : Symbol(name)
  {}
};
struct LBracket : public Symbol {
  LBracket(std::string name = "LBracket")
    : Symbol(name)
  {}
};
struct RBracket : public Symbol {
  RBracket(std::string name = "RBracket")
    : Symbol(name)
  {}
};
struct Comment : public Symbol {
  Comment(std::string name = "Comment")
    : Symbol(name)
  {}
};

struct Operator : public Symbol {
  Operator(std::string name = "Operator")
    : Symbol(name)
  {}
};
struct RelationalOperator : public Operator {
  RelationalOperator(std::string name = "RelationalOperator")
    : Operator(name)
  {}
};
struct SubscriptOperator : public Operator {
  SubscriptOperator(std::string name = "SubscriptOperator")
    : Operator(name)
  {}
};
struct ArithmeticOperator : virtual public Operator {
  ArithmeticOperator(std::string name = "ArithmeticOperator")
    : Operator(name)
  {}
};
struct LogicalOperator : virtual public Operator {
  LogicalOperator(std::string name = "LogicalOperator")
    : Operator(name)
  {}
};
struct BitwiseOperator : virtual public Operator {
  BitwiseOperator(std::string name = "BitwiseOperator")
    : Operator(name)
  {}
};

struct UnaryOperator : virtual public Operator {
  UnaryOperator(std::string name = "UnaryOperator")
    : Operator(name)
  {}
};
struct BinaryOperator : virtual public Operator {
  BinaryOperator(std::string name = "BinaryOperator")
    : Operator(name)
  {}
};
struct CompoundOperator : virtual public  Operator {
  CompoundOperator(std::string name = "CompoundOperator")
    : Operator(name)
  {}
};

struct UnaryArithmeticOperator : public UnaryOperator, public ArithmeticOperator {
  UnaryArithmeticOperator(std::string name = "UnaryArithmeticOperator")
    : ArithmeticOperator(name)
  {}
};
struct BinaryArithmeticOperator : public BinaryOperator, public ArithmeticOperator {
  BinaryArithmeticOperator(std::string name = "BinaryArithmeticOperator")
    : ArithmeticOperator(name)
  {}
};
struct CompoundArithmeticOperator : public CompoundOperator, public ArithmeticOperator {
  CompoundArithmeticOperator(std::string name = "CompoundArithmeticOperator")
    : ArithmeticOperator(name)
  {}
};

struct UnaryLogicalOperator : public UnaryOperator, public LogicalOperator {
  UnaryLogicalOperator(std::string name = "UnaryLogicalOperator")
    : LogicalOperator(name)
  {}
};
struct BinaryLogicalOperator : public BinaryOperator, public LogicalOperator {
  BinaryLogicalOperator(std::string name = "BinaryLogicalOperator")
    : LogicalOperator(name)
  {}
};

struct UnaryBitwiseOperator : public UnaryOperator, public BitwiseOperator {
  UnaryBitwiseOperator(std::string name = "UnaryBitwiseOperator")
    : BitwiseOperator(name)
  {}
};
struct BinaryBitwiseOperator : public BinaryOperator, public BitwiseOperator {
  BinaryBitwiseOperator(std::string name = "BinaryBitwiseOperator")
    : BitwiseOperator(name)
  {}
};
struct CompoundBitwiseOperator : public CompoundOperator, public BitwiseOperator {
  CompoundBitwiseOperator(std::string name = "CompoundBitwiseOperator")
    : BitwiseOperator(name)
  {}
};

struct Token
{
  Token()
    : attribute{},
      content{}
  {
  }

  Token(Token&& token)
    : attribute{std::move(token.attribute)},
      content{token.content}
  {
  }

  std::unique_ptr<Attribute> attribute;
  std::string                content;
};

template <typename T>
Token make_token(std::string content)
{
  Token token;
  token.attribute = std::make_unique<T>();
  token.content = content;
  return token;
}


std::vector<Token> parse(const std::vector<std::vector<std::string>>& string_matrix)
{
  std::vector<Token> result;
  for (auto row : string_matrix)
  {
    for (auto str : row)
    {
      if (std::regex_match(str, std::regex("if|for")))
      {
        result.emplace_back(make_token<StatementKeyword>(str));
      }
      else if (std::regex_match(str, std::regex("[0-9].*")))
      {
        result.emplace_back(make_token<NumberLiteral>(str));
      }
      else if (std::regex_match(str, std::regex("\\w+")))
      {
        result.emplace_back(make_token<Identifier>(str));
      }
      else
      {
        result.emplace_back(make_token<Symbol>(str));
      }
    }
  }
  return result;
}

#endif  // INCLUDED_TOKEN_HPP
