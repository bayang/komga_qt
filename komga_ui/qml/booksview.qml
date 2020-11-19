import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import QtQml.Models 2.14
import komga_api 1.0
import assets 1.0

Item {
    property real lastNextPageCalledTime: 0
    property string currentSeriesId
    property string currentSeriesName
    property real currentSeriesBookCount
    property string currentSeriesMetadataStatus
    property string currentSeriesMetadataSummary
    property string currentSeriesMetadataPublisher
    property string parentType
    property var currentSeriesMetadataTagsList: []
    property var currentSeriesMetadataGenresList: []
    anchors.fill: parent
    anchors.leftMargin: 10

    Connections {
        target: controller.ui_bookModel.ui_booksFilter
        onFiltersChanged: {
            console.log("filter changed")
            controller.ui_bookModel.loadBooks(currentSeriesId)
        }
    }

    ScrollView {
        id: scroll
        clip: true
        anchors.fill: parent

        ColumnLayout {
            id: container
            anchors.fill: parent

            RowLayout {
                id: searchAndButtonRow
                Layout.bottomMargin: 15
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignHCenter
                Button {
                    id : booksViewBackButton
                    onClicked: {
                        if (contentFrame.depth > 1) {
                            contentFrame.pop()
                        }
                    }
                    visible: contentFrame.depth > 1
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
                    Layout.alignment: Qt.AlignTop
                    onSearchTriggered: {
                        controller.doSearch(searchTerm)
                    }
                }
                RoundButton {
                    id: readButton
                    visible: ism.hasSelection
                    Layout.alignment: Qt.AlignBottom
                    onClicked: {
                        controller.markRead(ism.selectedIndexes, "Book")
                        ism.clearSelection()
                    }
                    font {
                        family: Style.fontAwesomeSolid
                        pointSize: Style.backArrowIconSize
                    }
                    text: "\uf06e";
                    ToolTip.delay: 1000
                    ToolTip.timeout: 3000
                    ToolTip.visible: hovered
                    hoverEnabled: true
                    ToolTip.text: qsTr("Mark read")
                }
                RoundButton {
                    id: unreadButton
                    visible: ism.hasSelection
                    onClicked: {
                        controller.markRead(ism.selectedIndexes, "Book", false)
                        ism.clearSelection()
                    }
                    font {
                        family: Style.fontAwesomeSolid
                        pointSize: Style.backArrowIconSize
                    }
                    text: "\uf070";
                    ToolTip.delay: 1000
                    ToolTip.timeout: 3000
                    ToolTip.visible: hovered
                    hoverEnabled: true
                    ToolTip.text: qsTr("Mark unread")
                }
                RoundButton {
                    id: deselectButton
                    visible: ism.hasSelection
                    onClicked: {
                        ism.clearSelection()
                    }
                    font {
                        family: Style.fontAwesomeSolid
                        pointSize: Style.backArrowIconSize
                    }
                    text: "\uf05e";
                    ToolTip.delay: 1000
                    ToolTip.timeout: 3000
                    ToolTip.visible: hovered
                    hoverEnabled: true
                    ToolTip.text: qsTr("Deselect")
                }
                BooksFilterComponent {
                    Layout.preferredHeight: readButton.height
                    Layout.preferredWidth: readButton.width
                    Layout.alignment: Qt.AlignTop
                }
            }

            RowLayout {
                id : firstRow
                Layout.bottomMargin: 15
                Layout.fillWidth: true
                Image {
                    id: seriesDetailImage
                    source: "image://async/" + getSourceType(parentType) + "/" + currentSeriesId
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
                        BadgeLabel {
                            id: countBadge
                            font.pointSize: Style.smallMediumTextSize
                            text: currentSeriesBookCount
                        }
                    }
                    RowLayout {
                        Label {
                            text: qsTr("Status : ")
                            font.pointSize: Style.smallMediumTextSize
                        }
                        BadgeLabel {
                            id: seriesStatus
                            text: qsTr(currentSeriesMetadataStatus)
                            font.pointSize: Style.smallMediumTextSize
                        }
                    }
                    Label {
                        id: seriesSummary
                        text: qsTr(currentSeriesMetadataSummary)
                        font.pointSize: Style.smallMediumTextSize
                        Layout.bottomMargin: 15
                        visible: currentSeriesMetadataSummary != ''
                    }
                    RowLayout {
                        visible: currentSeriesMetadataPublisher != ''
                        Label {
                            text: qsTr("Publisher : ")
                            font.pointSize: Style.smallMediumTextSize
                        }
                        Label {
                            id: seriesPublisher
                            text: qsTr(currentSeriesMetadataPublisher)
                            font.pointSize: Style.smallMediumTextSize
                        }
                    }
                    RowLayout {
                        visible: currentSeriesMetadataGenresList.length > 0
                        Label {
                            text: qsTr("Genres : ")
                            font.pointSize: Style.smallMediumTextSize
                        }

                        Repeater {
                            model: currentSeriesMetadataGenresList
                            delegate: BadgeLabel {
                                text: modelData
                                font.pointSize: Style.smallMediumTextSize
                            }
                        }
                    }
                    RowLayout {
                        visible: currentSeriesMetadataTagsList.length > 0
                        Label {
                            text: qsTr("Tags : ")
                            font.pointSize: Style.smallMediumTextSize
                        }
                        Repeater {
                            model: currentSeriesMetadataTagsList
                            delegate: BadgeLabel {
                                text: modelData
                                font.pointSize: Style.smallMediumTextSize
                            }
                        }
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
                Layout.preferredHeight: scroll.height - searchAndButtonRow.height - firstRow.height
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
                    selectHandleVisible: true

                    itemSelected: ism.hasSelection && ism.isRowSelected(index,ism.model.index(-1,-1))
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
                                       currentBookSummary: bookSummary,
                                       currentBookSize: bookSize,
                                       currentBookShortMediaType: bookMediaType,
                                       currentBookUrl: bookUrl,
                                       standaloneView: false,
                                   })
                    }
                    onSelectClicked: {
                        ism.select(ism.model.index(index, 0), ItemSelectionModel.Toggle)
                    }
                }
            }
            ItemSelectionModel {
                id: ism
                model: controller.ui_bookModel
            }
        }
    }

    function getSourceType(type) {
        if (type === "ReadList") {
            return "readlist"
        }
        return "series"
    }
}
