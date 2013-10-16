project(RedClient)
cmake_minimum_required(VERSION 2.8)
find_package(Qt5 COMPONENTS Gui Widgets Qml Quick Sql)

set(CMAKE_AUTOMOC ON)

add_definitions(${Qt5Widgets_DEFINITIONS} -std=c++11 -fPIC -fPIE -Wall -Wextra)

include_directories(${Qt5Gui_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Qml_INCLUDE_DIRS} ${Qt5Quick_INCLUDE_DIRS} ${Qt5Sql_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(widgets)

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

set(RedClient_SRCS ${CMAKE_CURRENT_BINARY_DIR}/qml.cpp abstracttreemodel.cpp projectsmodel.cpp rmrequest.cpp rmreqprojects.cpp redminemanager.cpp main.cpp rmproject.cpp login.cpp)

qt5_wrap_ui(UI_SRCS login.ui)

add_executable(RedClient ${RedClient_SRCS} ${UI_SRCS})

target_link_libraries(RedClient RedClientWidgets ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5Qml_LIBRARIES} ${Qt5Quick_LIBRARIES} ${Qt5Sql_LIBRARIES})

install(TARGETS RedClient RUNTIME DESTINATION bin)
