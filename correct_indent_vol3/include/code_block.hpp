#ifndef INCLUDED_CODE_BLOCK_HPP
#define INCLUDED_CODE_BLOCK_HPP

#include "token.hpp"
#include <iterator>

#define ATTR_RED   "\x1b[31m"
#define ATTR_GREEN "\x1b[32m"
#define ATTR_RESET "\x1b[0m"

struct CodeBlock
{
  enum class Kind
  {
    Paren, Brace,
  };

  CodeBlock(std::size_t start, std::size_t length, std::size_t level, std::string kind_str)
    : start{start},
      length{length},
      level{level},
      kind{kind_str == "LParen" ? Kind::Paren : Kind::Brace}
  {
    std::cout << "start : " << start << std::endl;
    std::cout << "length: " << length << std::endl;
    std::cout << "level : " << level << std::endl;
  }

  std::size_t start, length;
  std::size_t level;
  Kind        kind;
};

inline bool is_begin_symbol(std::string attr_name)
{
  return attr_name == "LParen" || attr_name == "LBrace";
}

inline bool is_end_symbol(std::string attr_name)
{
  return attr_name == "RParen" || attr_name == "RBrace";
}

token::TokenArray::iterator get_begin_itr(const token::TokenArray::iterator& end)
{
  std::string end_symbol{get_attr_name(end)};
  std::string begin_symbol{end_symbol == "RParen" ? "LParen" : "LBrace"};
  auto itr{end};
  for (; get_attr_name(itr) != begin_symbol; --itr) ;
  return itr;
}

using CodeBlockArray = std::vector<CodeBlock>;

CodeBlockArray gen_code_blocks(token::TokenArray tokens)
{
  CodeBlockArray result;
  std::size_t current_level{};
  for (auto itr{tokens.begin()}; itr != tokens.end(); ++itr)
  {
    if (is_end_symbol(get_attr_name(itr)))
    {
      auto end_itr{std::next(itr)};
      auto begin_itr{get_begin_itr(itr)};
      result.emplace_back(CodeBlock(std::distance(tokens.begin(), begin_itr), std::distance(begin_itr, end_itr),
                                    current_level, get_attr_name(begin_itr)));
      tokens.erase(begin_itr, end_itr);
      itr = std::prev(begin_itr);
      --current_level;
    }
    else if (is_begin_symbol(get_attr_name(itr)))
    {
      ++current_level;
    }
  }
  return result;
}

#endif  // INCLUDED_CODE_BLOCK_HPP
