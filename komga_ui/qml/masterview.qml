import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import Qt.labs.settings 1.0
import komga_api 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 1280
    height: 760
    title: qsTr("Komga")

    Settings {
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
                        controller.setSelectedLibrary(controller.ui_defaultLibraryId)
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
        target: controller
        onGoSeriesView: contentFrame.replace("qrc:/qml/seriesview.qml")
    }

    Connections {
        target: controller
        onGoBooksView: contentFrame.push("qrc:/qml/booksview.qml")
    }

    Connections {
        target: controller
        onGoBookDetailView: contentFrame.push("qrc:/qml/bookdetailview.qml")
    }

    Connections {
        target: controller
        onGoBookReadView: contentFrame.push("qrc:/qml/bookreadview.qml")
    }

    Connections {
        target: controller.ui_networkInformer
        onErrorMessageChanged: {
            console.log("error" + errorMessage)
            errorMessageLabel.visible = true
            errorVisibilityTimer.restart()
        }
    }

    LibraryView {
        id: navColumn
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
    }


   StackView {
       id: contentFrame
       anchors.top: parent.top
       anchors.left: navColumn.right
       anchors.right: parent.right
       anchors.bottom: parent.bottom
       clip: true
       initialItem: "qrc:/qml/seriesview.qml"
       focus: true
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
