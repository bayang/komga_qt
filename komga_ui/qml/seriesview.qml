import QtQuick 2.14
import QtQuick.Controls 2.14
import QtGraphicalEffects 1.14

import komga_api 1.0
import assets 1.0

Item {

    property real lastNextPageCalledTime: 0
    anchors.fill: parent
    anchors.leftMargin: 10

    Column {
        anchors.fill: parent
        SearchBar {
            id: searchBar
            width: parent.width > 600 ? 600 : parent.width
            height: 20
            anchors.horizontalCenter: parent.horizontalCenter
            onSearchTriggered: {
                controller.doSearch(searchTerm)
            }
        }

        Label {
            id: libraryText
            text: controller.ui_currentLibraryName
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
            height: parent.height - libraryText.height - searchBar.height
            cacheBuffer: cellHeight
            bottomMargin: 10
            ScrollBar.vertical: ScrollBar { }
            onMovementEnded: {
                if (atYEnd) {
                    var curTime = new Date().getTime();
                    if (curTime - lastNextPageCalledTime > 500) {
                        controller.nextSeriesPage()
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
                    onCardClicked: {
                        seriesList.currentIndex = index
                        controller.setSelectedSeries(seriesList.currentIndex)
                        controller.goBooksView()
                    }
            }
        }
    }
}
