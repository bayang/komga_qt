import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import Qt.labs.settings 1.0

import assets 1.0

Item {
    id: page

    Settings {
        id: serverSettings
            category: "server"
            property alias serverAdress: serverInput.text
            property alias serverUsername: userNameInput.text
            property alias serverPassword: passwordInput.text
    }

    ColumnLayout {
        Button {
            onClicked: {
                serverSettings.sync()
                if (contentFrame.depth > 0) {
                    contentFrame.pop()
                }
            }
            font {
                family: Style.fontAwesome
                pointSize: Style.backArrowIconSize
            }

            text: "\uf060"
        }
        Label {
            text: qsTr("Settings")
            font.pointSize: Style.mediumTextSize
        }
        GridLayout {
            columns: 2
            Label {
                id: serverLabel
                text: qsTr("Server Adress")
                rightPadding: 20
                font.pointSize: Style.smallMediumTextSize
            }
            TextField {
                id: serverInput
                Layout.minimumWidth: Style.defaultTextInputWidth
                selectByMouse: true
                placeholderText: qsTr("eg : http://localhost:8080/api/v1")
            }
            Label {
                text: qsTr("User name")
                rightPadding: 20
                width: serverLabel.width
                font.pointSize: Style.smallMediumTextSize
            }
            TextField {
                id: userNameInput
                Layout.minimumWidth: Style.defaultTextInputWidth
            }
            Label {
                width: serverLabel.width
                text: qsTr("Password")
                rightPadding: 20
                font.pointSize: Style.smallMediumTextSize
            }
            TextField {
                id: passwordInput
                Layout.minimumWidth: Style.defaultTextInputWidth
            }
        }
    }
}
