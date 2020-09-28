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
        onClicked: popup.open()
        font {
            family: Style.fontAwesomeSolid
            pointSize: Style.backArrowIconSize
        }
        text : "\uf0b0";
    }

    Popup {
        id: popup
        x: parent.x - statusGroup.width
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
                                    controller.ui_seriesModel.addReadStatusFilter(this.value)
                                }
                                else {
                                    controller.ui_seriesModel.removeReadStatusFilter(this.value)
                                }
                            }
                        }
                        CheckBox {
                            property string value: "READ"
                            text: "Read"
                            onCheckedChanged: {
                                if (checked){
                                    controller.ui_seriesModel.addReadStatusFilter(this.value)
                                }
                                else {
                                    controller.ui_seriesModel.removeReadStatusFilter(this.value)
                                }
                            }
                        }
                        CheckBox {
                            property string value: "IN_PROGRESS"
                            text: "In Progress"
                            onCheckedChanged: {
                                if (checked){
                                    controller.ui_seriesModel.addReadStatusFilter(this.value)
                                }
                                else {
                                    controller.ui_seriesModel.removeReadStatusFilter(this.value)
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
                            model: controller.ui_seriesModel.ui_seriesFilter.ui_seriesFilterTags
                            delegate: CheckBox {
                                text: modelData
                                onCheckedChanged: {
                                    if (checked){
                                        controller.ui_seriesModel.addTagFilter(this.text)
                                    }
                                    else {
                                        controller.ui_seriesModel.removeTagFilter(this.text)
                                    }
                                }
                            }
                        }
                    }
                }
                CollapsibleItem {
                    id: genresGroup
                    Layout.fillWidth: true
                    Layout.bottomMargin: 10
                    titleText: qsTr("Genres")
                    boxContent: ColumnLayout {
                        anchors.fill: parent
                        Repeater {
                            model: controller.ui_seriesModel.ui_seriesFilter.ui_seriesFilterGenres
                            delegate: CheckBox {
                                text: modelData
                                onCheckedChanged: {
                                    if (checked){
                                        controller.ui_seriesModel.addGenreFilter(this.text)
                                    }
                                    else {
                                        controller.ui_seriesModel.removeGenreFilter(this.text)
                                    }
                                }
                            }
                        }
                    }
                }
                CollapsibleItem {
                    id: statusGroup
                    Layout.fillWidth: true
                    Layout.bottomMargin: 10
                    titleText: qsTr("Series Status")
                    boxContent: ColumnLayout {
                        anchors.fill: parent
                        CheckBox {
                            property string value: "ENDED"
                            text: "Ended"
                            onCheckedChanged: {
                                if (checked){
                                    controller.ui_seriesModel.addStatusFilter(this.value)
                                }
                                else {
                                    controller.ui_seriesModel.removeStatusFilter(this.value)
                                }
                            }
                        }
                        CheckBox {
                            property string value: "ONGOING"
                            text: "Ongoing"
                            onCheckedChanged: {
                                if (checked){
                                    controller.ui_seriesModel.addStatusFilter(this.value)
                                }
                                else {
                                    controller.ui_seriesModel.removeStatusFilter(this.value)
                                }
                            }
                        }
                        CheckBox {
                            property string value: "ABANDONED"
                            text: "Abandoned"
                            onCheckedChanged: {
                                if (checked){
                                    controller.ui_seriesModel.addStatusFilter(this.value)
                                }
                                else {
                                    controller.ui_seriesModel.removeStatusFilter(this.value)
                                }
                            }
                        }
                        CheckBox {
                            property string value: "HIATUS"
                            text: "Hiatus"
                            onCheckedChanged: {
                                if (checked){
                                    controller.ui_seriesModel.addStatusFilter(this.value)
                                }
                                else {
                                    controller.ui_seriesModel.removeStatusFilter(this.value)
                                }
                            }
                        }
                    }
                }
                CollapsibleItem {
                    id: ageRatingsGroup
                    Layout.fillWidth: true
                    Layout.bottomMargin: 10
                    titleText: qsTr("Age Rating")
                    boxContent: ColumnLayout {
                        anchors.fill: parent
                        Repeater {
                            model: controller.ui_seriesModel.ui_seriesFilter.ui_seriesFilterAgeRatings
                            delegate: CheckBox {
                                text: modelData
                                onCheckedChanged: {
                                    if (checked){
                                        controller.ui_seriesModel.addAgeRatingFilter(this.text)
                                    }
                                    else {
                                        controller.ui_seriesModel.removeAgeRatingFilter(this.text)
                                    }
                                }
                            }
                        }
                    }
                }
                CollapsibleItem {
                    id: languagesGroup
                    Layout.fillWidth: true
                    Layout.bottomMargin: 10
                    titleText: qsTr("Language")
                    enabled: controller.ui_seriesModel.ui_seriesFilter.ui_seriesFilterLanguages.length > 0
                    boxContent: ColumnLayout {
                        anchors.fill: parent
                        Repeater {
                            model: controller.ui_seriesModel.ui_seriesFilter.ui_seriesFilterLanguages
                            delegate: CheckBox {
                                text: modelData
                                onCheckedChanged: {
                                    if (checked){
                                        controller.ui_seriesModel.addLanguageFilter(this.text)
                                    }
                                    else {
                                        controller.ui_seriesModel.removeLanguageFilter(this.text)
                                    }
                                }
                            }
                        }
                    }
                }
                CollapsibleItem {
                    id: publishersGroup
                    Layout.fillWidth: true
                    Layout.bottomMargin: 10
                    titleText: qsTr("Publisher")
                    enabled: controller.ui_seriesModel.ui_seriesFilter.ui_seriesFilterPublishers.length > 0
                    boxContent: ColumnLayout {
                        anchors.fill: parent
                        Repeater {
                            model: controller.ui_seriesModel.ui_seriesFilter.ui_seriesFilterPublishers
                            delegate: CheckBox {
                                text: modelData
                                onCheckedChanged: {
                                    if (checked){
                                        controller.ui_seriesModel.addPublisherFilter(this.text)
                                    }
                                    else {
                                        controller.ui_seriesModel.removePublisherFilter(this.text)
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
