#ifndef INCLUDED_NODE_HPP
#define INCLUDED_NODE_HPP

#include <cassert>
#include <vector>

#include "token.hpp"

#define ATTR_RED   "\x1b[31m"
#define ATTR_RESET "\x1b[0m"

namespace node
{
  struct Node
  {
    enum class Attribute
    {
      FunctionPrototype,
      FunctionDefine,
      FunctionCall,
      VariableDeclaration,
      VariableDefine,
      Unknown
    };

    Attribute attribute;
    token::TokenArray tokens;
  };

  token::TokenArray::iterator get_paren_block_begin(token::TokenArray::iterator end_itr)
  {
    assert(get_attr_name(end_itr) == "RParen");
    auto itr{end_itr};
    for (; get_attr_name(itr) != "LParen"; --itr) ;
    return itr;
  }
  
  void node_test(token::TokenArray tokens)
  {
    for (auto itr{tokens.begin()}, end{tokens.end()}; itr != end; ++itr)
    {
      if (get_attr_name(itr) == "RParen")
      {
        auto paren_itr{get_paren_block_begin(itr)};
        for (; paren_itr != itr; ++paren_itr)
        {
          std::cout << ATTR_RED << get_content(paren_itr);
        }
        std::cout << get_content(itr) << ATTR_RESET << std::endl;
        continue;
      }
      else
      {
        std::cout << get_content(itr) << std::endl;
      }
    }
  }
}

#endif  // INCLUDED_NODE_HPP
