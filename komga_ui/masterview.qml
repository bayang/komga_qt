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
    property Library currentLibrary
    property Series currentSeries
    property Book currentBook
    Library {id: defaultLib; ui_libraryId:-1; ui_libraryName: "All libraries"}

    Component.onCompleted: {
        currentLibrary = defaultLib
    }

    Connections {
        target: controller
        onGoSeriesView: contentFrame.replace("qrc:/seriesview.qml")
    }

    Connections {
        target: controller
        onGoBooksView: contentFrame.replace("qrc:/booksview.qml")
    }

    LibraryView {

        id: navColumn

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
