project(RedClient)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(RedClient_SRCS RedClient.cpp main.cpp)
qt4_automoc(${RedClient_SRCS})
add_executable(RedClient ${RedClient_SRCS})
target_link_libraries(RedClient ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
install(TARGETS RedClient RUNTIME DESTINATION bin)
