import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.11
import komga_api 1.0
import assets 1.0

Item {
    id: bookDetailRoot
    property bool imageCurrentlyHovered: false

    ScrollView {
        clip: true
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        ColumnLayout {
            width: parent.width
            Button {
                onClicked: {
                    if (contentFrame.depth > 0) {
                        contentFrame.pop()
                    }
                }
                font {
                    family: Style.fontAwesome
                    pointSize: Style.backArrowIconSize
                }
                text: "\uf060"
            }
            RowLayout {
                Layout.fillWidth: true
                Layout.minimumHeight: 330
                Layout.alignment: Qt.AlignTop
                spacing: 10
                Item {
                    id: imageBookWrapper
                    Layout.minimumWidth: bookDetailImage.width
                    Layout.alignment: Qt.AlignTop
                    Image {
                        id: bookDetailImage
                        source: "image://async/book/" + controller.ui_currentBook.ui_bookId
                        sourceSize.height: 300
                        sourceSize.width: -1
                        fillMode: Image.PreserveAspectCrop
                        ProgressBar {
                            width: parent.width
                            anchors.bottom: parent.bottom
                            contentItem.implicitHeight: 10
                            value: controller.ui_currentBook.ui_bookPageReached / controller.ui_currentBook.ui_bookPagesCount
                            visible: controller.ui_currentBook.ui_bookPageReached > 0 && ! controller.ui_currentBook.ui_bookCompleted
                        }
                    }
                    Label {
                        font {
                            family: Style.fontAwesomeSolid
                            pointSize: 50
                        }
                        anchors.centerIn: bookDetailImage
                        text: "\uf518"
                        visible: imageCurrentlyHovered
                    }

                    MouseArea {
                        id : bookDetailImageMouseArea
                        width: bookDetailImage.width
                        height: bookDetailImage.height
                        hoverEnabled: true
                        onClicked: {
                            readPopup.open()
                        }
                        onEntered: {
                            cursorShape = Qt.PointingHandCursor
                            imageCurrentlyHovered = true
                        }
                        onExited: {
                            imageCurrentlyHovered = false
                        }
                    }
                }

                ColumnLayout {
                    Layout.preferredWidth: parent.width - imageBookWrapper.width - navColumn.width
                    Layout.alignment: Qt.AlignTop
                    Label {
                        id: curBookStatus
                        text: qsTr(controller.ui_currentBook.ui_bookMetadata.ui_metadataTitle)
                        font.pointSize: Style.mediumTextSize
                    }
                    Label {
                        text: controller.ui_currentBook.ui_bookMetadata.ui_metadataWriters ? "Writers :" + qsTr(controller.ui_currentBook.ui_bookMetadata.ui_metadataWriters) : ""
                        font.pointSize: Style.smallMediumTextSize
                    }
                    Label {
                        text: controller.ui_currentBook.ui_bookMetadata.ui_metadataPencillers ? "Pencillers :" + qsTr(controller.ui_currentBook.ui_bookMetadata.ui_metadataPencillers) : ""
                        font.pointSize: Style.smallMediumTextSize
                        visible: controller.ui_currentBook.ui_bookMetadata.ui_metadataPencillers
                    }
                    Label {
                        text: controller.ui_currentBook.ui_bookMetadata.ui_metadataColorists ? "Colorists :" + qsTr(controller.ui_currentBook.ui_bookMetadata.ui_metadataColorists) : ""
                        font.pointSize: Style.smallMediumTextSize
                        visible: controller.ui_currentBook.ui_bookMetadata.ui_metadataColorists
                    }
                    Label {
                        text: controller.ui_currentBook.ui_bookMetadata.ui_metadataNumber ? "# " + qsTr(controller.ui_currentBook.ui_bookMetadata.ui_metadataNumber) : ""
                        font.pointSize: Style.smallMediumTextSize
                        visible: controller.ui_currentBook.ui_bookMetadata.ui_metadataNumber
                    }
                    Label {
                        text: controller.ui_currentBook.ui_bookMetadata.ui_metadataPublisher ? "Publisher : " + qsTr(controller.ui_currentBook.ui_bookMetadata.ui_metadataPublisher) : ""
                        font.pointSize: Style.smallMediumTextSize
                    }
                    Label {
                        text: qsTr(controller.ui_currentBook.ui_bookMetadata.ui_metadataSummary)
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        Layout.fillWidth: true
                        font.pointSize: Style.smallMediumTextSize
                    }
                }
            }
            RowLayout {
                Layout.alignment: Qt.AlignLeft
                Button {
                    text: qsTr("Read")
                    onClicked: readPopup.open()
                    font.pointSize: Style.smallTextSize
                }

                Label {
                    id : bookPagesCountLabel
                    text: qsTr(controller.ui_currentBook.ui_bookPagesCount.toString()) + " pages"
                    font.pointSize: Style.smallTextSize
                }
            }

            Label {
                text: "SIZE : " + qsTr(controller.ui_currentBook.ui_bookSize)
                font.pointSize: Style.smallTextSize
            }
            Label {
                text: "FORMAT : " + qsTr(controller.ui_currentBook.ui_bookShortMediaType)
                font.pointSize: Style.smallTextSize
            }
            Label {
                text: "FILE : " + qsTr(controller.ui_currentBook.ui_bookUrl)
                font.pointSize: Style.smallTextSize
            }

        }

    }


    Popup {
        id: readPopup
        parent: Overlay.overlay

        contentWidth: ApplicationWindow.window.width
        contentHeight: ApplicationWindow.window.height

        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape
        opacity: 1.0
        Overlay.modal: Rectangle {
            color: Qt.darker(Style.backgroundColor)
        }
        enter: Transition {
            NumberAnimation { property: "opacity"; from: 0.0; to: 1.0; duration: 800 }
        }
        exit: Transition {
            NumberAnimation { property: "opacity"; from: 1.0; to: 0.0; duration: 300 }
        }
        BookReadView {
            anchors.fill: parent
        }
    }
}
