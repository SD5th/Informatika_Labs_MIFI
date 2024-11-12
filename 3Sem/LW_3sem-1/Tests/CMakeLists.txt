find_package(Catch2 3 REQUIRED)

add_executable(Tests Tests.cpp)

target_link_libraries(Tests SmartPointers Catch2::Catch2WithMain)