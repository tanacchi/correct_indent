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
            std::size_t level, std::string kind_str)
    : begin{tokens_begin}, end{tokens_end},
      level{level},
      kind{kind_str == "Paren" ? Kind::Paren : Kind::Brace}
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

void gen_code_blocks(token::TokenArray&& tokens)
{
  std::size_t current_level{};
  for (auto itr{tokens.begin()}; itr != tokens.end(); ++itr)
  {
    std::cout << std::distance(itr, tokens.end()) << " ";
    // std::cout << get_content(itr);
    for (auto it{tokens.begin()}; it != tokens.end(); ++it)
    {
      if (it == itr)
      {
        std::cout << ATTR_GREEN << get_content(it) << ATTR_RESET;
      }
      else
      {
        std::cout << get_content(it);
      }
    }
    std::cout << std::endl;
    if (is_end_symbol(get_attr_name(itr)))
    {

      auto end_itr{std::next(itr)};
      auto begin_itr{get_begin_itr(itr)};

      for (auto it{begin_itr}; it != end_itr; ++it)
      {
        std::cout << ATTR_RED << get_content(it);
      }
      std::cout << ATTR_RESET << "level : " << current_level << std::endl;

      tokens.erase(begin_itr, end_itr);
      
      itr = std::prev(begin_itr);

      --current_level;
    }
    else if (is_begin_symbol(get_attr_name(itr)))
    {
      ++current_level;
    }
    else
    {
    }
    std::cout << std::endl;
  }

}

#endif  // INCLUDED_CODE_BLOCK_HPP
