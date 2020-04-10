import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import komga_api 1.0

Pane {
    width: 300
//    anchors.top: parent.top
//    anchors.left: parent.left
//    anchors.bottom: parent.bottom

    Component.onCompleted: {
        libraryModel.fetchData()
        seriesModel.loadSeries(defaultLib.ui_libraryId)
    }

    Column   {
        spacing: 6
        anchors.fill: parent

        TextLink {
            onTextLinkClicked: {
                currentLibrary = defaultLib
                controller.goSeriesView()
            }
            textLinkLabel: "All libraries"
            textLinkLabelBold: true
            textLinkLabelSize: 20
        }

        ScrollView {
            width: parent.width
            ListView {
                id: librariesList
                model: libraryModel
                clip: true
                width: parent.width
                delegate:
                    TextLink {
                        onTextLinkClicked: {
                            librariesList.currentIndex = index
                            currentLibrary = libraryModel.get(librariesList.currentIndex)
                            controller.goSeriesView()
                        }
                        textLinkLabel: "Library: " + libraryName + ", root: " + libraryRoot  + " , id: " + libraryId
                }
            }
        }
    }
}
