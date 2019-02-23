#ifndef INCLUDED_TOKEN_HPP
#define INCLUDED_TOKEN_HPP

/*
 * C言語の BNF 記法にしたがうものとする
 * https://cs.wmich.edu/~gupta/teaching/cs4850/sumII06/The%20syntax%20of%20C%20in%20Backus-Naur%20form.htm
 * とりあえず簡易版
 * 参考文献：http://sikakuisankaku.hatenablog.com/entry/2017/12/19/234459
 */

#include <string>

struct Token
{
    enum class Attribute
    {
      TermOperator,
      FactorOpearator,
      CompareOperator,
      Equal,
      Comma,
      SemiColon,
      LParen,   RParen,
      LBracket, RBracket,
      IfKeyword,
      ElseKeyWord,
      WhileKeyword,
      ReturnKeyword,
      TypeKeyword,
      Itentify,
      Number,
      CharAlphabet,
      CharNumber,
      Unknown
    };
   Token(Attribute attribute = Attribute::Unknown, std::string string = {})
     : attribute{attribute}, string{string}
   {
   }

   Attribute attribute;
   std::string content;
};

#endif  // INCLUDED_TOKEN_HPP
