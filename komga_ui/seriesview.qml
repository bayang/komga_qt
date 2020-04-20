import QtQuick 2.14
import QtQuick.Controls 2.14
import QtGraphicalEffects 1.14
import QtQuick.Controls.Material 2.14

import komga_api 1.0
import assets 1.0

Item {

    Column {
        anchors.fill: parent
        Label {
            id: libraryText
            text: qsTr("In Library " + controller.ui_currentLibraryName)

        }
        ScrollView {
            width: parent.width
            clip: true
            height: parent.height
            bottomPadding: 10
            GridView {
                id: seriesList
                model: controller.ui_seriesModel
                clip: true
                cellWidth : Style.thumbnailRequestedWidth + 5
                cellHeight: Style.thumbnailRequestedHeight + 80
                onMovementEnded: {
                    if (atYEnd) {
                        controller.nextSeriesPage()
                    }
                }
                delegate:
                    CardItem {
                        cardWidth: Style.thumbnailRequestedWidth
                        cardHeight: seriesList.cellHeight
                        thumbnailHeight: Style.thumbnailRequestedHeight
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
