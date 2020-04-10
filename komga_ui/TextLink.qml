import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14

Item {
    id: root

    signal textLinkClicked

    property real textLinkHeight: 40
    property alias textLinkLabel: innerLabel.text
    property alias textLinkLabelBold: innerLabel.font.bold
    property alias textLinkLabelSize: innerLabel.font.pixelSize

    height: textLinkHeight
    width: parent.width
    property bool currentlyHovered: false
    Label {
        id: innerLabel
        wrapMode: Text.Wrap
        width: parent.width
        color: currentlyHovered ? Material.accent : Material.foreground
    }
    MouseArea {
        id : libraryDelegateMouseArea
        width: parent.width
        height: parent.height
        hoverEnabled: true
        onClicked: {
            root.textLinkClicked()
        }
        onEntered: {
            cursorShape = Qt.PointingHandCursor
            currentlyHovered = true
        }
        onExited: {
            currentlyHovered = false
        }
    }
}
