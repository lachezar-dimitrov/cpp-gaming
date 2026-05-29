cmake_minimum_required(VERSION 3.20)

project(cpp_gaming LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(cpp_gaming src/main.cpp)
target_link_libraries(cpp_gaming PRIVATE SFML::Graphics SFML::Window SFML::System)
