import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import QtQml.Models 2.14
import komga_api 1.0
import assets 1.0

Label {
    id: countBadge
    padding: 4
    font.bold: true
    background: Rectangle {
        color: Style.hoverBorderColor
        radius: 4
    }
}
