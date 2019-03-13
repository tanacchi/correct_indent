#ifndef INCLUDED_NODE_HPP
#define INCLUDED_NODE_HPP

#include <vector>
#include "token.hpp"

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
}

#endif  // INCLUDED_NODE_HPP
