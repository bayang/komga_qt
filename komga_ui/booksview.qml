import QtQuick 2.14
import QtQuick.Controls 2.14
import komga_api 1.0

Item {
    Component.onCompleted: {
        bookModel.loadBooks(currentSeries.ui_seriesId)
    }
    anchors.fill: parent

    Column {
        anchors.fill: parent
        Text {
            id: seriesText
            text: qsTr("In Series " + currentSeries.ui_seriesName)
        }
        ScrollView {
            width: parent.width
            GridView {
                id: booksList
                model: bookModel
                clip: true
                cellWidth : 300
                cellHeight: 375
                delegate:
                    Item {
                        id: booksDelegate
                        width: booksList.cellWidth - 10
                        height: booksList.cellHeight - 10
                        Column {
                            Text { text: "Book: " + bookName + ", book number: " + bookNumber.toString()  + " , id: " + bookId}
                            Image {
                                id: bookImage
                                source: "image://books/" + bookId
                                fillMode: Image.PreserveAspectFit
                            }
                            Button {
                                text: "read book " + bookName
                                onClicked: {
                                    booksList.currentIndex = index
                                    currentBook = bookModel.get(booksList.currentIndex)
//                                    controller.goSeriesView(currentLibrary)
                                }
                            }
                        }
                }
            }
        }

    }


}
