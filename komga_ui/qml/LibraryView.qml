import QtQuick 2.14
import QtQuick.Controls 2.14
import komga_api 1.0
import assets 1.0

Pane {
    Component.onCompleted: {
        controller.refreshData()
        stack.push("qrc:/qml/seriesview.qml", {currentLibraryName: controller.ui_defaultLibraryName, currentSourceId: controller.ui_defaultLibraryId})
    }

    Column   {
        spacing: 6
        anchors.fill: parent

        TextLink {
            onTextLinkClicked: {
                controller.loadSeriesView(controller.ui_defaultLibraryId)
                stack.replace("qrc:/qml/seriesview.qml", {currentLibraryName: controller.ui_defaultLibraryName, currentSourceId: controller.ui_defaultLibraryId})
            }
            textLinkLabel: controller.ui_defaultLibraryName
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
                            controller.loadSeriesView(libraryId)
                            stack.replace("qrc:/qml/seriesview.qml", {currentLibraryName: libraryName, currentSourceId: libraryId})
                        }
                        textLinkLabel: libraryName
                }
            }
        }
        TextLink {
            onTextLinkClicked: {
                controller.loadBooksView(controller.ui_readingBooksId)
                stack.replace("qrc:/qml/BooksListView.qml", {currentViewName: controller.ui_readingBooksName})
            }
            textLinkLabel: controller.ui_readingBooksName
            textLinkLabelSize: Style.mediumTextSize
        }
        TextLink {
            onTextLinkClicked: {
                controller.loadCollectionsView()
                stack.replace("qrc:/qml/CollectionsView.qml")
            }
            textLinkLabel: controller.ui_collectionsName
            textLinkLabelSize: Style.mediumTextSize
        }
        TextLink {
            onTextLinkClicked: {
                controller.loadSeriesView(controller.ui_newSeriesId)
                stack.replace("qrc:/qml/seriesview.qml", {currentLibraryName: controller.ui_newSeriesName, currentSourceId: controller.ui_newSeriesId})
            }
            textLinkLabel: controller.ui_newSeriesName
            textLinkLabelSize: Style.mediumTextSize
        }
        TextLink {
            onTextLinkClicked: {
                controller.loadSeriesView(controller.ui_updatedSeriesId)
                stack.replace("qrc:/qml/seriesview.qml", {currentLibraryName: controller.ui_updatedSeriesName, currentSourceId: controller.ui_updatedSeriesId})
            }
            textLinkLabel: controller.ui_updatedSeriesName
            textLinkLabelSize: Style.mediumTextSize
        }
        TextLink {
            onTextLinkClicked: {
                controller.loadSeriesView(controller.ui_latestSeriesId)
                stack.replace("qrc:/qml/seriesview.qml", {currentLibraryName: controller.ui_latestSeriesName, currentSourceId: controller.ui_latestSeriesId})
            }
            textLinkLabel: controller.ui_latestSeriesName
            textLinkLabelSize: Style.mediumTextSize
        }
        TextLink {
            onTextLinkClicked: {
                controller.loadBooksView(controller.ui_latestBooksId)
                stack.replace("qrc:/qml/BooksListView.qml", {currentViewName: controller.ui_latestBooksName})
            }
            textLinkLabel: controller.ui_latestBooksName
            textLinkLabelSize: Style.mediumTextSize
        }
    }
}
