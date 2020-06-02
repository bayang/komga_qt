import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

import assets 1.0

Item {
    id: root
    signal searchTriggered(string searchTerm)

    onSearchTriggered: dropDownPopup.open()

    ListModel {
        id: testModel
        ListElement {
            name: "book1"
        }
        ListElement {
            name: "book2"
        }
    }

    RowLayout {
           id: searchBar
           width: parent.width
           height: parent.height
           TextField {
               id: searchText
               placeholderText: qsTr("Search...")
               Layout.fillWidth: true
               onAccepted: root.searchTriggered(searchText.text)
               Popup {
                   id: dropDownPopup
                   parent: searchText

                   contentWidth: searchText.width
                   contentHeight: 500
                   padding: 1
                   background: Rectangle {
                       color: Style.backgroundColor
                   }
                   y: searchText.y + searchText.height

                   modal: false
                   focus: true
                   closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                   opacity: 0.8
                   enter: Transition {
                       ParallelAnimation {
                         NumberAnimation { target: dropDownPopup; property: "opacity"; from: 0.0; to: 1.0; duration: 300 }
                         NumberAnimation { target: dropDownPopup; property: "height"; from: 0.0; to: dropDownPopup.height; duration: 300 }
                       }
                   }
                   exit: Transition {
                       NumberAnimation { property: "opacity"; from: 1.0; to: 0.0; duration: 300 }
                   }
                   contentItem:
                       ListView {
                           id: dropDownList
//                           model: testModel
                           model: controller.ui_searchModel
                           clip: true
                           anchors.fill: parent
                           delegate:
                               Label {
                                   text: "named " + resultName + " id " + resultId + " type " + resultType
                           }
                       }
               }
           }
           Button {
               id: searchButton
               onClicked: root.searchTriggered(searchText.text)
               font {
                   family: Style.fontAwesome
                   pointSize: Style.backArrowIconSize
               }
               text : "\uf002"
           }

       }
}
