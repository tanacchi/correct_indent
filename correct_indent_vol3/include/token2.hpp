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
#include <iterator>
#include <type_traits>
#include <functional>
#include <boost/any.hpp>

struct Attribute {
  Attribute() noexcept = default;
  Attribute(const Attribute&) noexcept = default;
  Attribute& operator=(const Attribute&) noexcept = default;
  ~Attribute() noexcept = default;
};

struct Keyword : public Attribute {};
struct TypeKeyword : public Keyword {};
struct StatementKeyword : public Keyword {};
struct PreprocessorOperator : public Keyword {};
struct IncludePreprocessorOperator : public PreprocessorOperator {};
struct DefinePreprocessorOperator : public PreprocessorOperator {};

struct PreprocessorArgument : public Attribute {};

struct Identifier : public Attribute {};

struct Literal : public Attribute {};
struct CharLiteral : public Literal {};
struct StringLiteral : public Literal {};
struct NumberLiteral : public Literal {};
struct BinaryNumberLiteral : public NumberLiteral {};
struct OctalNumberLiteral : public NumberLiteral {};
struct DecimalNumberLiteral : public NumberLiteral {};
struct HexadecimalNumberLiteral : public NumberLiteral {};

struct Space : public Attribute {};

struct NewLine : public Attribute {};

struct Symbol : public Attribute {};
struct Equal : public Symbol {};
struct Semicolon : public Symbol {};
struct Comma : public Symbol {};
struct SingleQuote : public Symbol {};
struct DoubleQuote : public Symbol {};
struct LParen : public Symbol {};
struct RParen : public Symbol {};
struct LBrace : public Symbol {};
struct RBrace : public Symbol {};
struct LBracket : public Symbol {};
struct RBracket : public Symbol {};
struct Hash: public Symbol {};
struct Comment : public Symbol {};

struct Operator : public Symbol {};
struct AssignOperator : public Operator {};
struct RelationalOperator : public Operator {};
struct SubscriptOperator : public Operator {};
struct ArithmeticOperator : virtual public Operator {};
struct LogicalOperator : virtual public Operator {};
struct BitwiseOperator : virtual public Operator {};

struct UnaryOperator : virtual public Operator {};
struct BinaryOperator : virtual public Operator {};
struct CompoundOperator : virtual public  Operator {};

struct UnaryArithmeticOperator : public UnaryOperator, public ArithmeticOperator {};
struct BinaryArithmeticOperator : public BinaryOperator, public ArithmeticOperator {};
struct CompoundArithmeticOperator : public CompoundOperator, public ArithmeticOperator {};

struct UnaryLogicalOperator : public UnaryOperator, public LogicalOperator {};
struct BinaryLogicalOperator : public BinaryOperator, public LogicalOperator {};

struct UnaryBitwiseOperator : public UnaryOperator, public BitwiseOperator {};
struct BinaryBitwiseOperator : public BinaryOperator, public BitwiseOperator {};
struct CompoundBitwiseOperator : public CompoundOperator, public BitwiseOperator {};

struct TokenBase
{
  TokenBase(const std::string& content)
    : content{content}
  {
  }

  std::string content;
};

template <typename T>
struct Token : public TokenBase
{
  using attribute = T;
  
  Token(const std::string& content)
    : TokenBase(content)
  {
  }
};

struct AnyToken
{
  template <typename T>
  AnyToken(T&& attribute, const std::string& content)
  {
    token_ptr.reset(new Token<T>(content));
  }

  std::unique_ptr<TokenBase> token_ptr;
};

using TokenArray = std::vector<AnyToken>;

TokenArray parse(const std::vector<std::vector<std::string>>& string_matrix)
{
  TokenArray result;

  for (auto row : string_matrix)
  {
    for (auto str : row)
    {
      if (std::regex_match(str, std::regex("if|for")))
      {
        result.emplace_back(StatementKeyword{}, str);
      }
      else if (std::regex_match(str, std::regex("[0-9].*")))
      {
        result.emplace_back(AnyToken{NumberLiteral{}, str});
      }
      else if (std::regex_match(str, std::regex("\\w+")))
      {
        result.emplace_back(AnyToken{Identifier{}, str});
      }
      else if (std::regex_match(str, std::regex(" ")))
      {
        result.emplace_back(AnyToken{Space{}, str});
      }
      else if (std::regex_match(str, std::regex("\n")))
      {
        result.emplace_back(AnyToken{NewLine{}, str});
      }
      else if (std::regex_match(str, std::regex("=")))
      {
        result.emplace_back(AnyToken{Equal{}, str});
      }
      else if (std::regex_match(str, std::regex(";")))
      {
        result.emplace_back(AnyToken{Semicolon{}, str});
      }
      else if (std::regex_match(str, std::regex(",")))
      {
        result.emplace_back(AnyToken{Comma{}, str});
      }
      else if (std::regex_match(str, std::regex("#")))
      {
        result.emplace_back(AnyToken{Hash{}, str});
      }
      else if (std::regex_match(str, std::regex("'")))
      {
        result.emplace_back(AnyToken{SingleQuote{}, str});
      }
      else if (std::regex_match(str, std::regex("\"")))
      {
        result.emplace_back(AnyToken{DoubleQuote{}, str});
      }
      else if (std::regex_match(str, std::regex("\\(")))
      {
        result.emplace_back(AnyToken{LParen{}, str});
      }
      else if (std::regex_match(str, std::regex("\\)")))
      {
        result.emplace_back(AnyToken{RParen{}, str});
      }
      else if (std::regex_match(str, std::regex("\\{")))
      {
        result.emplace_back(AnyToken{LBrace{}, str});
      }
      else if (std::regex_match(str, std::regex("\\}")))
      {
        result.emplace_back(AnyToken{RBrace{}, str});
      }
      else if (std::regex_match(str, std::regex("\\[")))
      {
        result.emplace_back(AnyToken{LBracket{}, str});
      }
      else if (std::regex_match(str, std::regex("\\]")))
      {
        result.emplace_back(AnyToken{RBracket{}, str});
      }
      else
      {
        result.emplace_back(AnyToken{Symbol{}, str});
      }
    }
  }

  return result;
}

#endif  // INCLUDED_TOKEN_HPP
