import QtQuick

QtObject {
    id: style
    readonly property color backgroundColor: "#DEE3E6"
    readonly property color foregroundColor: "#003569"
    readonly property color disableColor: Qt.rgba(foregroundColor.r,
                                                  foregroundColor.g,
                                                  foregroundColor.b, 0.5)
    readonly property color fg20: Qt.rgba(style.foregroundColor.r,
                                          style.foregroundColor.g,
                                          style.foregroundColor.b, 0.2)
    readonly property color fg30: Qt.rgba(style.foregroundColor.r,
                                          style.foregroundColor.g,
                                          style.foregroundColor.b, 0.3)
    readonly property color fg50: Qt.rgba(style.foregroundColor.r,
                                          style.foregroundColor.g,
                                          style.foregroundColor.b, 0.5)
    readonly property color fg75: Qt.rgba(style.foregroundColor.r,
                                          style.foregroundColor.g,
                                          style.foregroundColor.b, 0.75)
    readonly property color bg20: Qt.rgba(style.backgroundColor.r,
                                          style.backgroundColor.g,
                                          style.backgroundColor.b, 0.2)
    readonly property color bg75: Qt.rgba(style.backgroundColor.r,
                                          style.backgroundColor.g,
                                          style.backgroundColor.b, 0.75)

    readonly property color hoverColor: "#01AED6"
    readonly property color selectColor: "#B6C0CA"
    readonly property real monitorRatio: 1.3
    readonly property string fontFamily: "Roboto"
    readonly property double fontPointSize: 11 / monitorRatio
    function isNumeric(s) {
        return !isNaN(s - parseFloat(s))
    }
}
