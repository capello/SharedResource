cmake_minimum_required(VERSION 2.8)

PROJECT(ShareResource)
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} interface include)

SET (ShareConfigSoftware_HEADERS interface/ShareConfigMainWindow.h)
SET (ShareConfigSoftware_SOURCES
                                   source/ShareConfigSoftware.cpp
                                   source/ShareConfigMainWindow.cpp)

QT4_WRAP_CPP(ShareConfigSoftware_SOURCES ${ShareConfigSoftware_HEADERS})

add_executable(ShareConfigSoftware ${ShareConfigSoftware_SOURCES})

TARGET_LINK_LIBRARIES(ShareConfigSoftware ${QT_LIBRARIES})