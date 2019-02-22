/*
 * 1. 構文解析器を備えた、コンパイラ１歩手前くらいのものをつくる
 * 2. オプションによってコーディングスタイルを設定できるようにする
 *
 */

#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char** argv)
{
  const std::string source_file_name{argv[1]};
  std::fstream source_file_stream(source_file_name, std::ios::in);

  std::string input_string_raw{};
  for (std::string input_buff{}; std::getline(source_file_stream, input_buff);)
  {
    std::cout << input_buff << std::endl;
    input_string_raw += input_buff + ' ';
  }

  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  std::cout << input_string_raw << std::endl;
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  return 0;
}
