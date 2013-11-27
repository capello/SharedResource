cmake_minimum_required(VERSION 2.8)

PROJECT(ShareResource)
FIND_PACKAGE(Qt4 REQUIRED)

SET(CMAKE_CXX_FLAGS -g)
SET(QCA_INCLUDES /usr/include/qca2/QtCrypto/)
SET(QCA_LIBRARY_DIR /usr/lib64/qca2/)

SET(libShareResource_SOURCES sources/ShareResource.cpp
                              sources/SharePeer.cpp
                              sources/ShareAuth.cpp
                              sources/ShareResourceStorage.cpp
                              sources/ShareCommunicationNetwork.cpp
                              sources/ShareConfiguration.cpp
                              sources/ShareResourceStorageMeta.cpp
                              sources/ShareResourceStorageUnit.cpp
                              sources/ShareResourceStorageUnitLocalCache.cpp
                              sources/ShareResourceStorageUnitCommunication.cpp
                              sources/ShareDebug.cpp
                              sources/ShareCache.cpp)
SET(libShareResource_HEADERS include/ShareConfiguration.h
                             interface/ShareResource.h)

QT4_WRAP_CPP(libShareResource_HEADERS_MOC ${libShareResource_HEADERS})

INCLUDE(${QT_USE_FILE})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} interface include ${QCA_INCLUDES})
link_directories(${QCA_LIBRARY_DIR})

ADD_DEFINITIONS(${QT_DEFINITIONS})

ADD_LIBRARY(ShareResource SHARED ${libShareResource_SOURCES}
  ${libShareResource_HEADERS_MOC})

TARGET_LINK_LIBRARIES(ShareResource ${QT_LIBRARIES} -lqca)

add_subdirectory(Tools)
add_subdirectory(Tests)

set(CMAKE_BUILD_TYPE debug)
