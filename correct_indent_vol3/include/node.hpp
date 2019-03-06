#ifndef INCLUDED_NODE_HPP
#define INCLUDED_NODE_HPP

#include <vector>
#include "token.hpp"

struct Node
{
  enum class Attribute
  {
    Program,
    FDec,
    Prototype,
    VDec,
    Function,
    Sentence,
    IfStatement,
    ForStatement,
    Return,
    Assign,
    Call,
    Arguments,
    Expression,
    Formura,
    Term,
    Factor,
    BOpearator,
    Variable,
    Type,
    Unknown
  };

  Node(Attribute attribute = Unknown, std::vector<Token> tokens)
    : attribute{attribute}, tokens{tokens}
  {
  }

  Attribute attribute;
  std::vector<Token> tokens;
};

#endif  // INCLUDED_NODE_HPP
