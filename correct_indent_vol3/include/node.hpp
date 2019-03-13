#ifndef INCLUDED_NODE_HPP
#define INCLUDED_NODE_HPP

#include <vector>
#include "token.hpp"

struct Node
{
  enum class Attribute
  {
    Unknown
  };

  Attribute attribute;
  token::TokenArray tokens;
};

#endif  // INCLUDED_NODE_HPP
