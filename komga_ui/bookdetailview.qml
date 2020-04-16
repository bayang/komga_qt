import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.11
import komga_api 1.0

Item {
    width: parent.width

    Column {
        width: parent.width
        Button {
            onClicked: {
                if (contentFrame.depth > 0) {
                    contentFrame.pop()
                }
            }
            text: "Back"
        }
        Row {
            width: parent.width
            height: 400
            spacing: 10
            Image {
                id: bookDetailImage
                source: "image://books/" + controller.ui_currentBook.ui_bookId
                sourceSize.height: 300
                sourceSize.width: -1
                fillMode: Image.PreserveAspectCrop
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
                    text: "# " + qsTr(controller.ui_currentBook.ui_bookMetadata.ui_metadataNumber)
                }
                Label {
                    text: "PUBLISHER : " + qsTr(controller.ui_currentBook.ui_bookMetadata.ui_metadataPublisher)
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

    }
}
