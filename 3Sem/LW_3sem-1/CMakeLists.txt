cmake_minimum_required(VERSION 3.16)

project(LW_3Sem-1)

add_compile_options(--coverage)
add_link_options(--coverage)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

add_subdirectory(Source)
add_subdirectory(Tests)