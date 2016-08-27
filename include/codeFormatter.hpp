#ifndef __CODE_FORMATTER_H_INCLUDE__
#define __CODE_FORMATTER_H_INCLUDE__

#include <string>

struct Section {
  int delimiterIndex;
  std::string frontCode;
};

struct DelimiterInfo {
  char delimiter;
  std::string normalFormat;
  std::string onlyDelimFormat;
  void (*taskFunc)(Section*, std::string&);
};

void inputCode(std::string& code);
void formatCode(std::string& code);
void indentCode(std::string& code);
Section* getInputOneSection();
bool remake(Section* section, std::string& result);
int findDelimiter(const char input);
void addIndentRow(int indentDepth, std::size_t workPoint, std::string& code);
int getDiffIndent(const std::string& code, const std::size_t start, const std::size_t end);
void taskNormal(Section* section, std::string& result);
void taskSpace(Section* section, std::string& result);

#endif
