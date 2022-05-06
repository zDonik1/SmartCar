import QtQuick 2.15
import QtQuick.Window 2.15

import Controller 1.0

Window {
    width: 1296
    height: 972
    visible: true
    title: qsTr("Smart Car Preview")

    Rectangle {
        id: preview
        anchors.fill: parent
        color: "green"
        focus: true

        Keys.onPressed: controller.onKeyPressed(event.key)
        Keys.onReleased: controller.onKeyReleased(event.key)
    }
}
