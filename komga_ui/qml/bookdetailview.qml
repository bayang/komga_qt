import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.11
import komga_api 1.0
import assets 1.0

Item {
    id: bookDetailRoot
    property bool imageCurrentlyHovered: false
    property string currentBookId
    property real currentBookPageReached
    property real currentBookPageCount
    property bool currentBookCompleted
    property string currentBookMetadataTitle
    property string currentBookMetadataNumber
    property string currentBookWriters
    property string currentBookPencillers
    property string currentBookColorists
    property string currentBookSummary
    property string currentBookSize
    property string currentBookShortMediaType
    property string currentBookUrl
    // can we go back to series view etc...
    // or are we displaying a book alone (from search for example)
    // used to know if we need to update models
    // so that data is consistent when we pop the stack
    property bool standaloneView
    property bool hasPrevious
    property bool hasNext
    property bool currentlyReading: false
    property Book nextBook
    property Book previousBook

    Connections {
        target: controller.ui_bookModel
        onNextBookReady: {
            console.log("next book received " + book.ui_bookId)
            nextBook = book
            if (nextBook.ui_bookId != "-1") {
                hasNext = true
            }
            else {
                hasNext = false
            }
            readPopup.readView.nextBookId = nextBook.ui_bookId
            readPopup.readView.hasNextBook = hasNext
        }
        onPreviousBookReady: {
            console.log("previous book received " + book.ui_bookId)
            previousBook = book
            if (previousBook.ui_bookId != "-1") {
                hasPrevious = true
            }
            else {
                hasPrevious = false
            }
        }
    }

    Component.onCompleted: {
        preloadBooks()
    }

    function preloadBooks() {
        controller.nextBook(currentBookId)
        controller.previousBook(currentBookId)
    }

    function goToPreviousBook() {
        controller.updateSelectedBookIdx(-1)
        stack.replace("qrc:/qml/bookdetailview.qml", {
                          currentBookId: previousBook.ui_bookId,
                          currentBookPageReached: previousBook.ui_bookPageReached,
                          currentBookPageCount: previousBook.ui_bookPagesCount,
                          currentBookCompleted: previousBook.ui_bookCompleted,
                          currentBookMetadataTitle: previousBook.ui_bookMetadata.ui_metadataTitle,
                          currentBookWriters: previousBook.ui_bookMetadata.ui_metadataWriters,
                          currentBookPencillers: previousBook.ui_bookMetadata.ui_metadataPencillers,
                          currentBookColorists: previousBook.ui_bookMetadata.ui_metadataColorists,
                          currentBookSummary: previousBook.ui_bookMetadata.ui_metadataSummary,
                          currentBookSize: previousBook.ui_bookSize,
                          currentBookShortMediaType: previousBook.ui_bookShortMediaType,
                          currentBookUrl: previousBook.ui_bookUrl,
                          standaloneView: false,
                      })
    }

    function goToNextBook() {
            controller.updateSelectedBookIdx(1)
            if (currentlyReading) {
                readPopup.readView.disableSource()
                readPopup.readView.pageReached = 0
                currentBookPageReached = nextBook.ui_bookPageReached
                currentBookId = nextBook.ui_bookId
                currentBookPageCount = nextBook.ui_bookPagesCount
                currentBookCompleted = nextBook.ui_bookCompleted
                standaloneView = false
                currentBookMetadataTitle = nextBook.ui_bookMetadata.ui_metadataTitle
                currentBookWriters = nextBook.ui_bookMetadata.ui_metadataWriters
                currentBookPencillers = nextBook.ui_bookMetadata.ui_metadataPencillers
                currentBookColorists = nextBook.ui_bookMetadata.ui_metadataColorists
                currentBookSummary = nextBook.ui_bookMetadata.ui_metadataSummary
                currentBookSize = nextBook.ui_bookSize
                currentBookShortMediaType = nextBook.ui_bookShortMediaType
                currentBookUrl = nextBook.ui_bookUrl
                readPopup.readView.restoreSource()
                preloadBooks()
            }
            else {
                stack.replace("qrc:/qml/bookdetailview.qml", {
                               currentBookId: nextBook.ui_bookId,
                               currentBookPageReached: nextBook.ui_bookPageReached,
                               currentBookPageCount: nextBook.ui_bookPagesCount,
                               currentBookCompleted: nextBook.ui_bookCompleted,
                               currentBookMetadataTitle: nextBook.ui_bookMetadata.ui_metadataTitle,
                               currentBookWriters: nextBook.ui_bookMetadata.ui_metadataWriters,
                               currentBookPencillers: nextBook.ui_bookMetadata.ui_metadataPencillers,
                               currentBookColorists: nextBook.ui_bookMetadata.ui_metadataColorists,
                               currentBookSummary: nextBook.ui_bookMetadata.ui_metadataSummary,
                               currentBookSize: nextBook.ui_bookSize,
                               currentBookShortMediaType: nextBook.ui_bookShortMediaType,
                               currentBookUrl: nextBook.ui_bookUrl,
                               standaloneView: false,
                           })
            }

    }

    ScrollView {
        id: scroll
        clip: true
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        ColumnLayout {
            id: parentLayout
            RowLayout {
                Button {
                    onClicked: {
                        if (contentFrame.depth > 0) {
                            contentFrame.pop()
                        }
                    }
                    font {
                        family: Style.fontAwesomeSolid
                        pointSize: Style.backArrowIconSize
                    }
                    text: "\uf060"
                    ToolTip.delay: 1000
                    ToolTip.timeout: 3000
                    ToolTip.visible: hovered
                    hoverEnabled: true
                    ToolTip.text: qsTr("Back")
                }
                RoundButton {
                    id: previousButton
                    enabled: hasPrevious
                    onClicked: {
                        goToPreviousBook()
                    }
                    font {
                        family: Style.fontAwesomeSolid
                        pointSize: Style.backArrowIconSize
                    }
                    text: "\uf191";
                    ToolTip.delay: 1000
                    ToolTip.timeout: 3000
                    ToolTip.visible: hovered
                    hoverEnabled: true
                    ToolTip.text: qsTr("Previous book")
                }
                RoundButton {
                    id: nextButton
                    enabled: hasNext
                    onClicked: {
                        goToNextBook()
                    }
                    font {
                        family: Style.fontAwesomeSolid
                        pointSize: Style.backArrowIconSize
                    }
                    text: "\uf152";
                    ToolTip.delay: 1000
                    ToolTip.timeout: 3000
                    ToolTip.visible: hovered
                    hoverEnabled: true
                    ToolTip.text: qsTr("Next book")
                }

            }

            GridLayout {
                id: grid
                columnSpacing: 10
                Layout.minimumHeight: bookDetailImage.sourceSize.height
                Item {
                    id: imageBookWrapper
                    Layout.preferredWidth: bookDetailImage.paintedWidth
                    Layout.alignment: Qt.AlignTop
                    Image {
                        id: bookDetailImage
                        source: "image://async/book/" + currentBookId
                        sourceSize.height: 300
                        sourceSize.width: -1
                        fillMode: Image.PreserveAspectCrop
                        ProgressBar {
                            width: parent.width
                            anchors.bottom: parent.bottom
                            contentItem.implicitHeight: 10
                            value: currentBookPageReached / (currentBookPageCount - 1)
                            visible: currentBookPageReached > 0 && ! currentBookCompleted
                        }
                    }
                    Label {
                        font {
                            family: Style.fontAwesomeSolid
                            pointSize: 50
                        }
                        anchors.centerIn: bookDetailImage
                        text: "\uf518"
                        visible: imageCurrentlyHovered
                    }

                    MouseArea {
                        id : bookDetailImageMouseArea
                        width: bookDetailImage.width
                        height: bookDetailImage.height
                        hoverEnabled: true
                        onClicked: {
                            readPopup.open()
                        }
                        onEntered: {
                            cursorShape = Qt.PointingHandCursor
                            imageCurrentlyHovered = true
                        }
                        onExited: {
                            imageCurrentlyHovered = false
                        }
                    }
                }

                ColumnLayout {
                    id: textColumn
                    Layout.alignment: Qt.AlignTop
                    Label {
                        id: curBookStatus
                        text: qsTr(currentBookMetadataTitle)
                        font.pointSize: Style.mediumTextSize
                    }
                    Label {
                        text: currentBookWriters ? "Writers : " + qsTr(currentBookWriters) : ""
                        font.pointSize: Style.smallMediumTextSize
                    }
                    Label {
                        text: currentBookPencillers ? "Pencillers : " + qsTr(currentBookPencillers) : ""
                        font.pointSize: Style.smallMediumTextSize
                        visible: currentBookPencillers
                    }
                    Label {
                        text: currentBookColorists ? "Colorists : " + qsTr(currentBookColorists) : ""
                        font.pointSize: Style.smallMediumTextSize
                        visible: currentBookColorists
                    }
                    Label {
                        text: currentBookMetadataNumber ? "# " + qsTr(currentBookMetadataNumber) : ""
                        font.pointSize: Style.smallMediumTextSize
                        visible: currentBookMetadataNumber
                    }
                    Label {
                        text: qsTr(currentBookSummary)
                        wrapMode: Text.Wrap
                        Layout.fillWidth: true
                        font.pointSize: Style.smallMediumTextSize
                        Layout.maximumWidth: scroll.width - imageBookWrapper.width - 20
                    }
                }
            }
            RowLayout {
                Layout.alignment: Qt.AlignLeft
                Button {
                    text: qsTr("Read")
                    onClicked: readPopup.open()
                    font.pointSize: Style.smallTextSize
                }

                Label {
                    id : bookPagesCountLabel
                    text: qsTr(currentBookPageCount.toString()) + " pages"
                    font.pointSize: Style.smallTextSize
                }
            }

            Label {
                text: "SIZE : " + qsTr(currentBookSize)
                font.pointSize: Style.smallTextSize
            }
            Label {
                text: "FORMAT : " + qsTr(currentBookShortMediaType)
                font.pointSize: Style.smallTextSize
            }
            Label {
                text: "FILE : " + qsTr(currentBookUrl)
                font.pointSize: Style.smallTextSize
            }
        }
    }

    Popup {
        id: readPopup

        property alias readView: readView

        parent: Overlay.overlay

        contentWidth: ApplicationWindow.window.width
        contentHeight: ApplicationWindow.window.height

        modal: true
        focus: true
        background: Rectangle {
            color: Style.black
        }

        closePolicy: Popup.CloseOnEscape
        opacity: 1.0
        Overlay.modal: Rectangle {
            color: Qt.darker(Style.backgroundColor)
        }
        enter: Transition {
            NumberAnimation { property: "opacity"; from: 0.0; to: 1.0; duration: 800 }
        }
        exit: Transition {
            NumberAnimation { property: "opacity"; from: 1.0; to: 0.0; duration: 300 }
        }
        onAboutToHide: {

        }

        BookReadView {
            id: readView
            anchors.fill: parent
            bookId: currentBookId
            pageReached: currentBookCompleted ? 0 : currentBookPageReached
            pageCount: currentBookPageCount
            standaloneBook: standaloneView
            hasNextBook: hasNext
            onPageChanged: {
                currentBookPageReached = pageNum
                controller.preloadBookPages(currentBookId, currentBookPageReached, currentBookPageCount)
                if (hasNext && (currentBookPageCount - currentBookPageReached < 5)) {
                    console.log("remaining " + (currentBookPageCount - currentBookPageReached) + " nextId " + bookDetailRoot.nextBook.ui_bookId + " nextCount " + bookDetailRoot.nextBook.ui_bookPagesCount)
                    controller.preloadBookPages(bookDetailRoot.nextBook.ui_bookId, -1, bookDetailRoot.nextBook.ui_bookPagesCount)
                }
                // page nb is not 0 based
                controller.updateprogress(currentBookId, currentBookPageReached + 1)
            }
            onNextBook: {
                currentlyReading = true
                goToNextBook()
            }
        }
    }
}
