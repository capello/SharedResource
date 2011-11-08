cmake_minimum_required(VERSION 2.8)

PROJECT(ShareResource)
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} interface include)

add_executable(ShareDeamon source/ShareDeamon.cpp)