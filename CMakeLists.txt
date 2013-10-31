project(RedClient)
cmake_minimum_required(VERSION 2.8)

find_package(Qt5 COMPONENTS Gui Widgets Qml Quick Sql)
include_directories(${Qt5Gui_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Qml_INCLUDE_DIRS} ${Qt5Quick_INCLUDE_DIRS} ${Qt5Sql_INCLUDE_DIRS})
add_definitions(${Qt5Widgets_DEFINITIONS})

set(ENABLE_LTO FALSE CACHE BOOL "Enable Link-Time optimization")
if (${ENABLE_LTO})
    set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -flto)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -flto)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -flto")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -flto")
endif()

set(ENABLE_ADDRESS_SANITIZER FALSE CACHE BOOL "Enable Address-sanitizer")
if (${ENABLE_ADDRESS_SANITIZER})
    add_definitions(-fsanitize=address)
    set(EXTRA_LIBS ${EXTRA_LIBS} asan)
endif()

set(CMAKE_AUTOMOC ON)

add_definitions(-std=c++11 -fPIC -fPIE -Wall -Wextra)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--as-needed -O1")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--as-needed -O1")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,--as-needed -O1")

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

set(RedClient_SRCS 
    ${CMAKE_CURRENT_BINARY_DIR}/qml.cpp 
    
    rmobjectsummary.cpp
    rmproject.cpp 
    rmissue.cpp 
    rmtimeentry.cpp     
    rmuser.cpp
    
    rmrequest.cpp 
    rmreqprojects.h 
    rmreqissues.h
    rmreqtimeentry.h
    rmrequsers.h
    
    abstracttreemodel.cpp 
    projectsmodel.cpp 
    issuesmodel.cpp
    timeentriesmodel.cpp
    usersmodel.cpp
    
    redminemanager.cpp 
    
    login.cpp)


qt5_wrap_ui(UI_SRCS login.ui)

add_library(RedClient ${RedClient_SRCS} ${UI_SRCS})

add_subdirectory(widgets)
add_subdirectory(systemtray)
add_subdirectory(qml)
