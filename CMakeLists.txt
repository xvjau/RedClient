project(RedClient)
cmake_minimum_required(VERSION 2.8)

find_package(Qt5 COMPONENTS Gui Widgets Qml Quick Sql)
include_directories(${Qt5Gui_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Qml_INCLUDE_DIRS} ${Qt5Quick_INCLUDE_DIRS} ${Qt5Sql_INCLUDE_DIRS})
add_definitions(${Qt5Widgets_DEFINITIONS})

set(ENABLE_LTO FALSE CACHE BOOL "Enable Link-Time optimization")
if (${ENABLE_LTO})
    set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -flto)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -flto)
    set(CMAKE_LINK_LIBRARY_FLAG ${CMAKE_LINK_LIBRARY_FLAG} -flto)
    set(CMAKE_LINK_EXE_FLAG ${CMAKE_LINK_EXE_FLAG} -flto)
endif()

set(ENABLE_ADDRESS_SANITIZER FALSE CACHE BOOL "Enable Address-sanitizer")
if (${ENABLE_ADDRESS_SANITIZER})
    add_definitions(-fsanitize=address)
    set(EXTRA_LIBS ${EXTRA_LIBS} asan)
endif()

set(CMAKE_AUTOMOC ON)

add_definitions(-std=c++11 -fPIC -fPIE -Wall -Wextra)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

FILE(GLOB QML_FILES "qml/*.qml")

add_custom_command(
    OUTPUT qml.cpp

    COMMAND echo ${QML_FILES} > ${CMAKE_CURRENT_BINARY_DIR}/qml.tmp

    COMMAND sed 's/\\s/\\n/g' -i ${CMAKE_CURRENT_BINARY_DIR}/qml.tmp
    COMMAND sed 's/.*\\///g' -i ${CMAKE_CURRENT_BINARY_DIR}/qml.tmp
    COMMAND sed 's/^/\\t\\t\\<file\\>qml\\//' -i ${CMAKE_CURRENT_BINARY_DIR}/qml.tmp
    COMMAND sed 's/$$/\\<\\/file\\>/' -i ${CMAKE_CURRENT_BINARY_DIR}/qml.tmp

    COMMAND echo -e '<RCC>\\n\\t<qresource prefix=\"/\">' > qml.qrc
    COMMAND cat ${CMAKE_CURRENT_BINARY_DIR}/qml.tmp >> qml.qrc
    COMMAND echo -e '\\t</qresource>\\n</RCC>' >> qml.qrc

    COMMAND rcc qml.qrc > ${CMAKE_CURRENT_BINARY_DIR}/qml.cpp

    COMMAND rm qml.qrc ${CMAKE_CURRENT_BINARY_DIR}/qml.tmp

    DEPENDS ${QML_FILES}

    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}

    COMMENT "QML Resources"
)

set(RedClient_SRCS 
    ${CMAKE_CURRENT_BINARY_DIR}/qml.cpp 
    
    rmobjectsummary.cpp
    rmproject.cpp 
    rmissue.cpp 
    rmtimeentry.cpp 
    
    rmrequest.cpp 
    rmreqprojects.h 
    rmreqissues.h
    rmreqtimeentry.h
    
    abstracttreemodel.cpp 
    projectsmodel.cpp 
    issuesmodel.cpp
    timeentriesmodel.cpp
    
    redminemanager.cpp 
    
    login.cpp)


qt5_wrap_ui(UI_SRCS login.ui)

add_library(RedClient ${RedClient_SRCS} ${UI_SRCS})

add_subdirectory(widgets)
add_subdirectory(systemtray)