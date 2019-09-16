cmake_minimum_required(VERSION 3.12)
project(sub-dir-example)
set(CMAKE_CXX_STANDARD 14)
message("Project Name: ${PROJECT_NAME}")

# This will put rocks DB include and Libs in the path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

add_subdirectory(helper)
add_executable(${PROJECT_NAME} src/main.cpp)

include(ExternalProject)

# Add a external project in the path & expose to external path
set(EXTERNAL_CPP_KAFKA_INSTALL_LOCATION ${CMAKE_SOURCE_DIR}/external/cppkafka)
ExternalProject_Add(
        CppKafka
        GIT_REPOSITORY https://github.com/mfontanini/cppkafka.git
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_CPP_KAFKA_INSTALL_LOCATION} -DCPPKAFKA_DISABLE_TESTS=ON -DCPPKAFKA_BUILD_SHARED=OFF
        UPDATE_COMMAND ""
)
set(CppKafka_INCLUDE_DIRS ${EXTERNAL_CPP_KAFKA_INSTALL_LOCATION}/include)
set(CppKafka_LIBRARIES ${EXTERNAL_CPP_KAFKA_INSTALL_LOCATION}/lib/libcppkafka.a)

# We need RdKafka for CppKafka to work
find_package(RDKAFKA REQUIRED)
find_package(rocksdb REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE ${CppKafka_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${RDKAFKA_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${RocksDB_INCLUDE_DIR})

# Link helper project
target_link_libraries(
        ${PROJECT_NAME} LINK_PRIVATE ${RDKAFKA_LIBRARIES} ${CppKafka_LIBRARIES} helper ${RocksDB_LIBRARIES}
)