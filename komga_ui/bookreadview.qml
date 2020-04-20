import QtQuick 2.14
import QtQuick.Controls 2.14
import komga_api 1.0

Item {

    id: readContainer
    width: parent.width
    height: parent.height
    property real imgScale: 0
    property real lastSpacePressedTime: 0
    property bool infoVisibility: true

    Flickable {
        id: flickArea
        anchors.fill: parent
        focus: true
        contentWidth: Math.max(bookReadPage.paintedWidth * imgScale, readContainer.width)
        contentHeight: Math.max(bookReadPage.paintedHeight  * imgScale, readContainer.height)
        anchors.centerIn: parent
        boundsBehavior: Flickable.StopAtBounds
        boundsMovement: Flickable.StopAtBounds
        contentX: contentWidth === readContainer.width ? 0 : bookReadPage.paintedWidth * imgScale / 2 - flickArea.width / 2
        contentY: contentHeight === readContainer.height ? 0 : bookReadPage.paintedHeight * imgScale / 2 - flickArea.height / 2
        Image {
            id: bookReadPage
            source: "image://page/" + controller.ui_currentBook.ui_bookId + "/" + controller.ui_currPageNumber
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
            asynchronous: true
            clip: true
            transformOrigin: Item.Center
            scale: imgScale

            onProgressChanged: {
                console.log("progress " + bookReadPage.progress + " " + bookReadPage.sourceSize.width + " w " + bookReadPage.width + " pw " + bookReadPage.paintedWidth + " sc " + bookReadPage.scale + " scx " + bookReadPage.paintedWidth * bookReadPage.scale)
                if (progress === 1) {
                    console.log("prog 1")
                    lastSpacePressedTime = 0
                    if (! flickArea.atYBeginning) {
                        flickArea.contentY = 0
                    }
                }
            }
            onStatusChanged: {
                console.log("status " + bookReadPage.status + " " + bookReadPage.sourceSize.width + " w " + bookReadPage.width + " pw " + bookReadPage.paintedWidth + " sc " + bookReadPage.scale + " scx " + bookReadPage.paintedWidth * bookReadPage.scale)
            }

            onSourceChanged: {
                console.log("source changed " + bookReadPage.sourceSize.width + " w " + bookReadPage.width + " pw " + bookReadPage.paintedWidth + " sc " + bookReadPage.scale + " scx " + bookReadPage.paintedWidth * bookReadPage.scale)
                lastSpacePressedTime = 0
            }
            Component.onCompleted: {
                console.log("completed " + bookReadPage.sourceSize.width + " w " + bookReadPage.width + " pw " + bookReadPage.paintedWidth + " sc " + bookReadPage.scale + " scx " + bookReadPage.paintedWidth * bookReadPage.scale)
            }

            onSourceSizeChanged: {
                console.log("source size changed " + bookReadPage.sourceSize.width + " w " + bookReadPage.width + " pw " + bookReadPage.paintedWidth + " sc " + bookReadPage.scale + " scx " + bookReadPage.paintedWidth * bookReadPage.scale)
                console.log("readCon w readConL w" + readContainer.width)
                lastSpacePressedTime = 0
                if (imgScale === 0) {
                    imgScale = readContainer.height / bookReadPage.paintedHeight
                }
                if (! flickArea.atYBeginning) {
                    flickArea.contentY = 0
                }
                console.log("imgScale " + imgScale)
            }
            onScaleChanged: {
                console.log("scaled changed " + bookReadPage.sourceSize.width + " w " + bookReadPage.width + " pw " + bookReadPage.paintedWidth + " sc " + bookReadPage.scale + " scx " + bookReadPage.paintedWidth * bookReadPage.scale)
                console.log("xy " + readContainer.x + " " + readContainer.y + " / " + bookReadPage.x + " " + bookReadPage.y)

            }

            MouseArea {
                id : imageMouseArea
                anchors.fill: parent
                cursorShape: pressed ? Qt.ClosedHandCursor : Qt.ArrowCursor;
                onWheel: {
                    if (wheel.angleDelta.y > 0) {
                        scaleUp()
                    }
                    else {
                        scaleDown()
                    }
                }
            }
        }
    }

    BusyIndicator {
        running: bookReadPage.status === Image.Loading
        anchors.centerIn: parent
    }

    Keys.onSpacePressed: {
        flickArea.contentY += bookReadPage.paintedHeight / 4
        flickArea.returnToBounds()
        if (flickArea.atYEnd) {
            var curTime = new Date().getTime();
            console.log("atYEnd " + curTime + " " + lastSpacePressedTime)
            if (curTime - lastSpacePressedTime < 2000) {
                controller.ui_currPageNumber += 1
                console.log("next page")
            }
            lastSpacePressedTime = curTime
        }
    }
    Keys.onRightPressed: {
        flickArea.contentX += 30
        flickArea.returnToBounds()
    }
    Keys.onLeftPressed: {
        flickArea.contentX -= 30
        flickArea.returnToBounds()
    }
    Keys.onDownPressed: {
        flickArea.contentY += 30
        flickArea.returnToBounds()
    }
    Keys.onUpPressed: {
        flickArea.contentY -= 30
        flickArea.returnToBounds()
    }
    Keys.onPressed: {
        if (event.key === Qt.Key_Plus) {
            scaleUp()
            event.accepted = true;
        }
        else if (event.key === Qt.Key_Minus) {
            scaleDown()
            event.accepted = true
        }
        else if (event.key === Qt.Key_PageUp) {
            controller.ui_currPageNumber -= 1
            event.accepted = true
        }
        else if (event.key === Qt.Key_PageDown) {
            controller.ui_currPageNumber += 1
            event.accepted = true
        }
    }

    function scaleUp() {
        if (imgScale < 4) {
            imgScale += 0.1
        }
    }
    function scaleDown() {
        if (imgScale >= 0.2) {
            imgScale -= 0.1
        }
    }


    Item {
        id: pageNumberWrapper
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 20
        visible: infoVisibility

        YAnimator {
            id: pageNumberWrapperAnimator
               target: pageNumberWrapper;
               from: readContainer.height - 50;
               to: readContainer.height + pageNumberWrapper.height + 100;
               duration: 1000
               easing.type: Easing.Linear
           }
        Rectangle {
            opacity: 0.6
            width: pageNumberLabel.width + 5
            color: "gray"
            height: pageNumberLabel.height + 5
            anchors.centerIn: parent
        }

        Label {
            id: pageNumberLabel
            anchors.centerIn: parent
            text: (controller.ui_currPageNumber + 1).toString() + "/" + controller.ui_currentBook.ui_bookPagesCount
        }
    }

    Timer {
        id : visibilityTimer
        interval: 750
        repeat: false
        onTriggered: {
            pageNumberWrapperAnimator.start()
        }
    }

    MouseArea {
        id: bookPageMouseArea
        anchors.fill: parent
        hoverEnabled: true
        onPositionChanged: {
            pageNumberWrapper.y  = readContainer.height - 50
            visibilityTimer.restart()
        }
    }
}
