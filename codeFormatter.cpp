#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>

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

Section* getInputOneSection();
bool remake(Section* section, std::string& result);
void taskNormal(Section* section, std::string& result);
void taskSpace(Section* section, std::string& result);
int findDelimiter(char input);
void formatCode(std::string& code);
void indentCode(std::string& code);
void addIndentRow(int indentDepth, int workPoint, std::string& code);
int getDiffIndent(const std::string& code, int start, int end);

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

bool remake(Section* section, std::string& result) {
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

void taskNormal(Section* section,  std::string& result) {
  const int delimiterIndex = section->delimiterIndex;
  const DelimiterInfo* delimiter = &delimiters[delimiterIndex];

  if (!section->frontCode.empty())
    result += section->frontCode + section->normalFormat;
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

int findDelimiter(char input) {
  int i;
  const DelimiterInfo* delimiter_p = delimiters;

  while (delimiter_p->delimiter != '\0')
    if (input == (delimiter_p++)->delimiter) return delimiter_p - delimiters - 1;
  return -1;
}

void formatCode(std::string& code) {
  
}

void indentCode(std::string& code) {
  addIndentRow(0, 0, code);
}

void addIndentRow(int indentDepth, int workPoint, std::string& code) {
  if (workPoint >= code.size()) return;
  bool endBrace = false;

  if (code[workPoint] == '}') endBrace = true;
  code.insert(workPoint, (indentDepth - endBrace) * INDENT_WIDTH, ' '); // add indent

  int nextNewline = code.find('\n', workPoint);
  if (nextNewline == std::string::npos) nextNewline = code.size();

  indentDepth += getDiffIndent(code, workPoint, nextNewline);
  addIndentRow(indentDepth, nextNewline + 1, code);
}

int getDiffIndent(const std::string& code, int start, int end) {
  int diffDepth = 0;
  for (int i = start; i < end; i++)
    diffDepth += (code[i] == '{') - (code[i] == '}');
  return diffDepth;
}
