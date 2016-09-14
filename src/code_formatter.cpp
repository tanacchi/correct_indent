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
    {"", taskNoState}
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
  while (workPoint >= code.size()) {
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

  return 0;
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

  return 0;
}

std::size_t taskStateInclude(std::size_t workPoint, std::string& result) {

  return 0;
}

std::size_t taskStateDefine(std::size_t workPoint, std::string& result) {

  return 0;
}

std::size_t taskNoState(std::size_t workPoint, std::string& result) {

  return 0;
}
