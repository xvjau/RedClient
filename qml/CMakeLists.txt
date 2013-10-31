file(GLOB QML_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.qml")

add_custom_command(
    OUTPUT qml.cpp

    COMMAND echo ${QML_FILES} > ${CMAKE_CURRENT_BINARY_DIR}/qml.tmp

    COMMAND sed 's/\\s/\\n/g' -i ${CMAKE_CURRENT_BINARY_DIR}/qml.tmp
    COMMAND sed 's/.*\\///g' -i ${CMAKE_CURRENT_BINARY_DIR}/qml.tmp
    COMMAND sed 's/^/\\t\\t\\<file\\>/' -i ${CMAKE_CURRENT_BINARY_DIR}/qml.tmp
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

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(RedClientQML_SRCS qml.cpp)

#qt5_wrap_ui(RedClientQML_UI_SRCS mainwindow.ui)

add_executable(RedClientQML ${RedClientQML_SRCS} ${RedClientQML_UI_SRCS} main.cpp)

target_link_libraries(RedClientQML RedClient ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5Qml_LIBRARIES} ${Qt5Quick_LIBRARIES} ${Qt5Sql_LIBRARIES} ${EXTRA_LIBS})