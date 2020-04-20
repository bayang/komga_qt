import QtQuick 2.14
import QtQuick.Controls 2.14
import komga_api 1.0
import assets 1.0

Item {
    Column {
        anchors.fill: parent

        Button {
            id : booksViewBackButton
            onClicked: {
                if (contentFrame.depth > 0) {
                    contentFrame.pop()
                }
            }
            font {
                family: Style.fontAwesome
                pixelSize: Style.backArrowIconSize
            }
            text: "\uf060"
        }

        Row {
            id : firstRow
            height: 350
            bottomPadding: 0
            Image {
                id: seriesDetailImage
                source: "image://series/" + controller.ui_currentSeries.ui_seriesId
                sourceSize.height: 300
                sourceSize.width: -1
                fillMode: Image.PreserveAspectCrop
            }
            Column {
                leftPadding: 20
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
            height: parent.height - firstRow.height - booksViewBackButton.height
            clip: true
            bottomPadding: 5
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            GridView {
                id: booksList
                height: parent.height
                model: controller.ui_bookModel
                clip: true
                cellWidth : Style.thumbnailRequestedWidth + 5
                cellHeight: Style.thumbnailRequestedHeight + 85
                onMovementEnded: {
                    if (atYEnd) {
                        controller.nextBooksPage()
                    }
                }
                delegate:
                    CardItem {
                    cardWidth: Style.thumbnailRequestedWidth
                    cardHeight: booksList.cellHeight
                    thumbnailHeight: Style.thumbnailRequestedHeight
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
