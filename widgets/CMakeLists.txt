include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(RedClientWidgets_SRCS mainwindow.ui mainwindow.cpp)

qt5_wrap_ui(RedClientWidgets_UI_SRCS mainwindow.ui)

add_library(RedClientWidgets ${RedClientWidgets_UI_SRCS} ${RedClientWidgets_SRCS})