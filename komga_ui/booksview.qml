import QtQuick 2.14
import QtQuick.Controls 2.14
import komga_api 1.0
import assets 1.0

Item {
    property real lastNextPageCalledTime: 0

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
                pointSize: Style.backArrowIconSize
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

        GridView {
            id: booksList
            height: parent.height - firstRow.height - booksViewBackButton.height
            model: controller.ui_bookModel
            clip: true
            cellWidth : Style.thumbnailRequestedWidth + 5
            cellHeight: Style.thumbnailRequestedHeight + 85
            width: parent.width
            cacheBuffer: 0
            bottomMargin: 20
            onMovementEnded: {
                if (atYEnd) {
                    var curTime = new Date().getTime();
                    if (curTime - lastNextPageCalledTime > 500) {
                        controller.nextBooksPage()
                    }
                    lastNextPageCalledTime = curTime
                }
            }
            delegate:
                CardItem {
                cardWidth: Style.thumbnailRequestedWidth
                cardHeight: booksList.cellHeight
                thumbnailHeight: Style.thumbnailRequestedHeight
                imagePath: "image://books/" + bookId
                cardLabel: bookName
                subLabel: bookPageCount + " pages\nsize: " + bookSize
                topCornerLabel: bookMediaType
                topCornerLabelFontSize: 11
                onCardClicked: {
                    booksList.currentIndex = index
                    controller.setSelectedBook(booksList.currentIndex)
                    controller.goBookDetailView()
                }
            }
        }
    }
}
