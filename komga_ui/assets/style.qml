pragma Singleton
import QtQuick 2.14
import QtQuick.Controls.Material 2.14

Item {
    readonly property color backgroundColor: Material.backgroundColor
    readonly property color accentColor: Material.accent
    readonly property color foregroundColor: Material.foreground

    readonly property real libraryPaneWidth: 240
    readonly property real libraryPaneMinWidth: 125
    readonly property real libraryPaneMaxWidth: 350
    readonly property real thumbnailRequestedHeight: 230
    readonly property real thumbnailRequestedWidth: 175
    readonly property real backArrowIconSize: 18
    readonly property real defaultTextInputWidth: 400

    readonly property real smallCardHeight: 200
    readonly property real smallCardWidth: 100
    readonly property real smallCardThumbnailHeight: 150

    readonly property real mediumTextSize: 18
    readonly property real intermediateTextSize: 15
    readonly property real smallMediumTextSize: 13
    readonly property real smallTextSize: 11
    readonly property real microTextSize: 8

    readonly property color badgeBackground: "gray"
    readonly property color hoverBorderColor: "lightsteelblue"

    property alias fontAwesome: fontAwesomeLoader.name
    property alias fontAwesomeSolid: fontAwesomeLoaderSolid.name
    FontLoader {
        id: fontAwesomeLoader
        source: "qrc:/assets/Font Awesome 5 Free-Regular-400.otf"
    }
    FontLoader {
        id: fontAwesomeLoaderSolid
        source: "qrc:/assets/la-solid-900.ttf"
    }

}
