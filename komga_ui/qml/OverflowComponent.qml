import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

import komga_api 1.0
import assets 1.0

Item {
    id: root
    property string targetId
    property alias popupWidth: popup.contentWidth
    property alias popupContent: popup.contentItem
    property alias popup: popup

    RoundButton {
        id: triggerButton
        onClicked: popup.open()
        font {
            family: Style.fontAwesomeSolid
            pointSize: Style.backArrowIconSize
        }
        text : "\uf142";
    }

    Popup {
        id: popup
        x: triggerButton.x - root.popup.contentWidth
        y: parent.y + triggerButton.height
    }
}
