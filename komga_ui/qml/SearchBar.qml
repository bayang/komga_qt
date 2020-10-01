import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

import komga_api 1.0
import assets 1.0

Item {
    id: root
    signal searchTriggered(string searchTerm)
    onSearchTriggered: dropDownPopup.open()
    property alias searchBottom: searchBar.bottom

    RowLayout {
        id: searchBar
        anchors.fill: parent
        TextField {
            id: searchText
            placeholderText: qsTr("Search...")
            Layout.fillWidth: true
            font.pointSize: Style.smallTextSize
            onAccepted: root.searchTriggered(searchText.text)
            Popup {
                id: dropDownPopup
                parent: searchText
                contentWidth: searchText.width
                contentHeight: 500
                padding: 1
                background: Rectangle {
                    color: Style.backgroundColor
                }
                y: searchText.y + searchText.height
                modal: false
                focus: true
                closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                opacity: 0.8
                enter: Transition {
                    ParallelAnimation {
                        NumberAnimation { target: dropDownPopup; property: "opacity"; from: 0.0; to: 1.0; duration: 300 }
                        NumberAnimation { target: dropDownPopup; property: "height"; from: 0.0; to: dropDownPopup.height; duration: 300 }
                    }
                }
                exit: Transition {
                    NumberAnimation { property: "opacity"; from: 1.0; to: 0.0; duration: 300 }
                }
                contentItem:
                    ListView {
                    id: dropDownList
                    model: controller.ui_searchModel
                    clip: true
                    spacing: 10
                    leftMargin: 15
                    width: parent.width - 20
                    focus: true
                    highlight: Rectangle {
                        color: "transparent"
                        border.width: 3
                        border.color: Style.accentColor
                    }
                    Keys.onReturnPressed: {
                        if (dropDownList.activeFocus) {
                            currentItem.mouseA.clicked(null)
                        }
                    }
                    section.property: "resultType"
                    section.criteria: ViewSection.FullString
                    section.delegate:  Component {
                        id: sectionHeading
                        Text {
                            text: section
                            font.bold: true
                            font.pixelSize: Style.mediumTextSize
                            width: dropDownList.width
                            color: Style.accentColor
                        }
                    }
                    delegate: Item {
                        id: searchResultDelegate
                        width: dropDownList.width
                        height: searchResultImage.implicitHeight
                        property alias mouseA: resultMouseArea
                        RowLayout {
                            anchors.fill: parent
                            Image {
                                id: searchResultImage
                                source: "image://async/" + getSourceType(resultType) + "/" + resultId
                                sourceSize.height: 50
                                sourceSize.width: -1
                                fillMode: Image.PreserveAspectCrop
                            }
                            Label {
                                id: innerLabel
                                width: parent.width
                                elide: Text.ElideRight
                                text: resultName
                                Layout.alignment: Qt.AlignLeft
                                Layout.fillWidth: true
                                Layout.leftMargin: 5
                            }
                        }
                        MouseArea {
                            id: resultMouseArea
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: {
                                dropDownList.currentIndex = index
                                if (resultType === "Books") {
                                    stack.push("qrc:/qml/bookdetailview.qml", {
                                                   currentBookId: resultBook.ui_bookId,
                                                   currentBookPageReached: resultBook.ui_bookPageReached,
                                                   currentBookPageCount: resultBook.ui_bookPagesCount,
                                                   currentBookCompleted: resultBook.ui_bookCompleted,
                                                   currentBookMetadataTitle: resultBook.ui_bookMetadata.ui_metadataTitle,
                                                   currentBookWriters: resultBook.ui_bookMetadata.ui_metadataWriters,
                                                   currentBookPencillers: resultBook.ui_bookMetadata.ui_metadataPencillers,
                                                   currentBookColorists: resultBook.ui_bookMetadata.ui_metadataColorists,
                                                   currentBookSummary: resultBook.ui_bookMetadata.ui_metadataSummary,
                                                   currentBookSize: resultBook.ui_bookSize,
                                                   currentBookShortMediaType: resultBook.ui_bookShortMediaType,
                                                   currentBookUrl: resultBook.ui_bookUrl,
                                                   standaloneView: true
                                               })
                                }
                                else if (resultType === "Collections") {
                                    controller.loadCollectionSeriesView(resultCollection.ui_collectionId)
                                    stack.push("qrc:/qml/seriesview.qml", {currentLibraryName: resultCollection.ui_collectionName,
                                                   currentSourceId: resultCollection.ui_collectionId,
                                                   sourceIsLibrary: false})
                                }
                                else if (resultType === "Readlist") {
                                    controller.loadReadListBooksView(resultReadList.ui_readListId)
                                    console.log("read list size " + resultReadList.ui_readListBooksSize)
                                    stack.push("qrc:/qml/booksview.qml", {
                                                   currentSeriesId: resultReadList.ui_readListId,
                                                   currentSeriesName: resultReadList.ui_readListName,
                                                   currentSeriesBookCount: resultReadList.ui_readListBooksSize,
                                                   currentSeriesMetadataStatus: "",
                                                   parentType: "ReadList"
                                               }
                                           )
                                }
                                else {
                                    controller.loadBooksView(resultSeries.ui_seriesId)
                                    stack.replace("qrc:/qml/booksview.qml", {
                                                   currentSeriesId: resultSeries.ui_seriesId,
                                                   currentSeriesName: resultSeries.ui_seriesName,
                                                   currentSeriesBookCount: resultSeries.ui_seriesBooksCount,
                                                   currentSeriesMetadataStatus: resultSeries.ui_seriesMetadataStatus
                                               })
                                }
                                controller.resetSearch()
                                dropDownPopup.close()
                                searchText.text = ""
                            }
                            onEntered: {
                                cursorShape = Qt.PointingHandCursor
                            }
                        }
                    }
                }
            }
        }
        RoundButton {
            id: searchButton
            onClicked: root.searchTriggered(searchText.text)
            font {
                family: Style.fontAwesomeSolid
                pointSize: Style.smallMediumTextSize
            }
            text : "\uf002"
        }
    }

    function getSourceType(type) {
        if (type === "Books") {
            return "book"
        }
        else if (type === "Collections") {
            return "collection"
        }
        else if (type === "Readlist") {
            return "readlist"
        }
        return "series"
    }
}
