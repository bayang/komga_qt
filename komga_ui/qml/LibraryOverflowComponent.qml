import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

import komga_api 1.0
import assets 1.0

Item {
    id: root
    property string libraryId
    property alias popupWidth: popup.contentWidth

    RoundButton {
        id: triggerButton
        anchors.fill: parent
        onClicked: popup.open()
        font {
            family: Style.fontAwesomeSolid
            pointSize: Style.backArrowIconSize
        }
        text : "\uf142";
    }

    Popup {
        id: popup
        x: parent.x - contentWidth - 30
        y: parent.y + triggerButton.height

        ColumnLayout  {
            id:column
            anchors.fill: parent
            TextLink {
                id: scanLabel
                textLinkLabel: qsTr("Scan library files")
                onTextLinkClicked: {
                    controller.ui_libraryModel.scan(libraryId)
                    popup.close()
                }
            }
            TextLink {
                id: analyzeLabel
                textLinkLabel: qsTr("Analyze library")
                onTextLinkClicked: {
                    controller.ui_libraryModel.analyze(libraryId)
                    popup.close()
                }
            }
            TextLink {
                id: metadataRefreshLabel
                textLinkLabel: qsTr("Refresh metadata")
                onTextLinkClicked: {
                    controller.ui_libraryModel.refreshMetadata(libraryId)
                    popup.close()
                }
            }
        }
    }
}
