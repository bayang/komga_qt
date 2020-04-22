import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import Qt.labs.settings 1.0

import assets 1.0

Item {
    id: page
    width: parent.width
    height: parent.height

    Settings {
        id: serverSettings
            category: "server"
            property alias serverAdress: serverInput.text
            property alias serverUsername: userNameInput.text
            property alias serverPassword: passwordInput.text
    }

    ColumnLayout {
        Layout.preferredWidth: serverRow.minimumWidth
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
            text: "settings"
        }
        RowLayout {
            id: serverRow
            Layout.fillWidth: true
            Label {
                id: serverLabel
                text: "Server Adress"
                rightPadding: 20
            }
            TextField {
                id: serverInput
                Layout.minimumWidth: Style.defaultTextInputWidth
                selectByMouse: true
            }
        }
        RowLayout {
            Layout.fillWidth: true
            Label {
                text: "User name"
                rightPadding: 20
                width: serverLabel.width
            }
            TextField {
                id: userNameInput
                Layout.minimumWidth: Style.defaultTextInputWidth
            }
        }
        RowLayout {
            Label {
                width: serverLabel.width
                text: "Password"
                rightPadding: 20
            }
            TextField {
                id: passwordInput
                Layout.minimumWidth: Style.defaultTextInputWidth
            }
        }

    }
}
