cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

project(cppexamples VERSION 0.1.0 LANGUAGES CXX)

add_executable(binary_literals binary_literals.cpp)

add_executable(class_enums class_enums.cpp)

add_executable(filesystem filesystem.cpp)
target_link_libraries(filesystem -lstdc++fs)

add_executable(has_include has_include.cpp)

add_executable(lambda_expressions lambda_expressions.cpp)

add_executable(move move.cpp)

add_executable(random random.cpp)

add_executable(range_for range_for.cpp)

add_executable(raw_string_literals raw_string_literals.cpp)

add_executable(thread thread.cpp)
target_link_libraries(thread -lpthread)

add_executable(uniform_initialization uniform_initialization.cpp)

add_executable(virtual_override_final virtual_override_final.cpp)
