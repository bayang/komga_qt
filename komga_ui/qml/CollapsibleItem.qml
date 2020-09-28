import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14
import assets 1.0

Item {
    id: root
    implicitHeight: titleRect.implicitHeight + box.implicitHeight
    implicitWidth: Math.max(titleRect.implicitWidth, box.implicitWidth)

    property alias titleText: titleTxt.text
    property alias boxContent: box.contentItem
    state: "collapsed"

    Rectangle{
        id: titleRect
        implicitHeight: Math.max(titleTxt.height, caret.height)
        implicitWidth: caret.width + titleTxt.width
        color: "transparent"
        Label{
            id: titleTxt
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: Style.intermediateTextSize
        }
        Label {
            id: caret
            anchors.left: titleTxt.right
            anchors.rightMargin: 10
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            font {
                family: Style.fontAwesomeSolid
                pointSize: Style.smallMediumTextSize
            }
            text : "\uf106";
        }
        MouseArea{
            width: parent.width
            height:  parent.height
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                if (root.state == "collapsed")
                {
                    root.state = "expanded"
                }
                else
                {
                    root.state = "collapsed"
                }
            }
        }
    }

    GroupBox {
        id: box
        anchors.top: titleRect.bottom
        implicitHeight: contentItem.implicitHeight
//        Behavior on height {
//                 NumberAnimation { duration: 1000 }
//             }
    }

    states: [
        State {
            name: "collapsed"
            PropertyChanges {
                target: box
                height: 0
                opacity: 0
            }
            PropertyChanges {
                target: root
                height: titleRect.height
                implicitHeight: titleRect.height
            }
            PropertyChanges {
                target: caret
                text : "\uf107";
            }
        },
        State {
            name: "expanded"
            PropertyChanges {
                target: box
                implicitHeight: contentItem.implicitHeight
                opacity: 100
            }
            PropertyChanges {
                target: root
                implicitHeight: titleRect.implicitHeight + box.implicitHeight
            }
            PropertyChanges {
                target: caret
                text : "\uf106";
            }
        }
    ]

//    transitions: [
//        Transition {
//                        PropertyAnimation {
//                            target: box; property: "height"; duration: 300; easing.type: Easing.Linear
//                        }
//            //            NumberAnimation { target: box; property: "height"; duration: 100 }
//        }
//    ]
}
