cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
add_library(Sorters
            ISorter.hpp
            BubbleSorter.hpp 
            .cpp)