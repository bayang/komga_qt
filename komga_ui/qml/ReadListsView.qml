import QtQuick 2.14
import QtQuick.Controls 2.14
import komga_api 1.0
import assets 1.0

Item {
    id: root
    property real lastNextPageCalledTime: 0

        Column {
            id: readListsColumn
            anchors.fill: parent
            Label {
                id: readListsText
                text: controller.ui_readListsName
                font.pointSize: Style.mediumTextSize
                anchors.horizontalCenter: parent.horizontalCenter
            }

            GridView {
                id: readListsList
                model: controller.ui_readListsModel
                clip: true
                cellWidth : Style.thumbnailRequestedWidth + 12
                cellHeight: Style.thumbnailRequestedHeight + 80
                width: parent.width
                height: parent.height - readListsText.height
                cacheBuffer: cellHeight
                bottomMargin: 10
                ScrollBar.vertical: ScrollBar { }
                onMovementEnded: {
                    if (atYEnd) {
                        var curTime = new Date().getTime();
                        if (curTime - lastNextPageCalledTime > 500) {
                            controller.nextReadListsPage()
                        }
                        lastNextPageCalledTime = curTime
                    }
                }
                delegate:
                    CardItem {
                        cardWidth: Style.thumbnailRequestedWidth
                        cardHeight: readListsList.cellHeight
                        thumbnailHeight: Style.thumbnailRequestedHeight
                        imagePath: "image://async/readlist/" + readListId
                        cardLabel: readListName
                        subLabel: ""
                        topCornerLabel: ""
                        topCornerLabelFontSize: 12
                        topCornerLabelVisible: false
                        progressVisible: false
                        onCardClicked: {
                            readListsList.currentIndex = index
                            controller.loadReadListBooksView(readListId)
                            stack.push("qrc:/qml/booksview.qml", {
                                           currentSeriesId: readListId,
                                           currentSeriesName: readListName,
                                           currentSeriesBookCount: readListSize,
                                           currentSeriesMetadataStatus: "",
                                           parentType: "ReadList"
                                       }
                                   )
                        }
                }
            }
        }

}
