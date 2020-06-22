import QtQuick 2.14
import QtQuick.Controls 2.14
import komga_api 1.0
import assets 1.0

Pane {
    Component.onCompleted: {
//        controller.setSelectedLibrary(controller.ui_defaultLibraryId)
        controller.refreshData()
        stack.push("qrc:/qml/seriesview.qml", {currentLibraryName: controller.ui_defaultLibraryName, currentLibraryId: controller.ui_defaultLibraryId})
    }

    Column   {
        spacing: 6
        anchors.fill: parent

        TextLink {
            onTextLinkClicked: {
//                controller.setSelectedLibrary(controller.ui_defaultLibraryId)
                if (contentFrame.depth > 1) {
                    controller.goSeriesView(controller.ui_defaultLibraryId)
                }
                stack.replace("qrc:/qml/seriesview.qml", {currentLibraryName: controller.ui_defaultLibraryName, currentLibraryId: controller.ui_defaultLibraryId})
            }
            textLinkLabel: "All libraries"
            textLinkLabelBold: true
            textLinkLabelSize: 20
        }

        ScrollView {
            width: parent.width
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ListView {
                id: librariesList
                model: controller.ui_libraryModel
                clip: true
                width: parent.width
                delegate:
                    TextLink {
                        onTextLinkClicked: {
                            librariesList.currentIndex = index
//                            controller.setSelectedLibrary(librariesList.currentIndex)
                            if (contentFrame.depth > 1) {
                                controller.goSeriesView(libraryId)
                            }
                            stack.replace("qrc:/qml/seriesview.qml", {currentLibraryName: libraryName, currentLibraryId: libraryId})
                        }
                        textLinkLabel: libraryName
                }
            }
        }
        TextLink {
            onTextLinkClicked: {
//                controller.setSelectedLibrary(controller.ui_newSeriesId)
                if (contentFrame.depth > 1) {
                    controller.goSeriesView(controller.ui_newSeriesId)
                }
                stack.replace("qrc:/qml/seriesview.qml", {currentLibraryName: "New Series", currentLibraryId: controller.ui_newSeriesId})
            }
            textLinkLabel: "New Series"
            textLinkLabelSize: Style.mediumTextSize
        }
        TextLink {
            onTextLinkClicked: {
//                controller.setSelectedLibrary(controller.ui_updatedSeriesId)
                if (contentFrame.depth > 1) {
                    controller.goSeriesView(controller.ui_updatedSeriesId)
                }
                stack.replace("qrc:/qml/seriesview.qml", {currentLibraryName: "Updated Series", currentLibraryId: controller.ui_updatedSeriesId})
            }
            textLinkLabel: "Updated Series"
            textLinkLabelSize: Style.mediumTextSize
        }
        TextLink {
            onTextLinkClicked: {
//                controller.setSelectedLibrary(controller.ui_latestSeriesId)
                if (contentFrame.depth > 1) {
                    controller.goSeriesView(controller.ui_latestSeriesId)
                }
                stack.replace("qrc:/qml/seriesview.qml", {currentLibraryName: "Latest Series", currentLibraryId: controller.ui_latestSeriesId})
            }
            textLinkLabel: "Latest Series"
            textLinkLabelSize: Style.mediumTextSize
        }
    }
}
