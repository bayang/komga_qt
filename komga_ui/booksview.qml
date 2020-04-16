import QtQuick 2.14
import QtQuick.Controls 2.14
import komga_api 1.0

Item {
    property real thumbnailRequestedHeight: 230
    property real thumbnailRequestedWidth: 175

    Column {
        anchors.fill: parent
        Button {
            onClicked: {
                if (contentFrame.depth > 0) {
                    contentFrame.pop()
                }
            }
            text: "Back"
        }

        Row {
            id : firstRow
            height: 350
            Image {
                id: seriesDetailImage
                source: "image://series/" + controller.ui_currentSeries.ui_seriesId
                sourceSize.height: 300
                sourceSize.width: -1
                fillMode: Image.PreserveAspectCrop
            }
            Column {
                Label {
                    id: seriesText
                    text: qsTr(controller.ui_currentSeries.ui_seriesName)
                }
                Label {
                    id: seriesStatus
                    text: qsTr("STATUS : " + controller.ui_currentSeries.ui_seriesMetadataStatus)
                }
            }
        }

        ScrollView {
            width: parent.width
            height: parent.height - firstRow.height
            clip: true
            GridView {
                id: booksList
                model: controller.ui_bookModel
                clip: true
                cellWidth : thumbnailRequestedWidth + 5
                cellHeight: thumbnailRequestedHeight + 85
                onMovementEnded: {
                    if (atYEnd) {
                        console.log("Y end")
                        controller.nextBooksPage()
                    }
                }

                delegate:
                    CardItem {
                    cardWidth: thumbnailRequestedWidth
                    cardHeight: booksList.cellHeight
                    thumbnailHeight: thumbnailRequestedHeight
                    imagePath: "image://books/" + bookId
                    cardLabel: bookName
                    subLabel: bookPageCount + " pages"
                    topCornerLabel: bookMediaType
                    onCardClicked: {
                        booksList.currentIndex = index
                        controller.setSelectedBook(booksList.currentIndex)
                        controller.goBookDetailView()
                    }
                }
            }
        }
    }
}
