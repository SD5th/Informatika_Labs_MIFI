cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
add_library(SmartPointers
            UnqPtr.hpp 
            ShrdPtr.hpp 
            DynamicArray.hpp
            LinkedList.hpp
            .cpp)