import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import komga_api 1.0
import assets 1.0

Item {
    property real lastNextPageCalledTime: 0
    ScrollView {
        clip: true
        anchors.fill: parent

        ColumnLayout {
            anchors.fill: parent

            Label {
                id: collectionsText
                text: controller.ui_collectionsName
                font.pointSize: Style.mediumTextSize
//                anchors.horizontalCenter: parent.horizontalCenter
                Layout.alignment: Qt.AlignHCenter
                topPadding: 20
            }

            GridView {
                id: collectionsList
                model: controller.ui_collectionModel
                clip: true
                Layout.fillHeight: true
                Layout.fillWidth: true
                cellWidth : Style.thumbnailRequestedWidth + 12
                cellHeight: Style.thumbnailRequestedHeight + 80
//                width: parent.width
//                height: parent.height - collectionsText.height
                Layout.preferredHeight: parent.height - collectionsText.height
                Layout.preferredWidth: parent.width
                Layout.minimumHeight: cellHeight
                Layout.minimumWidth: 100
                cacheBuffer: cellHeight
                bottomMargin: 10
                ScrollBar.vertical: ScrollBar { }
                onMovementEnded: {
                    if (atYEnd) {
                        var curTime = new Date().getTime();
                        if (curTime - lastNextPageCalledTime > 500) {
                            controller.nextCollectionsPage()
                        }
                        lastNextPageCalledTime = curTime
                    }
                }
                delegate:
                    CardItem {
                        cardWidth: Style.thumbnailRequestedWidth
                        cardHeight: collectionsList.cellHeight
                        thumbnailHeight: Style.thumbnailRequestedHeight
                        imagePath: "image://async/collection/" + collectionId
                        cardLabel: collectionName
                        subLabel: ""
                        topCornerLabel: ""
                        topCornerLabelFontSize: 12
                        topCornerLabelVisible: false
                        progressVisible: false
                        onCardClicked: {
                            collectionsList.currentIndex = index
                            controller.loadCollectionSeriesView(collectionId)
                            stack.push("qrc:/qml/seriesview.qml", {currentLibraryName: collectionName,
                                           currentSourceId: collectionId,
                                           sourceIsLibrary: false})
                        }
                }
            }
        }
    }
}
