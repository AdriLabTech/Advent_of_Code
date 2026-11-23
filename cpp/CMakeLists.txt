cmake_minimum_required(VERSION 3.20)
project(aoc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Un día = un fichero src/solutions/y{año}/day{NN}.cpp (CONFIGURE_DEPENDS: se detecta solo al compilar)
file(GLOB_RECURSE SOLUTIONS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/solutions/*.cpp)

add_executable(aoc src/core/main.cpp ${SOLUTIONS})
target_include_directories(aoc PRIVATE src/core)
target_compile_definitions(aoc PRIVATE AOC_DEFAULT_INPUTS_DIR="${CMAKE_SOURCE_DIR}/../inputs")
if(NOT MSVC)
  target_compile_options(aoc PRIVATE -Wall -Wextra)
endif()
