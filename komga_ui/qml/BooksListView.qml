import QtQuick 2.14
import QtQuick.Controls 2.14
import QtGraphicalEffects 1.14
import QtQuick.Layouts 1.14

import komga_api 1.0
import assets 1.0

Item {

    property string currentViewName
    anchors.fill: parent
    anchors.leftMargin: 10

    ColumnLayout {
        anchors.fill: parent

        Label {
            id: viewName
            text: currentViewName
            font.pointSize: Style.mediumTextSize
            Layout.alignment: Qt.AlignHCenter
            topPadding: 20
        }

        GridView {
            id: booksList
            model: controller.ui_bookModel
            clip: true
            cellWidth : Style.thumbnailRequestedWidth + 10
            cellHeight: Style.thumbnailRequestedHeight + 85
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: cellHeight
            Layout.minimumWidth: 100
            Layout.preferredHeight: parent.height - viewName.height
            Layout.preferredWidth: parent.width
            cacheBuffer: cellHeight
            Layout.bottomMargin: 2
            ScrollBar.vertical: ScrollBar { }
            delegate:
                CardItem {
                cardWidth: Style.thumbnailRequestedWidth
                cardHeight: booksList.cellHeight
                thumbnailHeight: Style.thumbnailRequestedHeight
                imagePath: "image://async/book/" + bookId
                cardLabel: bookName
                subLabel: bookPageCount + " pages\nsize: " + bookSize
                topCornerLabel: "✓"
                topCornerLabelFontSize: Style.mediumTextSize
                topCornerLabelVisible: bookCompleted
                progressVisible: bookPageReached > 0 && ! bookCompleted
                progressValue: bookPageReached/bookPageCount
                progressHeight: 10
                onCardClicked: {
                    booksList.currentIndex = index
                    controller.setSelectedBookIdx(booksList.currentIndex)
                    stack.push("qrc:/qml/bookdetailview.qml", {
                                   currentBookId: bookId,
                                   currentBookPageReached: bookPageReached,
                                   currentBookPageCount: bookPageCount,
                                   currentBookCompleted: bookCompleted,
                                   currentBookMetadataTitle: bookTitle,
                                   currentBookWriters: bookWriters,
                                   currentBookPencillers: bookPencillers,
                                   currentBookColorists: bookColorists,
                                   currentBookSummary: bookSummary,
                                   currentBookSize: bookSize,
                                   currentBookShortMediaType: bookMediaType,
                                   currentBookUrl: bookUrl,
                                   standaloneView: false,
                               })
                }
            }
        }
    }
    Label {
        text: "Nothing here !"
        visible: booksList.count < 1
        anchors.centerIn: parent
        font.pointSize: Style.mediumTextSize
    }
}
