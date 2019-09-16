cmake_minimum_required(VERSION 3.12)
project(helper)
set(CMAKE_CXX_STANDARD 14)

add_library(helper src/helper.cpp)
target_include_directories(helper PUBLIC include)



