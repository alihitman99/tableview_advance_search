import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Window {
    id: rootItem

    visible: true

    width: 1000
    height: 630

    color: "red"

    // TEST
    //    Component {
    //        id: testComponent
    //        MyTableView {}
    //        //        Rectangle {
    //        //            width: 10
    //        //                        height: 10
    //        //            color: 'gold'
    //        //        }
    //    }
    // ENDTEST
    ColumnLayout {
        anchors.fill: parent

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            color: 'lightblue'

            Button {
                text: 'toggle visible'
                onClicked: {

                    // TODO
                }
            }
        }

        Rectangle {
            id: tableViewContainer
            Layout.fillWidth: true
            Layout.fillHeight: true

            data: managerInstance.qmlItem
        }
    }

    //    MyTableView {}
}
