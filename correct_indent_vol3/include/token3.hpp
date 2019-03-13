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
#include <map>
#include <functional>

struct Attribute {
  Attribute(std::string name = "Attribute") noexcept
    : name{name}
  {
  }
  Attribute(const Attribute& attribute) noexcept
    : name{attribute.name}
  {
  }
  Attribute(Attribute&& attribute) noexcept
    : name{std::move(attribute.name)}
  {
  }
  Attribute& operator=(const Attribute&) noexcept = default;
  ~Attribute() noexcept = default;

  std::string name{};
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
struct PreprocessorOperator : public Keyword {
  PreprocessorOperator(std::string name = "PreprocessorOperator")
    : Keyword(name)
  {}
};
struct IncludePreprocessorOperator : public PreprocessorOperator {
  IncludePreprocessorOperator(std::string name = "IncludePreprocessorOperator")
    : PreprocessorOperator(name)
  {}
};
struct DefinePreprocessorOperator : public PreprocessorOperator {
  DefinePreprocessorOperator(std::string name = "DefinePreprocessorOperator")
    : PreprocessorOperator(name)
  {}
};

struct PreprocessorArgument : public Attribute {
  PreprocessorArgument(std::string name = "PreprocessorArgument")
    : Attribute(name)
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

struct NewLine : public Attribute {
  NewLine(std::string name = "NewLine")
    : Attribute(name)
  {}
};

struct Symbol : public Attribute {
  Symbol(std::string name = "Symbol")
    : Attribute(name)
  {}
};
struct Equal : public Symbol {
  Equal(std::string name = "Equal")
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
struct SingleQuote : public Symbol {
  SingleQuote(std::string name = "SingleQuote")
    : Symbol(name)
  {}
};
struct DoubleQuote : public Symbol {
  DoubleQuote(std::string name = "DoubleQuote")
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
  LBrace(std::string name = "LBrace")
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
struct Hash: public Symbol {
  Hash(std::string name = "Hash")
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
struct AssignOperator : public Operator {
  AssignOperator(std::string name = "AssignOperator")
    : Operator(name)
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

struct TokenBase
{
  TokenBase(std::unique_ptr<Attribute>&& attribute_ptr,
            const std::string& content)
    : attribute_ptr{std::move(attribute_ptr)},
      content{content}
  {
  }

  std::unique_ptr<Attribute> attribute_ptr;
  std::string content;
};

template <typename T>
struct Token : public TokenBase
{
  using attribute = T;
  
  Token(const std::string& content)
    : TokenBase(std::make_unique<T>(), content)
  {
  }

  Token(T&& attribute, const std::string& content)
    : TokenBase(std::make_unique<T>(attribute), content)
  {
  }
};

struct AnyToken
{
  template <typename T>
  AnyToken(T&& attribute, const std::string& content)
  {
    token_ptr.reset(new Token<T>(attribute.name, content));
  }

