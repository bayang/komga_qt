import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

Item {
    id: root
    signal searchTriggered(string searchTerm)

    RowLayout {
           id: searchBar
           width: parent.width
           height: parent.height
//           Behavior on opacity { NumberAnimation{} }
//           visible: opacity ? true : false
           TextField {
               id: searchText
//               Behavior on opacity { NumberAnimation{} }
//               visible: opacity ? true : false
//               property bool ignoreTextChange: false
               placeholderText: qsTr("Search...")
               Layout.fillWidth: true
//               onTextChanged: {
//                   if (!ignoreTextChange)
//                       searchTextChanged(text)
//               }
               onAccepted: root.searchTriggered(searchText.text)
           }
           Button {
               id: searchButton
               icon.name: "system-search"
               icon.color: white
//               icon.Source:  "../../resources/search.png"
               onClicked: root.searchTriggered(searchText.text)
               font {
                   family: Style.fontAwesome
                   pointSize: Style.backArrowIconSize
               }
               text : "\uf002"
           }

       }

//    function doSearch(text) {
//        console.log("searched " + text)
//    }

}
