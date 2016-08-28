#ifndef __CODE_PARSER_H_INCLUDE__
#define __CODE_PARSER_H_INCLUDE__

#include <istream>

class CodeParser {
public:
  CodeParser(std::vector<char>& delimiters, std::istream& is = std::cin);
  std::string* read();

private:
  const istream& is;
}

#endif
