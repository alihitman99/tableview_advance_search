import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Window {
    id: window

    visible: true

    width: 1000
    height: 630

    color: "#DEE3E6"



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
            id: tableViewContainer
            Layout.fillWidth: true
            Layout.fillHeight: true

            data: managerInstance.qmlItem
        }
    }

    //    MyTableView {}
}
