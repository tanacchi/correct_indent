#include "code_formatter.hpp"

#include <iostream>
#include <algorithm>
#include <cstdio>

const int INDENT_WIDTH = 2;
const DelimiterInfo delimiters[] = {
    {' ', "", "", taskSpace},
    {'\n', "", "", taskSpace},
    {',', ", ", ", ", taskNormal},
    {';', ";\n", ";\n", taskNormal},
    {'(', "(", "(", taskNormal},
    {')', ")", ")", taskNormal},
    {'{', "{\n", "{\n", taskNormal},
    {'}', "}\n", "}\n", taskNormal},
    {'[', "[", "[", taskNormal},
    {']', "]", "]", taskNormal},
    {'\0', "", "", NULL}
};
const StatementInfo statements[] {
    {"for", taskStateFor},
    {"#include", taskStateInclude},
    {"#define", taskStateDefine},
    {"", taskNoState},
    {"", NULL}
};

int main(int argc, char* argv[]) {
  std::string result;
  inputCode(result);
  formatCode(result);
  indentCode(result);
  std::cout << result;
}

void inputCode(std::string& result) {
  bool continueFlag = true;

  while (continueFlag) {
    Section* section = getInputOneSection();
    continueFlag = remake(section, result);
  }
}

void formatCode(std::string& code) {
  std::size_t workPoint = 0;
  while (workPoint < code.size()) {
    int stateIndex = getStateIndex(workPoint, code);
    workPoint = statements[stateIndex].taskFunc(workPoint, code);
  }
}

void indentCode(std::string& code) {
  addIndentRow(0, 0, code);
}

Section* getInputOneSection() {
  int inputChar;
  int delimiterIndex = -1; // for EOF
  Section* section = new Section; // delete by remake

  while ((inputChar = std::getchar()) != EOF) {
    delimiterIndex = findDelimiter(inputChar);
    if (delimiterIndex != -1) break; // found delimiter
    section->frontCode += static_cast<char>(inputChar);
  }

  section->delimiterIndex = delimiterIndex;
  return section;
}

bool remake(Section* const section, std::string& result) {
  bool continueFlag = section->delimiterIndex != -1;
  if (continueFlag)
    delimiters[section->delimiterIndex].taskFunc(section, result);
  else {
    if (!section->frontCode.empty())
      result += section->frontCode;
    result += '\n';
  }

  delete section; // new by getInputOneSection

  return continueFlag;
}

int findDelimiter(const char input) {
  const DelimiterInfo* delimiter_p = delimiters;

  while (delimiter_p->delimiter != '\0')
    if (input == (delimiter_p++)->delimiter) return delimiter_p - delimiters - 1;
  return -1;
}

int getStateIndex(std::size_t workIndex, const std::string code) {
  const StatementInfo* statement_p = statements;

  while (statement_p->taskFunc != NULL) {
    const std::string head_code = code.substr(workIndex, statement_p->statement.size());
std::cout << workIndex << ":Cheak code: " << head_code << std::endl;
    if (head_code == (statement_p++)->statement) return statement_p - statements - 1;
  }
  return statement_p - statements - 1;
}

void addIndentRow(int indentDepth, std::size_t workPoint, std::string& code) {
  if (workPoint >= code.size()) return;
  bool endBrace = false;

  if (code[workPoint] == '}') endBrace = true;
  code.insert(workPoint, (indentDepth - endBrace) * INDENT_WIDTH, ' '); // add indent

  std::size_t nextNewline = code.find('\n', workPoint);
  if (nextNewline == std::string::npos) nextNewline = code.size();

  indentDepth += getDiffIndent(code, workPoint, nextNewline);
  addIndentRow(indentDepth, nextNewline + 1, code);
}

int getDiffIndent(const std::string& code, const std::size_t start, const std::size_t end) {
  int diffDepth = 0;
  for (std::size_t i = start; i < end; i++)
    diffDepth += (code[i] == '{') - (code[i] == '}');
  return diffDepth;
}

void taskNormal(Section* section,  std::string& result) {
  const int delimiterIndex = section->delimiterIndex;
  const DelimiterInfo* delimiter = &delimiters[delimiterIndex];

  if (!section->frontCode.empty())
    result += section->frontCode + delimiter->normalFormat;
  else
    result += delimiter->onlyDelimFormat;
}

void taskSpace(Section* section, std::string& result) {
  if (section->frontCode.empty())
    switch (result.back()) {
      case ' ': case '\n': return;
      default: result += ' ';
    }
  else
    result += section->frontCode + ' ';
}

std::size_t taskStateFor(std::size_t workPoint, std::string& result) {
  

  return result.size();
}

std::size_t taskStateInclude(std::size_t workPoint, std::string& result) {
  workPoint = result.find(' ', workPoint + 9); // by next word (length of "#include " is 9)
  result[workPoint] = '\n';
  return workPoint + 1;
}

std::size_t taskStateDefine(std::size_t workPoint, std::string& result) {
  workPoint += 7; // go to next word (length of "#define" is 8)
  for (int i = 0; i < 2; i++)
    workPoint = result.find(' ', workPoint + 1); // go to after 2 words.
  result[workPoint] = '\n';
  return workPoint + 1;
}

std::size_t taskNoState(std::size_t workPoint, std::string& result) {
  std::size_t next_pos = result.find(' ', workPoint);
  return (next_pos != std::string::npos ? next_pos + 1 : result.size());
}

