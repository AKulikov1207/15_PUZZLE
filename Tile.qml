import QtQuick 2.0

Rectangle {
    id: root

    property string displayText: ""

    color: "lightgreen"

    border.color: "black"
    border.width: 1

    radius: 10

    Text {
        id: _firstText
        anchors.centerIn: root

        text: root.displayText
        font.pointSize: Math.min(root.width, root.height) / 3
        font.bold: true
    }
}
