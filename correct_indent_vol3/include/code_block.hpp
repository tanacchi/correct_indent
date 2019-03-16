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

using CodeBlockArray = std::vector<CodeBlock>;

void gen_code_blocks(token::TokenArray&& tokens)
{
  std::size_t current_level{};
  for (auto itr{tokens.begin()}, end{tokens.end()}; itr != end; ++itr)
  {
  }
}

#endif  // INCLUDED_CODE_BLOCK_HPP
