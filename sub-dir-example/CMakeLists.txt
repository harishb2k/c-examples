cmake_minimum_required(VERSION 3.12)
project(sub-dir-example)
set(CMAKE_CXX_STANDARD 14)
message("Project Name: ${PROJECT_NAME}")

# This will put rocks DB include and Libs in the path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

add_subdirectory(helper)
add_executable(${PROJECT_NAME} src/main.cpp)

include(ExternalProject)

# Path to install external libs
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_SOURCE_DIR}/external/cppkafka)
message("EXTERNAL_INSTALL_LOCATION = ${EXTERNAL_INSTALL_LOCATION}")

# Add a external project in the path & expose to external path
ExternalProject_Add(
        CppKafka
        GIT_REPOSITORY https://github.com/mfontanini/cppkafka.git
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION} -DCPPKAFKA_DISABLE_TESTS=ON -DCPPKAFKA_BUILD_SHARED=OFF
)
set(CppKafka_INCLUDE_DIRS ${EXTERNAL_INSTALL_LOCATION}/include)
set(CppKafka_LIBRARIES ${EXTERNAL_INSTALL_LOCATION}/lib/libcppkafka.a)
message("CppKafka_INCLUDE_DIRS = ${CppKafka_INCLUDE_DIRS}")
message("CppKafka_LIBRARIES = ${CppKafka_LIBRARIES}")

# We need RdKafka for CppKafka to work
find_package(RDKAFKA REQUIRED)
set(LIBS ${LIBS} ${RDKAFKA_LIBRARIES})
include_directories(${RDKAFKA_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${RDKAFKA_LIBRARIES})

# Link helper project
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC helper)

include_directories(${CppKafka_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CppKafka_LIBRARIES})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${CppKafka_LIBRARIES})
