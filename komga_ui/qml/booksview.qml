import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
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
                source: "image://async/series/" + controller.ui_currentSeries.ui_seriesId
                sourceSize.height: 300
                sourceSize.width: -1
                fillMode: Image.PreserveAspectCrop
            }
            Column {
                leftPadding: 20

                RowLayout {
                    Label {
                        id: seriesText
                        text: qsTr(controller.ui_currentSeries.ui_seriesName)
                        font.pointSize: Style.mediumTextSize
                    }
                    Label {
                        id: countBadge
                        text: controller.ui_currentSeries.ui_seriesBooksCount
                        font.pointSize: Style.smallMediumTextSize
                        padding: 4
                        font.bold: true
                        background: Rectangle {
                            color: Style.hoverBorderColor
                            radius: 4
                        }
                    }
                }
                Label {
                    id: seriesStatus
                    text: qsTr("STATUS : " + controller.ui_currentSeries.ui_seriesMetadataStatus)
                    font.pointSize: Style.smallMediumTextSize
                }
            }
        }

        GridView {
            id: booksList
            height: parent.height - firstRow.height - booksViewBackButton.height
            model: controller.ui_bookModel
            clip: true
            cellWidth : Style.thumbnailRequestedWidth + 10
            cellHeight: Style.thumbnailRequestedHeight + 85
            width: parent.width
            cacheBuffer: cellHeight
            ScrollBar.vertical: ScrollBar { }
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
                imagePath: "image://async/book/" + bookId
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
