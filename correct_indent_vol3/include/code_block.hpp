#ifndef INCLUDED_CODE_BLOCK_HPP
#define INCLUDED_CODE_BLOCK_HPP

#include "token.hpp"
#include <iterator>

#define ATTR_RED   "\x1b[31m"
#define ATTR_RESET "\x1b[0m"

struct CodeBlock
{
  enum class Kind
  {
    Paren, Brace,
  };

  static std::size_t current_level;

  CodeBlock(const token::TokenArray::iterator& tokens_begin, 
            const token::TokenArray::iterator& tokens_end,
            Kind kind)
    : level{current_level},
      tokens{std::make_move_iterator(tokens_begin), std::make_move_iterator(tokens_end)},
      kind{kind}
  {
  }

  std::size_t level;
  token::TokenArray  tokens;
  Kind        kind;
};

std::size_t CodeBlock::current_level{0};

inline bool is_begin_symbol(std::string attr_name)
{
  return attr_name == "LParen" || attr_name == "LBrace";
}

inline bool is_end_symbol(std::string attr_name)
{
  return attr_name == "RParen" || attr_name == "RBrace";
}

using CodeBlockArray = std::vector<CodeBlock>;

token::TokenArray::iterator get_begin(const token::TokenArray::iterator& end)
{
  std::string end_symbol{get_attr_name(end)};
  std::string begin_symbol{end_symbol == "RParen" ? "LParen" : "LBrace"};
  auto itr{end};
  for (; get_attr_name(itr) != begin_symbol; --itr) ;
  return itr;
}

void gen_code_blocks(token::TokenArray&& tokens)
{
  for (auto itr{tokens.begin()}, end{tokens.end()}; itr != end; ++itr)
  {
    if (is_begin_symbol(get_attr_name(itr)))
    {
      ++CodeBlock::current_level;
    }
    else if (is_end_symbol(get_attr_name(itr)))
    {
      auto end_itr{itr};
      auto begin_itr{get_begin(itr)};
      for (; begin_itr != end_itr; ++begin_itr)
      {
        std::cout << ATTR_RED << get_content(begin_itr);
      }
      std::cout << get_content(itr) << ATTR_RESET  << " [level : " << CodeBlock::current_level << " ]" << std::endl;
      --CodeBlock::current_level;
      tokens.erase(begin_itr, end_itr);
    }
    else 
    {
      std::cout << get_content(itr) << std::endl;
    }
  }
}

#endif  // INCLUDED_CODE_BLOCK_HPP
