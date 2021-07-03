import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Item {
    id: toolbarItem
    anchors.fill: parent
    RowLayout {
        anchors.fill: parent
        ToolButton {
            text: qsTr("File")
            onClicked: {
                console.log("File toolbar btn clicked");
            }
        }
    }
}
