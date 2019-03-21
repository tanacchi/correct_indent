cmake_minimum_required(VERSION 3.5.1)

project(
  correct_indent
  VERSION 0.0.0
  LANGUAGES CXX
)

find_package(Boost REQUIRED)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-Wall -std=c++1y")

include_directories(
  include
  ${Boost_INCLUDE_DIRS}
)
link_directories(${Boost_LIBRARY_DIRS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)
set(OUTPUT_NAME "a.out")
add_executable(${OUTPUT_NAME}
  src/main.cpp
)
target_link_libraries(${OUTPUT_NAME}
  ${Boost_LIBRARIES}
)
