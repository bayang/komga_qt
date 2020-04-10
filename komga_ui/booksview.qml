import QtQuick 2.14
import QtQuick.Controls 2.14
import komga_api 1.0

Item {
    Component.onCompleted: {
        bookModel.loadBooks(currentSeries.ui_seriesId)
    }

    property real thumbnailRequestedHeight: 230
    property real thumbnailRequestedWidth: 175

    Column {
        anchors.fill: parent
        Label {
            id: seriesText
            text: qsTr("In Series " + currentSeries.ui_seriesName)
        }
        Label {
            id: seriesStatus
            text: qsTr("Status " + currentSeries.ui_seriesMetadataStatus)
        }
        ScrollView {
            width: parent.width
            height: parent.height
            GridView {
                id: booksList
                model: bookModel
                clip: true
                cellWidth : thumbnailRequestedWidth + 5
                cellHeight: thumbnailRequestedHeight + 85
                onMovementEnded: {
                    if (atYEnd) {
                        console.log("Y end")
                    }
                }

                delegate:
                    CardItem {
                    cardWidth: thumbnailRequestedWidth
                    cardHeight: booksList.cellHeight
                    thumbnailHeight: thumbnailRequestedHeight
                    imagePath: "image://books/" + bookId
                    cardLabel: bookName
                    topCornerLabel: "CBR"
                    onCardClicked: {
                        booksList.currentIndex = index
                        currentBook = bookModel.get(booksList.currentIndex)
                        controller.goBookDetailView()
                    }
                }
            }
        }
    }
}
