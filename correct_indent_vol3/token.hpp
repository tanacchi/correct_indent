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

struct Token
{
    enum class Attribute
    {
      TermOperator,         // + | -
      FactorOpearator,      // * | / | %
      CompareOperator,      // == | != | > | >= | < | <= 
      Equal,                // =
      Comma,                // ,
      SemiColon,            // ;
      LParen,   RParen,     // ( , )
      LBrace,   RBrace,     // { , }
      LBracket, RBracket,   // [ , ]
      IfKeyword,            // if
      ElseKeyWord,          // else
      WhileKeyword,         // while
      ReturnKeyword,        // return
      TypeKeyword,          // int
      Identify              // CharAlphabet(CharAlphabet|CharNumber)*
      Number,               // CharNumber(CharNumber)*
      CharAlphabet,         // [a-zA-Z_]
      CharNumber,           // [0-9]
      Space,                // ' '
      NewLine,              // '\n'
      Unknown
    };
   Token(Attribute attribute = Attribute::Unknown, std::string string = {})
     : attribute{attribute}, content{string}
   {
   }

   Attribute attribute;
   std::string content;
};

std::vector<Token> parse_level_1(std::vector<std::vector<std::string>> tokens)
{
  std::vector<Token> result;
  for (const auto& row : tokens)
  {
    for (const auto& str : row)
    {
      Token token{};
      std::cout << str << "\t";
      if (std::regex_match(str, std::regex("[a-zA-Z_].*")))
      {
        std::cout << "<- Identify" << std::endl;
        token.attribute = Token::Attribute::Identify;
      }
      else if (std::regex_match(str, std::regex("\\d.*")))
      {
        std::cout << "<- Number" << std::endl;
        token.attribute = Token::Attribute::Number;
      }
      else if (str == "(")
      {
        std::cout << "<- LParen" << std::endl;
        token.attribute = Token::Attribute::LParen;
      }
      else if (str == ")")
      {
        std::cout << "<- RParen" << std::endl;
        token.attribute = Token::Attribute::RParen;
      }
      else if (str == "{")
      {
        std::cout << "<- LBrace" << std::endl;
        token.attribute = Token::Attribute::LBrace;
      }
      else if (str == "}")
      {
        std::cout << "<- RBrace" << std::endl;
        token.attribute = Token::Attribute::RBrace;
      }
      else
      {
        std::cout << "<- Other" << std::endl;
      }
      token.content = str;
      result.emplace_back(token);
    }
  }
  return result;
}

#endif  // INCLUDED_TOKEN_HPP
