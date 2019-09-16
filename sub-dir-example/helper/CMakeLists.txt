cmake_minimum_required(VERSION 3.12)
project(helper)
set(CMAKE_CXX_STANDARD 14)

# add_library - this will create a lib project with name "helper"
add_library(helper src/helper.cpp)

# This will ensure that inlcude from this sub-dir is visible to parent for access
target_include_directories(helper PUBLIC include)



