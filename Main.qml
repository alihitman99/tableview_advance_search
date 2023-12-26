import QtQuick
import QtQuick.Window
import QtQuick.Controls
//import QtQuick.Controls.Fusion
import Qt.labs.qmlmodels
import QtQuick.Layouts


Window {
    id: rootItem
    width: 1200
    height: 800
    visible: true
    title: qsTr("Object List")
    color: "#DEE3E6"

    property double monitorRatio: 1.3
    Component.onCompleted: {
        //myProxyModel.filterStringColumn("")
    }

    ColumnLayout{
        anchors.fill: parent
        //        spacing: 1

        Rectangle{
            id: searchRect
            color: "#DEE3E6"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.bottomMargin: 1

            TextField{
                id: txtSearch
                Layout.leftMargin: 20
                Layout.topMargin: 20
                implicitWidth: 200
                placeholderText: "Search"
                onTextChanged: {
                    //                        console.log(txtSearchType.text)
                    //                        myProxyModel.setFilterColor(txtSearchColor.text)
                    myProxyModel.filterString("filterAllTable", txtSearch.text)
                }
                onTextEdited: {
                    //console.log("sear")
                }

            }


        }
        Rectangle{
            id: filterSearchRect
            color: "#DEE3E6"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.bottomMargin: 2
            ColumnLayout{
                spacing: 20

                RowLayout{
                    spacing: 30
                    SelectColor{

                    }





                    RowLayout{
                        ComboFilter{

                        }

                        Text{
                            id : _txtFilter1
                            text: ":"
                            font.pointSize: 12
                            width: 20
                        }
                        TextField{
                            id: txtFilter1
                            placeholderText: "description"

                            Keys.onPressed: (event)=> {
                                                if (event.key === Qt.Key_Enter || event.key === 16777220) {
                                                    //console.log("pressed enter")
                                                    tagsModel.append({name: comboFilter1.currentText, signLogical: " : " , value1: txtFilter1.text, isTo:'' , value2:'', filter:"filter1"})
                                                    myProxyModel.addTag1("filter", comboFilter1.currentText, txtFilter1.text);
                                                }
                                            }

                            //                        MouseArea{
                            //                            anchors.fill: parent
                            //                            acceptedButtons: Qt.LeftButton | Qt.RightButton | Qt.Key_Enter
                            //                            onClicked: {
                            //                                if(mouse.button === Qt.Key_Enter){
                            //                                    console.log("enter pressed")
                            //                                }
                            //                            }
                            //                        }

                        }
                    }

                    RowLayout{
                        ComboBox{
                            id: comboFilter2
                            model: myProxyModel.getDataComboBoxInt()
                        }
                        Text{
                            text: ":"
                            font.pointSize: 12
                            width: 20
                            onTextChanged: {

                            }
                        }
                        TextField{
                            id: txtFromFilter2
                            placeholderText: "numberFrom"
                        }
                        Text{
                            text: "To"
                            font.pointSize: 12
                            width: 20
                        }
                        TextField{
                            id: txtToFilter2
                            placeholderText: "numberTo"

                            Keys.onPressed: (event)=> {
                                                if (event.key === Qt.Key_Enter || event.key === 16777220) {
                                                    //console.log("pressed enter")
                                                    tagsModel.append({name: comboFilter2.currentText, signLogical: " : "  , value1: txtFromFilter2.text, isTo: " To " , value2: txtToFilter2.text, filter: "filter2"})
                                                    myProxyModel.addTag2("filter", comboFilter2.currentText, txtFromFilter2.text, txtToFilter2.text)
                                                }
                                            }
                        }
                    }
                    RowLayout{
                        ComboBox{
                            id: comboFilter3
                            model: myProxyModel.getDataComboBoxInt()
                        }
                        Text{
                            id : _txtFilter3
                            text: "="
                            font.pointSize: 12
                            width: 20
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    contextMenu.popup()

                                }
                                Menu {
                                    id: contextMenu
                                    MenuItem {
                                        id: menuSmaller
                                        text: "<"
                                        onClicked: {
                                            _txtFilter3.text = menuSmaller.text
                                        }
                                    }
                                    MenuItem {
                                        id: menuSmallerEqual
                                        text: "<="
                                        onClicked: {
                                            _txtFilter3.text = menuSmallerEqual.text
                                        }
                                    }
                                    MenuItem {
                                        id: menuEqual
                                        text: "="
                                        onClicked: {
                                            _txtFilter3.text = menuEqual.text
                                        }
                                    }

                                    MenuItem {
                                        id: menuBigger
                                        text: ">"
                                        onClicked: {
                                            _txtFilter3.text = menuBigger.text
                                        }
                                    }
                                    MenuItem {
                                        id: menuBiggerEqul
                                        text: ">="
                                        onClicked: {
                                            _txtFilter3.text = menuBiggerEqul.text
                                        }
                                    }

                                }
                            }
                        }
                        TextField{
                            id: txtFilter3
                            placeholderText: "number"

                            Keys.onPressed: (event)=> {
                                                if (event.key === Qt.Key_Enter || event.key === 16777220) {
                                                    //console.log("pressed enter")
                                                    tagsModel.append({name: comboFilter3.currentText, signLogical: _txtFilter3.text, value1: txtFilter3.text, isTo: "" , value2: "", filter: "filter3"})
                                                    myProxyModel.addTag3("filter", comboFilter3.currentText, txtFilter3.text, _txtFilter3.text)
                                                }
                                            }
                        }
                    }
                }
                Flow{
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.leftMargin: 5
                    ListView {
                        width: parent.width
                        height: 60
                        orientation: ListView.Horizontal

                        model: ListModel {
                            id: tagsModel

                        }

                        delegate:
                            ButtonTag{ name: model.name; signLogical: model.signLogical; value1: model.value1; isTo: model.isTo ; value2: model.value2 ; filter: model.filter }

//                        Component.onCompleted: {
//                            tagsModel.append({ name: "color", value: "red" })
//                            tagsModel.append({ name: "color", value: "green" })
//                            tagsModel.append({ name: "color", value: "blue" })
//                            tagsModel.append({ name: "color", value: "pink" })
//                        }
                    }
                }
            }


        }
        Rectangle{
            id: popInSearchRect
            color: "#DEE3E6"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.bottomMargin: 0.5
            Button{
                id: btnShowSearch
                anchors.horizontalCenter: parent.horizontalCenter
                Layout.topMargin: 30
                text: "Search"
                property bool showSearch: false
                onClicked: {
                    myProxyModel.getColorFilter()
                    if(showSearch === false){
                        filterSearchRect.visible = false
                        showSearch = true
                    }
                    else if(showSearch === true){
                        filterSearchRect.visible = true
                        showSearch = false
                    }
                }
            }
        }

        Rectangle{
            id: categoryRect
            color: "#DEE3E6"
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.bottomMargin: 1
            Layout.leftMargin: 20
            TabBar {
                id: tabBar
                width: parent.width
                Component.onCompleted: {
                    myProxyModel.filterStringColumn(repeater.itemAt(0).text) //myProxyModel.getTabBarName()[0]
                    console.log(repeater.itemAt(0).text)
                }

                readonly property color foregroundColor: "#003569"
                readonly property color disableColor: Qt.rgba(foregroundColor.r, foregroundColor.g, foregroundColor.b, 0.5)
                Repeater {
                    id: repeater
                    model: myProxyModel.getTabBarName()

                    TabButton {
                        id: tabMain
                        required property var model
                        required property var modelData

                        text: modelData

                        onClicked: {
                            console.log("show table: ", txtTabbar.text)
                            myProxyModel.filterStringColumn(txtTabbar.text)
                        }
                        background: Rectangle{
                            id: tabBarBack
                            //implicitWidth: 20
                            //implicitHeight: 20
                            color: tabBarBack.down ? "#DEE3E6" : "transparent"
                            //radius: tabBarBacks.implicitWidth
                            Rectangle {
                                id: rectBackTabbar
                                width: parent.width
                                height: 2
                                color: tabBar.currentIndex === model.index ? tabBar.foregroundColor : tabBar.disableColor
                                anchors.bottom: parent.bottom
                            }
                        }
                        contentItem: Text{
                            id: txtTabbar
                            //anchors.fill: parent
                            anchors.centerIn: parent
                            text: tabMain.text
                            font.family: "Roboto"
                            font.pointSize: 17 / rootItem.monitorRatio
                            color: tabBar.currentIndex === model.index ? tabBar.foregroundColor : tabBar.disableColor
                        }
                    }
                }

            }
        }

        Rectangle{
            id: tableviewRect
            color: "#DEE3E6"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.bottomMargin: 12

//            Rectangle {
//                anchors.fill: parent
//                color: 'pink'
//                //z: -20
//            }

            HorizontalHeaderView{
                anchors.left: tableview.left
                anchors.bottom: tableview.top
                syncView: tableview
                clip: true
                delegate: Rectangle{
                    id: rectHorizontalHeaderView
                    implicitHeight: 30
                    implicitWidth: 50 //parent.width
                    color: "transparent"//"#DEE3E6"
                    Rectangle {
                        width: parent.width
                        height: 2
                        color: "#003569"
                        anchors.bottom: parent.bottom
                    }
                    Text{
                        text: display
                        color: "#003569"
                        font.family: "Roboto"
                        font.pointSize: 17 / rootItem.monitorRatio
                        //anchors.centerIn: parent
                        anchors.left: model.column === 2 ? parent.left : undefined
                        anchors.centerIn: model.column === 2 ? undefined : parent
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.leftMargin: model.column === 2 ? -tableview.columnZero - tableview.columnIcons : 0

                        visible: model.column !== 0 && model.column !== 1 && model.column !== myProxyModel.columnCount()-1 && model.column !== myProxyModel.columnCount()-2 && model.column !== myProxyModel.columnCount()-3
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            //                            console.log(model.index)
                            console.log(model.index) //model : data displayRole in c++
                            myProxyModel.sortTable(model.index) // model : data index in c++
                        }
                    }
                }
            }

            //            VerticalHeaderView{
            //                anchors.right: tableview.left
            //                anchors.top: tableview.top
            //                syncView: tableview
            //                clip: true
            //            }



                TableView{
                    id: tableview
                    Layout.fillWidth: true
                    //Layout.fillHeight: true
                    anchors.fill: parent
                    //Layout.alignment: Qt.AlignLeft
                    anchors.leftMargin: 20
                    anchors.topMargin: 20
                    //                anchors.centerIn: rectTableView
                    selectionBehavior: TableView.SelectRows //tableview.SelectRows
                    property int selectRowModel: -1
                    property int columnZero: 5 //tableview.width / myProxyModel.columnCount() / 7
                    property int columnIcons: 35 //tableview.width / myProxyModel.columnCount() / 2

                    //columnSpacing: 1
                    rowSpacing: 1
                    clip: true
                    //        topMargin: 50

                    function oddRow(IndexRow) {
                        return IndexRow % tableview.rows
                        //                return tableview.rows % IndexRow
                    }

                    model: myProxyModel //tableModel //myProxyModel

                    selectionModel: myProxyModel.selectRowModel()

                    //                selectionMode: tableview.SingleSelection

                    delegate: Rectangle {
                        //Component.onCompleted: console.log("index " + model.index +" created!")
                        //Component.onDestruction: console.log("index " + model.index +" destructed!")
                        id: rectDelegate
                        //implicitWidth: 120 //rootItem.width / myProxyModel.columnCount() //120 //rootItem.height / 3
                        implicitHeight: 32
                        radius: model.column === 0 ? 10 : 0
                        color: selected ? "lightblue" : background
                        //anchors.right: column === myProxyModel.columnCount()-1 ? parent.right : undefined

                        required property bool selected
                        property int idxRow: model.row
                        property int rowCount : myProxyModel.getColumnCount()
                        property int columnCnt: myProxyModel.columnCount()
                        Image {
                            id: icons
                            anchors.centerIn: parent
                            //source: model.column === 1 || model.column === 15 || model.column === 16 || model.column === 17 ? decorate : "icons/airplane.png" //"icons/airplane.png" //decorate
                            source: model.column === 1 || model.column === myProxyModel.columnCount()-1 || model.column === myProxyModel.columnCount()-2 || model.column === myProxyModel.columnCount()-3  ? decorate : "icons/airplane.png"
                            width: 30
                            height: 30
                            //visible: model.column === 1 || model.column === 15 || model.column === 16 || model.column === 17
                            visible: model.column === 1 || model.column === myProxyModel.columnCount()-1 || model.column === myProxyModel.columnCount()-2 || model.column === myProxyModel.columnCount()-3
                        }

                        Text {
                            text: display /* === undefined ? 'blank' : display*/
                            font.pointSize: 17 / rootItem.monitorRatio
                            font.family: "Roboto"
                            color: "#003569"
                            //anchors.fill: parent
                            //anchors.centerIn: parent
                            anchors.left: model.column === 2 ? parent.left : undefined
                            anchors.centerIn: model.column === 2 ? undefined : parent
                            anchors.verticalCenter: parent.verticalCenter
                            visible: model.column !== 0 && model.column !== 1 && model.column !== myProxyModel.columnCount()-3 && model.column !== myProxyModel.columnCount()-2 && model.column !== myProxyModel.columnCount()-1
                        }
                        Rectangle {
                            width: parent.width
                            height: 1
                            color: "#003569"
                            opacity: 0.2
                            anchors.bottom: parent.bottom
                        }

                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                //tableview.selectRowModel = model.row
                                //myProxyModel.selectionRow(rowCount, idxRow);
                                console.log("Row index: ", idxRow)
                                //console.log("column count : ", rowCount)
                                console.log("column filter count: ", myProxyModel.columnCount())
                            }
                        }
                    }

                    columnWidthProvider: function (column) {
                                            var columnProviderSize = rootItem.width / (myProxyModel.columnCount() - 2)
                                            //console.log(rootItem.width / myProxyModel.columnCount())
                                            return column === 0  ? tableview.columnZero : (column === 1 || column === myProxyModel.columnCount()-2 || column === myProxyModel.columnCount()-3 ? tableview.columnIcons : columnProviderSize);
                        //return tableview.width / myProxyModel.columnCount();
                    } //rectDelegate.implicitWidth

                }

        }
    }
}
