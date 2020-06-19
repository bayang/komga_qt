import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

import assets 1.0

Item {
    id: root
    signal searchTriggered(string searchTerm)
    onSearchTriggered: dropDownPopup.open()

    RowLayout {
        id: searchBar
        width: parent.width
        height: parent.height
        Layout.alignment: Qt.AlignVCenter
        TextField {
            id: searchText
            placeholderText: qsTr("Search...")
            Layout.fillWidth: true
            font.pointSize: Style.smallTextSize
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
                    model: controller.ui_searchModel
                    clip: true
                    spacing: 10
                    leftMargin: 15
                    width: parent.width - 20
                    focus: true
                    section.property: "resultType"
                    section.criteria: ViewSection.FullString
                    section.delegate:  Component {
                        id: sectionHeading
                        Text {
                            text: section
                            font.bold: true
                            font.pixelSize: Style.mediumTextSize
                            width: dropDownList.width
                            color: Style.accentColor
                        }
                    }
                    delegate: Item {
                        id: searchResultDelegate
                        width: dropDownList.width
                        height: searchResultImage.implicitHeight
                        RowLayout {
                            anchors.fill: parent
                            Image {
                                id: searchResultImage
                                source: "image://async/" + getSourceType(resultType) + "/" + resultId
                                sourceSize.height: 50
                                sourceSize.width: -1
                                fillMode: Image.PreserveAspectCrop
                            }
                            Label {
                                id: innerLabel
                                width: parent.width
                                elide: Text.ElideRight
                                text: resultName
                                Layout.alignment: Qt.AlignLeft
                                Layout.fillWidth: true
                                Layout.leftMargin: 5
                            }
                        }
                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: {
//                                console.log("clicked index " + index)
                                controller.setSearchResult(index)
                                dropDownPopup.close()
                                searchText.text = ""
                            }
                            onEntered: {
                                cursorShape = Qt.PointingHandCursor
                            }
                        }
                    }
                }
            }
        }
        Button {
            id: searchButton
            onClicked: root.searchTriggered(searchText.text)
            font {
                family: Style.fontAwesomeSolid
                pointSize: Style.smallMediumTextSize
            }
            text : "\uf002"
        }
    }
    function getSourceType(type) {
        if (type === "Books") {
            return "book"
        }
        return "series"
    }
}


