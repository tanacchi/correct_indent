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

  CodeBlock(const token::TokenArray::iterator& tokens_begin, 
            const token::TokenArray::iterator& tokens_end,
            std::size_t level)
    : begin{tokens_begin}, end{tokens_end},
      level{level},
      kind{get_attr_name(begin) == "LParen" ? Kind::Paren : Kind::Brace}
  {
  }

  friend std::ostream& operator<<(std::ostream& os, const CodeBlock& code_block)
  {
    for (auto itr{code_block.begin}; itr != code_block.end; ++itr)
    {
      os << ATTR_RED << itr->token_ptr->content;
    }
    os << ATTR_RESET << " [ level : " << code_block.level << " ]"
                     << " kind : " << (code_block.kind == CodeBlock::Kind::Paren ? "Paren" : "Brace") << std::endl;
    return os;
  }

  token::TokenArray::iterator begin, end;
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

CodeBlockArray gen_code_blocks(token::TokenArray&& tokens)
{
  CodeBlockArray result;
  std::size_t current_level{};
  for (auto itr{tokens.begin()}; itr != tokens.end(); ++itr)
  {
    if (is_end_symbol(get_attr_name(itr)))
    {
      auto end_itr{std::next(itr)};
      auto begin_itr{get_begin_itr(itr)};
      CodeBlock block{begin_itr, end_itr, current_level};
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
