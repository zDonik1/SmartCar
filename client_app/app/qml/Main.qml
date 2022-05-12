import QtQuick 2.15
import QtQuick.Window 2.15

import Stream 1.0
import Controller 1.0

Window {
    width: 1296
    height: 972
    visible: true
    title: qsTr("Smart Car Preview")

    Component.onCompleted: controller.setStreamPreview(preview)

    StreamPreview {
        id: preview
        anchors.fill: parent
        focus: true
    }
}
