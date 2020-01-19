import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Tile {
        width: root.width / 4
        height: root.height / 4
    }
}
