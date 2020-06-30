import QtQuick 2.14
import QtQuick.Controls 2.14
import komga_api 1.0
import assets 1.0

Item {

    id: readContainer
    property real imgScale: 0
    property real lastSpacePressedTime: 0
    property real bookId
    property real pageReached
    property real pageCount
    property bool standaloneBook
    signal pageChanged(real pageNum);

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
            source: "image://page/" + bookId + "/" + pageReached
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
            asynchronous: true
            cache: true
            clip: true
            transformOrigin: Item.Center
            scale: imgScale

            onProgressChanged: {
//                console.log("progress " + bookReadPage.progress + " " + bookReadPage.sourceSize.width + " w " + bookReadPage.width + " pw " + bookReadPage.paintedWidth + " sc " + bookReadPage.scale + " scx " + bookReadPage.paintedWidth * bookReadPage.scale)
                if (progress === 1) {
                    lastSpacePressedTime = 0
                    if (! flickArea.atYBeginning) {
                        flickArea.contentY = 0
                    }
                }
            }
            onStatusChanged: {
//                console.log("status " + bookReadPage.status + " " + bookReadPage.sourceSize.width + " w " + bookReadPage.width + " pw " + bookReadPage.paintedWidth + " sc " + bookReadPage.scale + " scx " + bookReadPage.paintedWidth * bookReadPage.scale)
            }

            onSourceChanged: {
//                console.log("source changed " + bookReadPage.sourceSize.width + " w " + bookReadPage.width + " pw " + bookReadPage.paintedWidth + " sc " + bookReadPage.scale + " scx " + bookReadPage.paintedWidth * bookReadPage.scale)
                lastSpacePressedTime = 0
            }
            Component.onCompleted: {
//                console.log("completed " + bookReadPage.sourceSize.width + " w " + bookReadPage.width + " pw " + bookReadPage.paintedWidth + " sc " + bookReadPage.scale + " scx " + bookReadPage.paintedWidth * bookReadPage.scale)
            }

            onSourceSizeChanged: {
//                console.log("source size changed " + bookReadPage.sourceSize.width + " w " + bookReadPage.width + " pw " + bookReadPage.paintedWidth + " sc " + bookReadPage.scale + " scx " + bookReadPage.paintedWidth * bookReadPage.scale)
//                console.log("readConH  readCon w" +readContainer.height + " " + readContainer.width)
                lastSpacePressedTime = 0
                if (imgScale === 0) {
                    fitHeight()
                }
                if (! flickArea.atYBeginning) {
                    flickArea.contentY = 0
                }
//                console.log("imgScale " + imgScale)
            }
            onScaleChanged: {
//                console.log("scaled changed " + bookReadPage.sourceSize.width + " w " + bookReadPage.width + " pw " + bookReadPage.paintedWidth + " sc " + bookReadPage.scale + " scx " + bookReadPage.paintedWidth * bookReadPage.scale)
//                console.log("xy " + readContainer.x + " " + readContainer.y + " / " + bookReadPage.x + " " + bookReadPage.y)

            }
        }
    }

    BusyIndicator {
        running: bookReadPage.status === Image.Loading
        anchors.centerIn: parent
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

    function fitWidth() {
        imgScale = readContainer.width / bookReadPage.paintedWidth
    }

    function fitHeight() {
        imgScale = readContainer.height / bookReadPage.paintedHeight
    }



    Item {
        id: pageNumberWrapper
        anchors.horizontalCenter: parent.horizontalCenter
        y: readContainer.height - 50

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
            text: (pageReached + 1).toString() + "/" + pageCount
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

    Timer {
        id : firstPageTimer
        interval: 750
        repeat: false
        onTriggered: {
            firstPageLabel.visible = false
        }
    }

    Label {
        id: firstPageLabel
        anchors.centerIn: parent
        color: "white"
        font {
            pointSize: 30
        }
        visible: false
    }

    Keys.onSpacePressed: {
        flickArea.contentY += bookReadPage.paintedHeight / 4
        flickArea.returnToBounds()
        if (flickArea.atYEnd) {
            var curTime = new Date().getTime();
            if (curTime - lastSpacePressedTime < 2000) {
                setCurrentReachedPage(pageReached + 1)
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
        else if (event.key === Qt.Key_PageUp || event.key === Qt.Key_J) {
            setCurrentReachedPage(pageReached - 1)
            event.accepted = true
        }
        else if (event.key === Qt.Key_PageDown || event.key === Qt.Key_K) {
            setCurrentReachedPage(pageReached + 1)
            event.accepted = true
        }
        else if (event.key === Qt.Key_End || event.key === Qt.Key_M) {
            setCurrentReachedPage(pageCount - 1)
            event.accepted = true
        }
        else if (event.key === Qt.Key_Home || event.key === Qt.Key_L) {
            setCurrentReachedPage(0)
            event.accepted = true
        }
        else if (event.key === Qt.Key_W) {
            fitWidth()
            event.accepted = true
        }
        else if (event.key === Qt.Key_H) {
            fitHeight()
            event.accepted = true
        }
    }
    function setCurrentReachedPage(pageNumber) {
        if (pageNumber < 0) {
            firstPageLabel.text = "First page"
            firstPageLabel.visible = true
            firstPageTimer.restart()
            return;
        }
        else if (pageNumber >= pageCount) {
            firstPageLabel.text = "Last page"
            firstPageLabel.visible = true
            firstPageTimer.restart()
            return;
        }
        else {
            console.log("current image nb changed " + pageNumber);
            pageReached = pageNumber;
            // update model so that parent views are updated
            if (! standaloneBook) {
                controller.setCurrentBookPageReached(pageNumber);
            }
            readContainer.pageChanged(pageNumber);
        }
    }
    MouseArea {
        id : imageMouseArea
        anchors.fill: parent
        cursorShape: pressed || flickArea.dragging ? Qt.ClosedHandCursor : Qt.ArrowCursor;
        // let button press be catched by flickable only (for dragging)
        acceptedButtons: Qt.NoButton
        onWheel: {
            if (wheel.angleDelta.y > 0) {
                scaleUp()
            }
            else {
                scaleDown()
            }
        }
        hoverEnabled: true
        onPositionChanged: {
            pageNumberWrapper.y  = readContainer.height - 50
            visibilityTimer.restart()
        }
    }
}
