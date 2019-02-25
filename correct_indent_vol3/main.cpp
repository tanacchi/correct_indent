/*
 * 1. 構文解析器を備えた、コンパイラ１歩手前くらいのものをつくる
 * 2. オプションによってコーディングスタイルを設定できるようにする
 *
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <regex>

#include "token.hpp"

template<typename charT = char>
decltype(auto) remove_consecutive_chars(
    typename std::basic_string<charT>::iterator first,
    typename std::basic_string<charT>::iterator last,
    const charT target)
{
  charT prev_char{'\0'};
  auto result{first};
  for (; first != last; ++first)
  {
    if (!(*first == prev_char && *first == target))
    {
      *result++ = prev_char = *first;
    }
  }
  return result;
}

int main(int argc, char** argv)
{
  const std::string source_file_name{argv[1]};
  std::fstream source_file_stream(source_file_name, std::ios::in);

  std::string input_string_raw{};
  for (std::string input_buff{}; std::getline(source_file_stream, input_buff);)
  {
    input_string_raw += input_buff + '\n';
  }

  auto result1{remove_consecutive_chars(input_string_raw.begin(), 
                                        input_string_raw.end(), 
                                        ' ')};
  auto result2{remove_consecutive_chars(input_string_raw.begin(), 
                                        result1,
                                        '\n')};

  std::stringstream ss{input_string_raw.assign(input_string_raw.begin(), result2)};
  std::vector<std::string> string_rows{};
  for (std::string row_buff{}; std::getline(ss, row_buff);)
  {
    if (row_buff != " ")
      string_rows.emplace_back(row_buff);
  }

  for (auto& str : string_rows)
  {
    std::string::size_type length{str.find_last_not_of(" ") - str.find_first_not_of(" ") + 1};
    str = str.substr(str.find_first_not_of(" "), length);
  }
  
  std::vector<std::vector<std::string>> tokens{};
  for (auto& str : string_rows)
  {
    std::vector<std::string> sub_tokens{};
    for (std::string target{str}; !target.empty();)
    {
      std::smatch result{};
      if (std::regex_search(target, result, std::regex("\\W")))
      {
        std::string prefix{result.prefix()};
        if (!prefix.empty())
          sub_tokens.emplace_back(prefix);
        sub_tokens.emplace_back(result.str());
      }
      else
      {
        sub_tokens.emplace_back(target);
      }
      target = result.suffix();
    }
    tokens.emplace_back(sub_tokens);
  }

  parse_level_1(tokens);

  return 0;
}
