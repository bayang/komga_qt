import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import Qt.labs.settings 1.0
import komga_api 1.0
import assets 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 1280
    height: 760
    title: qsTr("Komga")
    property alias stack: contentFrame
    property alias leftNav: navColumn

    Settings {
        id: settings
        category: "layout"
        property alias x: window.x
        property alias y: window.y
        property alias width: window.width
        property alias height: window.height
    }

    menuBar: MenuBar {
            Menu {
                title: qsTr("&File")
                Action {
                    text: qsTr("&Settings...")
                    onTriggered: contentFrame.push("qrc:/qml/SettingsView.qml")
                }
                Action {
                    text: qsTr("&Refresh...")
                    onTriggered: {
                        controller.loadSeriesView(controller.ui_defaultLibraryId)
                        controller.refreshData()
                    }
                }
                MenuSeparator { }
                Action {
                    text: qsTr("&Quit")
                    onTriggered: Qt.quit()
                }
            }
        }

    Connections {
        target: controller.ui_networkInformer
        onErrorMessageChanged: {
            console.error("error " + errorMessage)
            errorMessageLabel.visible = true
            errorVisibilityTimer.restart()
        }
    }

    SplitView {
        id: splitView
        anchors.fill: parent

        LibraryView {
            id: navColumn
            SplitView.preferredWidth: Style.libraryPaneWidth
            SplitView.minimumWidth: Style.libraryPaneMinWidth
            SplitView.maximumWidth: Style.libraryPaneMaxWidth
        }

       StackView {
           id: contentFrame
           clip: true
           initialItem: "qrc:/qml/seriesview.qml"
           focus: true
       }
    }

   Label {
       text: "ERROR network is down"
       visible: ! controller.ui_networkInformer.ui_networkAccessible
   }

   Label {
       id: errorMessageLabel
       text: controller.ui_networkInformer.ui_networkError
       visible: false
       x: window.width / 2
       y: window.height - 100
   }

   Timer {
       id : errorVisibilityTimer
       interval: 2000
       repeat: false
       onTriggered: {
           errorMessageLabel.visible = false
       }
   }
}
