import QtQuick 2.14
import QtQuick.Controls 2.14
import QtGraphicalEffects 1.14
import QtQuick.Controls.Material 2.14

import komga_api 1.0

Item {

    Component.onCompleted: {
        if (currentLibrary == null) {
            currentLibrary = defaultLib
        }

        seriesModel.loadSeries(currentLibrary.ui_libraryId)
    }
    property real thumbnailRequestedHeight: 230
    property real thumbnailRequestedWidth: 175

    Column {
        anchors.fill: parent
        Label {
            id: libraryText
            text: qsTr("In Library " + currentLibrary.ui_libraryName)
        }
        ScrollView {
            width: parent.width
            clip: false
            height: parent.height
            GridView {
                id: seriesList
                model: seriesModel
                clip: true
                cellWidth : thumbnailRequestedWidth + 5
                cellHeight: thumbnailRequestedHeight + 50
                onMovementEnded: {
                    if (atYEnd) {
                        console.log("Y end")
                    }
                }
                delegate:
                    CardItem {
                        cardWidth: thumbnailRequestedWidth
                        cardHeight: seriesList.cellHeight
                        thumbnailHeight: thumbnailRequestedHeight
                        imagePath: "image://series/" + seriesId
                        cardLabel: seriesName
                        topCornerLabel: seriesBookCount
                        onCardClicked: {
                            seriesList.currentIndex = index
                            currentSeries = seriesModel.get(seriesList.currentIndex)
                            controller.goBooksView()
                        }
                }
            }
        }
    }
}
