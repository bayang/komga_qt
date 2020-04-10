import QtQuick 2.14
import QtQuick.Controls 2.14
import komga_api 1.0

Item {

    Row {
        width: 400
        height: 400
        spacing: 10
        Image {
            id: bookDetailImage
            source: "image://books/" + currentBook.ui_bookId
            sourceSize.height: 300
            sourceSize.width: -1
            fillMode: Image.PreserveAspectCrop
        }
        Label {
            id: curBookStatus
            text: qsTr(currentBook.ui_bookMetadata.ui_metadataTitle)
        }
    }

}
