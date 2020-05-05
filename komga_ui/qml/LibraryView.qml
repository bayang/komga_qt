import QtQuick 2.14
import QtQuick.Controls 2.14
import komga_api 1.0
import assets 1.0

Pane {
//    width: Style.libraryPaneWidth

    Component.onCompleted: {
        controller.setSelectedLibrary(controller.ui_defaultLibraryId)
        controller.refreshData()
    }

    Column   {
        spacing: 6
        anchors.fill: parent

        TextLink {
            onTextLinkClicked: {
                controller.setSelectedLibrary(controller.ui_defaultLibraryId)
                if (contentFrame.depth > 1) {
                    controller.goSeriesView()
                }
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
                            controller.setSelectedLibrary(librariesList.currentIndex)
                            if (contentFrame.depth > 1) {
                                controller.goSeriesView()
                            }
                        }
                        textLinkLabel: libraryName
                }
            }
        }
        TextLink {
            onTextLinkClicked: {
                controller.setSelectedLibrary(controller.ui_newSeriesId)
                if (contentFrame.depth > 1) {
                    controller.goSeriesView()
                }
            }
            textLinkLabel: "New Series"
            textLinkLabelBold: true
            textLinkLabelSize: Style.mediumTextSize
        }
        TextLink {
            onTextLinkClicked: {
                controller.setSelectedLibrary(controller.ui_updatedSeriesId)
                if (contentFrame.depth > 1) {
                    controller.goSeriesView()
                }
            }
            textLinkLabel: "Updated Series"
            textLinkLabelBold: true
            textLinkLabelSize: Style.mediumTextSize
        }
        TextLink {
            onTextLinkClicked: {
                controller.setSelectedLibrary(controller.ui_latestSeriesId)
                if (contentFrame.depth > 1) {
                    controller.goSeriesView()
                }
            }
            textLinkLabel: "Latest Series"
            textLinkLabelBold: true
            textLinkLabelSize: Style.mediumTextSize
        }
    }
}
