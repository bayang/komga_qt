import QtQuick 2.14
import QtQuick.Controls 2.14
import QtGraphicalEffects 1.14
import QtQuick.Controls.Material 2.14

import komga_api 1.0

Item {

    property real thumbnailRequestedHeight: 230
    property real thumbnailRequestedWidth: 175

    Column {
        anchors.fill: parent
        Label {
            id: libraryText
            text: qsTr("In Library " + controller.ui_currentLibrary.ui_libraryName)
        }
        ScrollView {
            width: parent.width
            clip: true
            height: parent.height
            GridView {
                id: seriesList
                model: controller.ui_seriesModel
                clip: true
                cellWidth : thumbnailRequestedWidth + 5
                cellHeight: thumbnailRequestedHeight + 80
                onMovementEnded: {
                    if (atYEnd) {
                        console.log("Y end")
                        controller.nextSeriesPage()
                    }
                }
                delegate:
                    CardItem {
                        cardWidth: thumbnailRequestedWidth
                        cardHeight: seriesList.cellHeight
                        thumbnailHeight: thumbnailRequestedHeight
                        imagePath: "image://series/" + seriesId
                        cardLabel: seriesName
                        subLabel: seriesBookCount + " books"
                        topCornerLabel: seriesBookCount
                        onCardClicked: {
                            seriesList.currentIndex = index
                            controller.setSelectedSeries(seriesList.currentIndex)
                            controller.goBooksView()
                        }
                }
            }
        }
    }
}
