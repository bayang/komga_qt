import QtQuick 2.14
import QtQuick.Controls 2.14
import QtGraphicalEffects 1.14
import QtQuick.Controls.Material 2.14
import QtQuick.Controls.Material.impl 2.14
import QtGraphicalEffects 1.12

import komga_api 1.0

Item {
    anchors.fill: parent

    Component.onCompleted: {
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
            GridView {
                id: seriesList
                model: seriesModel
                clip: true
                cellWidth : thumbnailRequestedWidth + 5
                cellHeight: thumbnailRequestedHeight + 50
                delegate:
                    Item {
                        id: seriesDelegate
                        width: thumbnailRequestedWidth
                        height: seriesList.cellHeight - 10
                        property bool currentlyHovered: false

                        Rectangle {
                            id: seriesDelegateBackgound
                            anchors.horizontalCenter: seriesDelegate.horizontalCenter
                            width: parent.width
                            height: parent.height
                            Material.elevation: 20
                            color: Qt.lighter(Material.backgroundColor)
                            radius: 8


                            Column {
                                id: seriesDelegateColumn
                                spacing: 5
                                anchors.horizontalCenter: parent.horizontalCenter
                                width: parent.width

                                Image {
                                    id: seriesImage
                                    property bool rounded: true
                                    source: "image://series/" + seriesId
                                    sourceSize.height: thumbnailRequestedHeight
                                    sourceSize.width: thumbnailRequestedWidth
                                    fillMode: Image.PreserveAspectCrop
                                    anchors.horizontalCenter: seriesDelegateColumn.horizontalCenter
                                    layer.enabled: rounded
                                        layer.effect: OpacityMask {
                                            maskSource: Item {
                                                width: seriesImage.width
                                                height: seriesImage.height
                                                Rectangle {
                                                    anchors.centerIn: parent
                                                    width: seriesImage.width
                                                    height: seriesImage.height
                                                    radius: 8
                                                }
                                            }
                                        }
                                }
                                Label {
                                    text: seriesName + ", bookscount: " + seriesBookCount
                                    anchors.horizontalCenter: seriesDelegateColumn.horizontalCenter

                                }
                            }
                        }
                        MouseArea {
                            id : seriesDelegateMouseArea
                            width: parent.width
                            height: parent.height
                            hoverEnabled: true
                            onClicked: {
                                seriesList.currentIndex = index
                                currentSeries = seriesModel.get(seriesList.currentIndex)
                                controller.goBooksView()
                            }
                            onEntered: {
                                cursorShape = Qt.PointingHandCursor
                                currentlyHovered = true
                            }
                            onExited: {
                                currentlyHovered = false
                            }
                        }
                        Rectangle {
                            id: seriesDelegateRect
                            border.color: "lightsteelblue"
                            width: thumbnailRequestedWidth
                            height: parent.height
                            border.width: currentlyHovered ? 3 : 0
                            radius: 8
                            color: "transparent"
                            anchors.horizontalCenter: seriesDelegateBackgound.horizontalCenter
                        }

                }
            }
        }
    }


}
