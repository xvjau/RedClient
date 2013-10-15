import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0

ApplicationWindow {
    title: qsTr("Red Client")
    width: 800
    height: 600

    Rectangle {
        width: parent.width
        height: parent.heigth

        Row {
            anchors.fill:parent
            anchors.margins: 8

            spacing: 9

//             TextField {
//                 id: userName
//                 placeholderText: "User Name"
//             }
        }
    }
}
