#ifndef INCLUDED_NODE_HPP
#define INCLUDED_NODE_HPP

#include <algorithm>
#include <cassert>
#include <vector>
#include <deque>
#include <utility>

#include "token.hpp"
#include "code_block.hpp"

namespace node
{
  struct Node
  {
    enum class Attribute
    {
      ParenBlock,
      BraceBlock,
      FunctionPrototype,
      FunctionDefine,
      FunctionCall,
      VariableDeclaration,
      VariableDefine,
      Unknown
    };

    Node()
      : attribute{Attribute::Unknown},
        tokens{},
        sub_ptr{}
    {
    }

    Node(Attribute attribute, const token::TokenArray::iterator& begin, const token::TokenArray::iterator& end)
      : attribute{attribute},
        tokens{begin, end},
        sub_ptr{}
    {
    }

    Attribute attribute;
    token::TokenArray tokens;
    std::shared_ptr<Node> sub_ptr;
  };

  token::TokenArray::iterator get_paren_block_begin(token::TokenArray::iterator end_itr)
  {
    assert(get_attr_name(end_itr) == "RParen");
    auto itr{end_itr};
    for (; get_attr_name(itr) != "LParen"; --itr) ;
    return itr;
  }
  
  void node_test(const token::TokenArray& tokens, const CodeBlockArray& blocks)
  {
    std::deque<token::AnyToken> deque;
    for (auto block : blocks)
    {
      std::cout << block.start << " " << block.length << std::endl;
      std::cout << ATTR_RED;
      for (std::size_t i{}; i < block.length; ++i)
      {
        std::cout << tokens[block.start + i].token_ptr->content;
      }
      std::cout << ATTR_RESET << std::endl;
    }
  }
}

#endif  // INCLUDED_NODE_HPP
