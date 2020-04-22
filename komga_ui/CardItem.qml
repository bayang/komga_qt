import QtQuick 2.14
import QtGraphicalEffects 1.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14

Item {
    id: root

    property real cardWidth
    property real cardHeight
    property real thumbnailHeight

    property alias imagePath: seriesImage.source
    property alias cardLabel: labelText.text
    property alias subLabel: subText.text
    property alias topCornerLabel: nbBooksLabel.text
    property color hoverBorderColor: "lightsteelblue"
    property alias topCornerLabelFontSize: nbBooksLabel.font.pointSize

    signal cardClicked

    width: cardWidth
    height: cardHeight - 10
    property bool cardCurrentlyHovered: false


    Rectangle {
        id: seriesDelegateBackgound
        anchors.horizontalCenter: root.horizontalCenter
        width: parent.width
        height: parent.height
        color: Qt.lighter(Material.backgroundColor)
        radius: 8

        Column {
            id: seriesDelegateColumn
            spacing: 0
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width

            Image {
                id: seriesImage
                property bool rounded: true
                source: "image://series/"
                sourceSize.height: thumbnailHeight
                sourceSize.width: cardWidth
                fillMode: Image.PreserveAspectCrop
                anchors.horizontalCenter: seriesDelegateColumn.horizontalCenter
                layer.enabled: rounded
                    layer.effect: OpacityMask {
                        maskSource: Item {
                            width: seriesImage.width
                            height: seriesImage.height
                            Rectangle {
                                anchors.centerIn: parent
                                width: seriesImage.width
                                height: seriesImage.height
                                radius: 8
                            }
                        }
                    }
            }
            Label {
                id : labelText
                anchors.horizontalCenter: parent.horizontalCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                elide: Text.ElideRight
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                height: seriesDelegateBackgound.height - seriesImage.height - subText.height
            }
            Label {
                id : subText
                anchors.horizontalCenter: parent.horizontalCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                width: parent.width
                horizontalAlignment: Text.AlignHCenter

            }

        }
    }
    MouseArea {
        id : seriesDelegateMouseArea
        width: parent.width
        height: parent.height
        hoverEnabled: true
            ToolTip.delay: 1500
            ToolTip.timeout: 3000
            ToolTip.visible: cardCurrentlyHovered
            ToolTip.text: qsTr(cardLabel)
        onClicked: {
            root.cardClicked()
        }
        onEntered: {
            cursorShape = Qt.PointingHandCursor
            cardCurrentlyHovered = true
        }
        onExited: {
            cardCurrentlyHovered = false
        }
    }
    Rectangle {
        id: seriesDelegateRect
        border.color: hoverBorderColor
        width: cardWidth
        height: parent.height
        border.width: cardCurrentlyHovered ? 3 : 0
        radius: 8
        color: "transparent"
        anchors.horizontalCenter: seriesDelegateBackgound.horizontalCenter
    }

    Rectangle {
        anchors.top: seriesDelegateRect.top
        anchors.right: seriesDelegateRect.right
        height: 30
        width: 30
        color: hoverBorderColor
        radius: 8
        Label {
            id: nbBooksLabel
            anchors.centerIn: parent
//            font.pointSize: 16
            font.bold: true
        }
    }
}
