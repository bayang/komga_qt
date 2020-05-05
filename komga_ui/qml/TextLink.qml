import QtQuick 2.14
import QtQuick.Controls 2.14
import assets 1.0

Item {
    id: root

    signal textLinkClicked

    property real textLinkHeight: 40
    property alias textLinkLabel: innerLabel.text
    property alias textLinkLabelBold: innerLabel.font.bold
    property alias textLinkLabelSize: innerLabel.font.pointSize

    height: textLinkHeight
    width: parent.width
    property bool currentlyHovered: false

    Label {
        id: innerLabel
        wrapMode: Text.Wrap
        width: parent.width
        color: currentlyHovered ? Style.accentColor : Style.foregroundColor
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
}
