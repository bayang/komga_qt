import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQml.Models 2.14
import QtGraphicalEffects 1.14

import komga_api 1.0
import assets 1.0

Item {
    id: seriesRoot
    property real lastNextPageCalledTime: 0
    property string currentLibraryName
    property string currentSourceId
    property bool sourceIsLibrary: true;
    property bool backEnabled: false;
    anchors.leftMargin: 10
    signal deselect(int idx);

    Connections {
        target: controller.ui_seriesModel
        onFiltersApplied: {
            console.log("filter applied ")
            controller.ui_seriesModel.filterSeries(seriesRoot.currentSourceId)
        }
    }

    Column {
        anchors.fill: parent
        Row {
            id: searchRow
            width: parent.width
            height: Math.max(searchBar.height, readButton.height)
            SearchBar {
                id: searchBar
                width: parent.width > 600 ? 600 : parent.width
                height: 20
                anchors.centerIn: parent
                anchors.verticalCenter: parent.verticalCenter
                onSearchTriggered: {
                    controller.doSearch(searchTerm)
                }
            }
            Row {
                anchors.right: parent.right
                RoundButton {
                    id: readButton
                    visible: ism.hasSelection
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        controller.markRead(ism.selectedIndexes, "Series")
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
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        controller.markRead(ism.selectedIndexes, "Series", false)
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
                    anchors.verticalCenter: parent.verticalCenter
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
                SeriesFilterComponent {
                    width: readButton.width
                    height: readButton.height
                    anchors.verticalCenter: parent.verticalCenter
                }

            }

        }

        Label {
            id: libraryText
            text: currentLibraryName
            font.pointSize: Style.mediumTextSize
            anchors.horizontalCenter: parent.horizontalCenter
            topPadding: 20
        }

        GridView {
            id: seriesList
            model: controller.ui_seriesModel
            clip: true
            cellWidth : Style.thumbnailRequestedWidth + 12
            cellHeight: Style.thumbnailRequestedHeight + 80
            width: parent.width
            height: parent.height - libraryText.height - searchRow.height
            cacheBuffer: cellHeight
            bottomMargin: 10
            ScrollBar.vertical: ScrollBar { }
            onMovementEnded: {
                if (atYEnd) {
                    var curTime = new Date().getTime();
                    if (curTime - lastNextPageCalledTime > 500) {
                        if (sourceIsLibrary) {
                            controller.nextSeriesPage(currentSourceId)
                        }
                        else {
                            controller.nextCollectionsSeriesPage(currentSourceId)
                        }
                    }
                    lastNextPageCalledTime = curTime
                }
            }
            delegate:
                CardItem {
                    cardWidth: Style.thumbnailRequestedWidth
                    cardHeight: seriesList.cellHeight
                    thumbnailHeight: Style.thumbnailRequestedHeight
                    imagePath: "image://async/series/" + seriesId
                    cardLabel: seriesName
                    subLabel: seriesBookCount + " books"
                    topCornerLabel: seriesBookInProgressCount + "/" + seriesBookUnreadCount
                    topCornerLabelFontSize: 12
                    topCornerLabelVisible: seriesBookUnreadCount > 0 || seriesBookInProgressCount > 0
                    progressVisible: false
                    selectHandleVisible: true

                    itemSelected: ism.hasSelection && ism.isRowSelected(index,ism.model.index(-1,-1))
                    onCardClicked: {
                        seriesList.currentIndex = index
                        controller.loadBooksView(seriesId)
                        controller.loadSeriesCollections(seriesId)
                        stack.push("qrc:/qml/booksview.qml", {
                                       currentSeriesId: seriesId,
                                       currentSeriesName: seriesName,
                                       currentSeriesBookCount: seriesBookCount,
                                       currentSeriesMetadataStatus: seriesMetadataStatus,
                                       currentSeriesMetadataSummary: seriesMetadataSummary,
                                       currentSeriesMetadataPublisher: seriesMetadataPublisher,
                                       currentSeriesMetadataTagsList: seriesMetadataTagsList,
                                       currentSeriesMetadataGenresList: seriesMetadataGenresList
                                   }
                               )
                    }
                    onSelectClicked: {
                        ism.select(ism.model.index(index, 0), ItemSelectionModel.Toggle)
                    }
            }
        }
        ItemSelectionModel {
            id: ism
            model: controller.ui_seriesModel
        }
    }
}
