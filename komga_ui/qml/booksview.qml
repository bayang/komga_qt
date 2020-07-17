import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import komga_api 1.0
import assets 1.0

Item {
    property real lastNextPageCalledTime: 0
    property string currentSeriesId
    property string currentSeriesName
    property real currentSeriesBookCount
    property string currentSeriesMetadataStatus
//    anchors.fill: parent
    anchors.leftMargin: 10

    ScrollView {
        id: scroll
        clip: true
        anchors.fill: parent

        ColumnLayout {
            anchors.fill: parent

            RowLayout {
                id: searchAndButtonRow
                Layout.bottomMargin: 15
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter
                Button {
                    id : booksViewBackButton
                    onClicked: {
                        if (contentFrame.depth > 0) {
                            contentFrame.pop()
                        }
                    }
                    font {
                        family: Style.fontAwesomeSolid
                        pointSize: Style.backArrowIconSize
                    }
                    text: "\uf060"
                }
                SearchBar {
                    id: searchBar
                    Layout.preferredHeight: 20
                    Layout.preferredWidth: 600
                    onSearchTriggered: {
                        controller.doSearch(searchTerm)
                    }
                }
            }

            RowLayout {
                id : firstRow
                Layout.bottomMargin: 15
                Layout.fillWidth: true
                Image {
                    id: seriesDetailImage
                    source: "image://async/series/" + currentSeriesId
                    sourceSize.height: 270
                    sourceSize.width: -1
                    fillMode: Image.PreserveAspectCrop
                    Layout.preferredHeight: 320
                }
                ColumnLayout {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    Layout.fillWidth: true
                    RowLayout {

                        Label {
                            id: seriesText
                            text: qsTr(currentSeriesName)
                            font.pointSize: Style.mediumTextSize
                        }
                        Label {
                            id: countBadge
                            text: currentSeriesBookCount
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
                        text: qsTr("STATUS : " + currentSeriesMetadataStatus)
                        font.pointSize: Style.smallMediumTextSize
                        Layout.bottomMargin: 15
                    }
                    Label {
                        id: collectionsLabel
                        text: qsTr("Collections :")
                        font.pointSize: Style.smallMediumTextSize
                        visible: collectionsList.count > 0
                    }
                    ListView {
                            id: collectionsList
                            model: controller.ui_collectionModel
                            clip: true
                            visible: count > 0
                            Layout.fillWidth: true
                            Layout.minimumWidth: visible ? Style.smallCardWidth : 0;
                            Layout.minimumHeight: visible ? Style.smallCardHeight : 0;
                            orientation: ListView.Horizontal
                            spacing : 10
                            ScrollBar.horizontal: ScrollBar { }
                            delegate:
                                CardItem {
                                    cardWidth: Style.smallCardWidth
                                    cardHeight: Style.smallCardHeight
                                    thumbnailHeight: Style.smallCardThumbnailHeight
                                    imagePath: "image://async/collection/" + collectionId
                                    cardLabel: collectionName
                                    subLabel: ""
                                    topCornerLabel: collectionSize
                                    topCornerLabelFontSize: Style.smallTextSize
                                    topCornerLabelVisible: true
                                    progressVisible: false
                                    onCardClicked: {
                                        collectionsList.currentIndex = index
                                        controller.loadCollectionSeriesView(collectionId)
                                        stack.push("qrc:/qml/seriesview.qml", {currentLibraryName: collectionName,
                                                       currentSourceId: collectionId,
                                                       sourceIsLibrary: false,
                                                       backEnabled: true})
                                    }
                            }
                        }
                }
            }

            GridView {
                id: booksList
                model: controller.ui_bookModel
                clip: true
                cellWidth : Style.thumbnailRequestedWidth + 10
                cellHeight: Style.thumbnailRequestedHeight + 85
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.minimumHeight: cellHeight
                Layout.minimumWidth: 100
                Layout.preferredHeight: cellHeight * 2
                Layout.preferredWidth: parent.width
                cacheBuffer: cellHeight
                Layout.bottomMargin: 2
                onMovementEnded: {
                    if (atYEnd) {
                        var curTime = new Date().getTime();
                        if (curTime - lastNextPageCalledTime > 500) {
                            controller.nextBooksPage(currentSeriesId)
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
                    topCornerLabel: "✓"
                    topCornerLabelFontSize: Style.mediumTextSize
                    topCornerLabelVisible: bookCompleted
                    progressVisible: bookPageReached > 0 && ! bookCompleted
                    progressValue: bookPageReached/bookPageCount
                    progressHeight: 10
                    onCardClicked: {
                        booksList.currentIndex = index
                        controller.setSelectedBookIdx(booksList.currentIndex)
                        stack.push("qrc:/qml/bookdetailview.qml", {
                                       currentBookId: bookId,
                                       currentBookPageReached: bookPageReached,
                                       currentBookPageCount: bookPageCount,
                                       currentBookCompleted: bookCompleted,
                                       currentBookMetadataTitle: bookTitle,
                                       currentBookWriters: bookWriters,
                                       currentBookPencillers: bookPencillers,
                                       currentBookColorists: bookColorists,
                                       currentBookPublisher : bookPublisher,
                                       currentBookSummary: bookSummary,
                                       currentBookSize: bookSize,
                                       currentBookShortMediaType: bookMediaType,
                                       currentBookUrl: bookUrl,
                                       standaloneView: false
                                   })
                    }
                }
            }
        }
    }
}
