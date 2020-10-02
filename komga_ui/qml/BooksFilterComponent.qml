import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

import komga_api 1.0
import assets 1.0

Item {
    id: root

    RoundButton {
        id: filtersButton
        anchors.fill: parent
        onClicked: {
            console.log("open")
            popup.open()
        }
        font {
            family: Style.fontAwesomeSolid
            pointSize: Style.backArrowIconSize
        }
        text : "\uf0b0";
    }

    Popup {
        id: popup
        y: parent.y + filtersButton.height
        ScrollView {
            id: scroll
            clip: true
            anchors.fill: parent
            ColumnLayout  {
                id:column
                anchors.fill: parent
                CollapsibleItem {
                    id: readStatusGroup
                    titleText: qsTr("Read Status")
                    Layout.fillWidth: true
                    Layout.bottomMargin: 10
                    boxContent: ColumnLayout {
                        anchors.fill: parent
                        CheckBox {
                            property string value: "UNREAD"
                            text: "Unread"
                            onCheckedChanged: {
                                if (checked){
                                    controller.ui_bookModel.addReadStatusFilter(this.value)
                                }
                                else {
                                    controller.ui_bookModel.removeReadStatusFilter(this.value)
                                }
                            }
                        }
                        CheckBox {
                            property string value: "READ"
                            text: "Read"
                            onCheckedChanged: {
                                if (checked){
                                    controller.ui_bookModel.addReadStatusFilter(this.value)
                                }
                                else {
                                    controller.ui_bookModel.removeReadStatusFilter(this.value)
                                }
                            }
                        }
                        CheckBox {
                            property string value: "IN_PROGRESS"
                            text: "In Progress"
                            onCheckedChanged: {
                                if (checked){
                                    controller.ui_bookModel.addReadStatusFilter(this.value)
                                }
                                else {
                                    controller.ui_bookModel.removeReadStatusFilter(this.value)
                                }
                            }
                        }
                    }
                }

                CollapsibleItem {
                    id: tagsGroup
                    Layout.fillWidth: true
                    titleText: qsTr("Tags")
                    Layout.bottomMargin: 10
                    boxContent: ColumnLayout {
                        anchors.fill: parent
                        Repeater {
                            model: controller.ui_bookModel.ui_booksFilter.ui_booksFilterTags
                            delegate: CheckBox {
                                text: modelData
                                onCheckedChanged: {
                                    if (checked){
                                        controller.ui_bookModel.addTagFilter(this.text)
                                    }
                                    else {
                                        controller.ui_bookModel.removeTagFilter(this.text)
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
