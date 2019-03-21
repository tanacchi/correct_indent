/*
 * 1. 構文解析器を備えた、コンパイラ１歩手前くらいのものをつくる
 * 2. オプションによってコーディングスタイルを設定できるようにする
 *
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <regex>

#include "token.hpp"
#include "code_block.hpp"
#include "node.hpp"

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

  std::vector<std::string> source_strings{};
  for (std::string input_buff{}; std::getline(source_file_stream, input_buff);)
  {
    source_strings.emplace_back(input_buff);
  }

  for (auto& s : source_strings)
  {
    // 行頭・行末の空白を除去
    s = " " + s + " ";
    s.erase(s.begin(),                           s.begin() + s.find_first_not_of(" "));
    s.erase(s.begin() + s.find_last_not_of(" ") + 1, s.end());

    // 連続する空白を除去
    auto no_consecutive_space_itr{remove_consecutive_chars(s.begin(), s.end(), ' ')};
    s.erase(no_consecutive_space_itr, s.end());

    s.erase(std::remove(s.begin(), s.end(), '\0'), s.end());
  }
  source_strings.erase(std::remove(source_strings.begin(), source_strings.end(), std::string{}), source_strings.end());

  std::vector<std::vector<std::string>> string_matrix{};
  for (const auto& str : source_strings)
  {
    std::vector<std::string> token_strings{};
    for (std::string target{str}; !target.empty();)
    {
      std::smatch result{};
      if (std::regex_search(target, result, std::regex("\\W")))
      {
        std::string prefix{result.prefix()};
        if (!prefix.empty())
          token_strings.emplace_back(prefix);
        token_strings.emplace_back(result.str());
      }
      else
      {
        token_strings.emplace_back(target);
      }
      target = result.suffix();
    }
    token_strings.emplace_back("\n");
    string_matrix.emplace_back(token_strings);
  }

  token::TokenArray tokens1{token::parse1(string_matrix)};
  token::TokenArray tokens2{token::parse2(std::move(tokens1))};
  for (const auto& anytoken : tokens2)
  {
    std::cout << anytoken.token_ptr->content << "\t\t<-[" << anytoken.token_ptr->attribute_ptr->name << "]" << std::endl;
  }

  auto blocks = gen_code_blocks(tokens2);
  node::node_test(tokens2, blocks);

  return 0;
}
