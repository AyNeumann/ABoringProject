import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: root
    visibility: Window.Maximized
    visible: true
    title: qsTr("A Boring Project")

    menuBar: B_Toolbar {}

    Rectangle {
        id: sideMenu
        width: root.width / 6
        height: root.height
        color: "dodgerblue"

        Button {
            id: doSomethingBtn
            text: "Do something"
            width: sideMenu.width - 2
            anchors.horizontalCenter: sideMenu.horizontalCenter
        }
    }

    Rectangle {
        id: mainWindow
        width: root.width - sideMenu.width
        height: root.height
        anchors.left: sideMenu.right
        color: "lightgray"

        StackView {
            id: stack
            anchors.fill: parent
        }
    }


}
