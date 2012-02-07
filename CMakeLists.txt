cmake_minimum_required(VERSION 2.8)

PROJECT(ShareResource)
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} interface include)

SET(libShareResource_SOURCES sources/ShareResource.cpp 
                              sources/SharePeer.cpp
                              sources/ShareAuth.cpp
                              sources/ShareResourceId.cpp
                              sources/ShareResourceStorage.cpp
                              sources/ShareCommunicationNetwork.cpp)
SET(libShareResource_HEADERS )
   
QT4_WRAP_CPP(libShareResource_HEADERS_MOC ${libShareResource_HEADERS})

INCLUDE(${QT_USE_FILE} )

ADD_DEFINITIONS(${QT_DEFINITIONS})

ADD_LIBRARY(libShareResource SHARED ${libShareResource_SOURCES} 
  ${libShareResource_HEADERS_MOC})

TARGET_LINK_LIBRARIES(libShareResource ${QT_LIBRARIES})

add_subdirectory(Tools)
add_subdirectory(Tests)

set(CMAKE_BUILD_TYPE debug)