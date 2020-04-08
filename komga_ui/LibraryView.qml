import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import komga_api 1.0

Pane {
    width: 300
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.bottom: parent.bottom

//    Item {
//        anchors.fill: parent

    Component.onCompleted: {
        libraryModel.fetchData()
        seriesModel.loadSeries(defaultLib.ui_libraryId)
    }
//        Rectangle {
//            anchors.fill: parent

            Column {
                spacing: 6
                anchors.fill: parent

                Button {
                    id: myButton
                    text: "All libraries"
                    onClicked: {
                        currentLibrary = defaultLib
                        controller.goSeriesView()
                    }
                }

                ScrollView {
                    width: parent.width
                    ListView {
                        id: librariesList
                        model: libraryModel
                        clip: true
                        width: parent.width
                        delegate:
                            Item {
                                id: libraryDelegate
                                height: 40
                                width: parent.width
                                property bool currentlyHovered: false
                                Label {
                                    text: "Library: " + libraryName + ", root: " + libraryRoot  + " , id: " + libraryId
                                    wrapMode: Text.Wrap
                                    width: parent.width
                                    color: currentlyHovered ? "blue" : Material.foreground
                                }
                                MouseArea {
                                    id : libraryDelegateMouseArea
                                    width: parent.width
                                    height: parent.height
                                    hoverEnabled: true
                                    onClicked: {
                                        librariesList.currentIndex = index
                                        currentLibrary = libraryModel.get(librariesList.currentIndex)
                                        controller.goSeriesView()
                                    }
                                    onEntered: {
                                        cursorShape = Qt.PointingHandCursor
                                        currentlyHovered = true
                                    }
                                    onExited: {
                                        currentlyHovered = false
                                    }
                                }
                        }
                    }
                }
            }
//        }
//    }

}
