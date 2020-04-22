import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.11
import komga_api 1.0
import assets 1.0

Item {
    property bool imageCurrentlyHovered: false

    Column {
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
        Row {
            width: parent.width
            height: 330
            spacing: 10
            bottomPadding: 0
            Item {
                Image {
                    id: bookDetailImage
                    source: "image://books/" + controller.ui_currentBook.ui_bookId
                    sourceSize.height: 300
                    sourceSize.width: -1
                    fillMode: Image.PreserveAspectCrop
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
                        controller.goBookReadView()
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

            Column {
                width: parent.width - bookDetailImage.width
                Label {
                    id: curBookStatus
                    text: qsTr(controller.ui_currentBook.ui_bookMetadata.ui_metadataTitle)
                }
                Label {
                    text: qsTr(controller.ui_currentBook.ui_bookMetadata.ui_metadataAuthors)
                }
                Label {
                    text: controller.ui_currentBook.ui_bookMetadata.ui_metadataNumber ? "# " + qsTr(controller.ui_currentBook.ui_bookMetadata.ui_metadataNumber) : ""
                }
                Label {
                    text: controller.ui_currentBook.ui_bookMetadata.ui_metadataPublisher ? "PUBLISHER : " + qsTr(controller.ui_currentBook.ui_bookMetadata.ui_metadataPublisher) : ""
                }
                Label {
                    text: qsTr(controller.ui_currentBook.ui_bookMetadata.ui_metadataSummary)
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    width: parent.width
                }
            }
        }
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Button {
                text: "Read"
                onClicked: controller.goBookReadView()
            }

            Label {
                id : bookPagesCountLabel
                text: qsTr(controller.ui_currentBook.ui_bookPagesCount.toString()) + " pages"
            }
        }

        Label {
            text: "SIZE : " + qsTr(controller.ui_currentBook.ui_bookSize)
        }
        Label {
            text: "FORMAT : " + qsTr(controller.ui_currentBook.ui_bookShortMediaType)
        }
        Label {
            text: "FILE : " + qsTr(controller.ui_currentBook.ui_bookUrl)
        }

    }
}
