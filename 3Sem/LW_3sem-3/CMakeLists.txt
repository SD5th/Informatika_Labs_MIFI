cmake_minimum_required(VERSION 3.16)

project(LW_3Sem-3)

#add_compile_options(--coverage)
#add_link_options(--coverage)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(SOURCES
    main.cpp)
add_executable(Main ${SOURCES})

target_link_libraries(Main PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets)