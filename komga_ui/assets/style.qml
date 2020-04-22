pragma Singleton
import QtQuick 2.14

Item {
    readonly property real libraryPaneWidth: 270
    readonly property real thumbnailRequestedHeight: 230
    readonly property real thumbnailRequestedWidth: 175
    readonly property real backArrowIconSize: 18
    readonly property real defaultTextInputWidth: 400
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
