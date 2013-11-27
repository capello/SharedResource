cmake_minimum_required(VERSION 2.8)

PROJECT(ShareResource)
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} interface include)

add_executable(simpleTextFile source/simpleTextFile.cpp)

target_link_libraries(simpleTextFile ShareResource)

set(CMAKE_BUILD_TYPE debug)
