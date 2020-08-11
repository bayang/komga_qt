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
    property string currentBookPublisher
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

    Connections {
        target: controller.ui_bookModel
        onNextBookReady: {
            console.log("book " + book)
            controller.updateSelectedBookIdx(1)
            if (currentlyReading) {
                currentBookId= book.ui_bookId
                currentBookPageReached= book.ui_bookPageReached
                currentBookPageCount= book.ui_bookPagesCount
                currentBookCompleted= book.ui_bookCompleted
                standaloneView= false
                hasNext= controller.hasNextBook()
                hasPrevious= controller.hasPreviousBook()
                currentBookMetadataTitle= book.ui_bookMetadata.ui_metadataTitle
                currentBookWriters= book.ui_bookMetadata.ui_metadataWriters
                currentBookPencillers= book.ui_bookMetadata.ui_metadataPencillers
                currentBookColorists= book.ui_bookMetadata.ui_metadataColorists
                currentBookPublisher = book.ui_bookMetadata.ui_metadataPublisher
                currentBookSummary= book.ui_bookMetadata.ui_metadataSummary
                currentBookSize= book.ui_bookSize
                currentBookShortMediaType= book.ui_bookShortMediaType
                currentBookUrl= book.ui_bookUrl
            }
            else {
                stack.replace("qrc:/qml/bookdetailview.qml", {
                               currentBookId: book.ui_bookId,
                               currentBookPageReached: book.ui_bookPageReached,
                               currentBookPageCount: book.ui_bookPagesCount,
                               currentBookCompleted: book.ui_bookCompleted,
                               currentBookMetadataTitle: book.ui_bookMetadata.ui_metadataTitle,
                               currentBookWriters: book.ui_bookMetadata.ui_metadataWriters,
                               currentBookPencillers: book.ui_bookMetadata.ui_metadataPencillers,
                               currentBookColorists: book.ui_bookMetadata.ui_metadataColorists,
                               currentBookPublisher : book.ui_bookMetadata.ui_metadataPublisher,
                               currentBookSummary: book.ui_bookMetadata.ui_metadataSummary,
                               currentBookSize: book.ui_bookSize,
                               currentBookShortMediaType: book.ui_bookShortMediaType,
                               currentBookUrl: book.ui_bookUrl,
                               standaloneView: false,
                               hasPrevious: controller.hasPreviousBook(),
                               hasNext: controller.hasNextBook()
                           })
            }
        }
        onPreviousBookReady: {
            console.log("book " + book)
            controller.updateSelectedBookIdx(-1)
            stack.replace("qrc:/qml/bookdetailview.qml", {
                           currentBookId: book.ui_bookId,
                           currentBookPageReached: book.ui_bookPageReached,
                           currentBookPageCount: book.ui_bookPagesCount,
                           currentBookCompleted: book.ui_bookCompleted,
                           currentBookMetadataTitle: book.ui_bookMetadata.ui_metadataTitle,
                           currentBookWriters: book.ui_bookMetadata.ui_metadataWriters,
                           currentBookPencillers: book.ui_bookMetadata.ui_metadataPencillers,
                           currentBookColorists: book.ui_bookMetadata.ui_metadataColorists,
                           currentBookPublisher : book.ui_bookMetadata.ui_metadataPublisher,
                           currentBookSummary: book.ui_bookMetadata.ui_metadataSummary,
                           currentBookSize: book.ui_bookSize,
                           currentBookShortMediaType: book.ui_bookShortMediaType,
                           currentBookUrl: book.ui_bookUrl,
                           standaloneView: false,
                           hasPrevious: controller.hasPreviousBook(),
                           hasNext: controller.hasNextBook()
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
                    visible: hasPrevious
                    onClicked: {
                        controller.previousBook(currentBookId)
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
                    visible: hasNext
                    onClicked: {
                        controller.nextBook(currentBookId)
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
                            value: currentBookPageReached / currentBookPageCount
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
                        text: currentBookPublisher ? "Publisher : " + qsTr(currentBookPublisher) : ""
                        font.pointSize: Style.smallMediumTextSize
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
            anchors.fill: parent
            bookId: currentBookId
            pageReached: currentBookCompleted ? 0 : currentBookPageReached
            pageCount: currentBookPageCount
            standaloneBook: standaloneView
            hasNextBook: hasNext
            onPageChanged: {
                currentBookPageReached = pageNum
                controller.preloadBookPages(currentBookId, currentBookPageReached, currentBookPageCount)
                // page nb is not 0 based
                controller.updateprogress(currentBookId, currentBookPageReached + 1)
            }
            onNextBook: {
                currentlyReading = true
                controller.nextBook(currentBookId)
            }
        }
    }
}
