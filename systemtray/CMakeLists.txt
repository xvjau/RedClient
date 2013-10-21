include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(RedClientSystemTray_SRCS mainwindow.ui mainwindow.cpp)

qt5_wrap_ui(RedClientSystemTray_UI_SRCS mainwindow.ui)
    
add_executable(RedClientSystemTray ${RedClientSystemTray_UI_SRCS} ${RedClientSystemTray_SRCS} main.cpp)

target_link_libraries(RedClientSystemTray RedClient ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5Qml_LIBRARIES} ${Qt5Quick_LIBRARIES} ${Qt5Sql_LIBRARIES} ${EXTRA_LIBS})