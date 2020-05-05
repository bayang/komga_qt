import QtQuick 2.14
import QtQuick.Controls 2.14
import QtGraphicalEffects 1.14

import komga_api 1.0
import assets 1.0

Item {

    property real lastNextPageCalledTime: 0

//    Connections {
//        target: controller.ui_seriesModel
//        onRefresh: {
//            console.log("refresh called")
//            seriesList.forceLayout()
//        }
//    }

    Column {
        anchors.fill: parent
        Label {
            id: libraryText
            text: controller.ui_currentLibraryName
            font.pointSize: Style.mediumTextSize
            anchors.horizontalCenter: parent.horizontalCenter
        }
        GridView {
            id: seriesList
            model: controller.ui_seriesModel
            clip: true
            cellWidth : Style.thumbnailRequestedWidth + 12
            cellHeight: Style.thumbnailRequestedHeight + 80
            width: parent.width
            height: parent.height
            cacheBuffer: cellHeight
            bottomMargin: 20
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
                    topCornerLabel: seriesBookCount
                    topCornerLabelFontSize: 12
                    onCardClicked: {
                        seriesList.currentIndex = index
                        controller.setSelectedSeries(seriesList.currentIndex)
                        controller.goBooksView()
                    }
            }
        }
    }
}
