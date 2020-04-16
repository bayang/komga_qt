import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import komga_api 1.0

ApplicationWindow {

    visible: true
    width: 1280
    height: 760
    title: qsTr("Komga")

    Connections {
        target: controller
        onGoSeriesView: contentFrame.replace("qrc:/seriesview.qml")
    }

    Connections {
        target: controller
        onGoBooksView: contentFrame.push("qrc:/booksview.qml")
    }

    Connections {
        target: controller
        onGoBookDetailView: contentFrame.push("qrc:/bookdetailview.qml")
    }

    Connections {
        target: controller
        onGoBookReadView: contentFrame.push("qrc:/bookreadview.qml")
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
       initialItem: "qrc:/seriesview.qml"
   }
}
