cmake_minimum_required(VERSION 3.12)
project(sub-dir-example)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(helper)
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} helper)