  std::unique_ptr<TokenBase> token_ptr;
};

// ハッシュコードからインスタンスを作る
// テーブル的なものを作るしか無いみたい
AnyToken duplicate(TokenBase& token)
{
  static const std::map<std::string, std::function<Attribute(void)>> name_token_table {{
    {"Attribute",                   [](){ return Attribute(); }},
    {"Keyword",                     [](){ return Keyword(); }  },
    {"TypeKeyword",                 [](){ return TypeKeyword(); }  },
    {"StatementKeyword",            [](){ return StatementKeyword(); }  },
    {"PreprocessorOperator",        [](){ return PreprocessorOperator(); }  },
    {"IncludePreprocessorOperator", [](){ return IncludePreprocessorOperator(); }  },
    {"DefinePreprocessorOperator",  [](){ return DefinePreprocessorOperator(); }  },
    {"PreprocessorArgument",        [](){ return PreprocessorArgument(); }  },
    {"Identifier",                  [](){ return Identifier(); }  },
    {"Literal",                     [](){ return Literal(); }  },
    {"CharLiteral",                 [](){ return CharLiteral(); }  },
    {"StringLiteral",               [](){ return StringLiteral(); }  },
    {"NumberLiteral",               [](){ return NumberLiteral(); }  },
    {"BinaryNumberLiteral",         [](){ return BinaryNumberLiteral(); }  },
    {"OctalNumberLiteral",          [](){ return OctalNumberLiteral(); }  },
    {"DecimalNumberLiteral",        [](){ return DecimalNumberLiteral(); }  },
    {"HexadecimalNumberLiteral",    [](){ return HexadecimalNumberLiteral(); }  },
    {"Space",                       [](){ return Space(); }  },
    {"NewLine",                     [](){ return NewLine(); }  },
    {"Symbol",                      [](){ return Symbol(); }  },
    {"Equal",                       [](){ return Equal(); }  },
    {"Semicolon",                   [](){ return Semicolon(); }  },
    {"Comma",                       [](){ return Comma(); }  },
    {"SingleQuote",                 [](){ return SingleQuote(); }  },
    {"DoubleQuote",                 [](){ return DoubleQuote(); }  },
    {"LParen",                      [](){ return LParen(); }  },
    {"RParen",                      [](){ return RParen(); }  },
    {"LBrace",                      [](){ return LBrace(); }  },
    {"RBrace",                      [](){ return RBrace(); }  },
    {"LBracket",                    [](){ return LBracket(); }  },
    {"RBracket",                    [](){ return RBracket(); }  },
    {"Hash",                        [](){ return Hash(); }  },
    {"Comment"                  ,   [](){ return Comment(); }  },
    {"Operator",                    [](){ return Operator(); }  },
    {"AssignOperator",              [](){ return AssignOperator(); }  },
    {"RelationalOperator",          [](){ return RelationalOperator(); }  },
    {"SubscriptOperator",           [](){ return SubscriptOperator(); }  },
    {"ArithmeticOperator",          [](){ return ArithmeticOperator(); }  },
    {"LogicalOperator",             [](){ return LogicalOperator(); }  },
    {"BitwiseOperator",             [](){ return BitwiseOperator(); }  },
    {"UnaryOperator",               [](){ return UnaryOperator(); }  },
    {"BinaryOperator",              [](){ return BinaryOperator(); }  },
    {"CompoundOperator",            [](){ return CompoundOperator(); }  },
    {"UnaryArithmeticOperator",     [](){ return UnaryArithmeticOperator(); }  },
    {"BinaryArithmeticOperator",    [](){ return BinaryArithmeticOperator(); }  },
    {"CompoundArithmeticOperator",  [](){ return CompoundArithmeticOperator(); }  },
    {"UnaryLogicalOperator",        [](){ return UnaryLogicalOperator(); }  },
    {"BinaryLogicalOperator",       [](){ return BinaryLogicalOperator(); }  },
    {"UnaryBitwiseOperator",        [](){ return UnaryBitwiseOperator(); }  },
    {"BinaryBitwiseOperator",       [](){ return BinaryBitwiseOperator(); }  },
    {"CompoundBitwiseOperator",     [](){ return CompoundBitwiseOperator(); }  },
  }};

  auto found_attribute_generator{name_token_table.at(token.attribute_ptr->name)};
  std::cout << "!!!" << found_attribute_generator().name << std::endl;
  return AnyToken{found_attribute_generator(), token.content};
}


using TokenArray = std::vector<AnyToken>;

TokenArray parse1(const std::vector<std::vector<std::string>>& string_matrix)
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

TokenArray parse2(TokenArray tokens)
{
  TokenArray result;

  auto itr{tokens.begin()};

  auto get_content  {[&](){ return itr->token_ptr->content; }};
  auto get_attr_name{[&](){ return itr->token_ptr->attribute_ptr->name; }};

  for (const auto& end{tokens.end()}; itr != end; ++itr)
  {
    if (get_attr_name() == "Hash")
    {
      ++itr;
      std::string kind{get_content()};
      result.emplace_back(AnyToken{PreprocessorOperator{}, "#" + kind});
      
      for (++itr; get_attr_name() != "NewLine"; ++itr)
      {
        if (get_attr_name() == "Space")
        {
          result.emplace_back(AnyToken{Space{}, " "});
        }
        else 
        {
          result.emplace_back(PreprocessorArgument{}, get_content());
        }
      }
    }
    else if (get_attr_name() == "SingleQuote")
    {
      std::string content{get_content()};
      for (++itr; get_attr_name() != "SingleQuote"; ++itr)
      {
        content += get_content();
      }
      result.emplace_back(CharLiteral{}, content + "'");
    }
    else if (get_attr_name() == "DoubleQuote")
    {
      std::string content{get_content()};
      for (++itr; get_attr_name() != "DoubleQuote"; ++itr)
      {
        content += get_content();
      }
      result.emplace_back(StringLiteral{}, content + "\"");
    }
    else
    {
      result.emplace_back(duplicate(*itr->token_ptr));
    }
  }
  return result;
}

#endif  // INCLUDED_TOKEN_HPP
