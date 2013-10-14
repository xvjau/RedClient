#Fake code so that QtCreator finds these files

FILE(GLOB QML_FILES "*.qml")

add_custom_target(fake_qml_target
SOURCES ${QML_FILES})
