import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts


ComboBox{
    id: comboFilter1
    property real txtWidth: 0
    property string comboFilterName: txtContentItem.text
    Layout.minimumWidth: 50
    Layout.maximumWidth: 50
    //model: myProxyModel.getDataComboBox()

    function findLongestString(stringList) {
        var longest = "";

        for (var i = 0; i < stringList.length; i++) {
            if (stringList[i].length > longest.length) {
                longest = stringList[i];
            }
        }

        return longest;
    }
    Text {
        id:maximumText
        text: "Longest String: " + comboFilter1.findLongestString(comboFilter1.model)
        anchors.centerIn: parent
        Component.onCompleted: {comboFilter1.txtWidth = maximumText.width}
        visible : false
    }
    delegate: ItemDelegate {
        id:itemDelegate
        implicitWidth: comboFilter1.txtWidth
        background:Rectangle{
            width:  comboFilter1.txtWidth
            color:"yellow"
            border.width: .3
            border.color: "black"
            //                                    radius:5
        }

        contentItem: Text {
            //Layout.leftMargin: 20
            text: comboFilter1.textRole
                  ? (Array.isArray(comboFilter1.model) ? modelData[comboFilter1.textRole] : model[comboFilter1.textRole])
                  : modelData
            color: "blue"
            //font.family: style.fontFamily
            //font.pixelSize: 14/style.monitorRatio
        }

        //                                highlighted: comboFilter1.highlightedIndex === index
    }
    indicator:Rectangle{}

    contentItem: TextField {
        id: txtContentItem
        leftPadding: 0
        rightPadding: comboFilter1.indicator.width + comboFilter1.spacing

        //text: "a"
        font: comboFilter1.font
        color: comboFilter1.pressed ? "#17a81a" : "#21be2b"
        verticalAlignment: Text.AlignVCenter
        placeholderText: "subject"
        onTextChanged: {
            if(txtContentItem.text !== ""){
                if(nameFilter === "String"){
                    //console.log("string pass")
                    comboFilter1.model = myProxyModel.filterCombo(text, nameFilter);
                }
                else if(nameFilter === "Int"){
                    //console.log("Int pass")
                    comboFilter1.model = myProxyModel.filterCombo(text, nameFilter);
                }
                popupCombo.open()
            }
            if(txtContentItem.text === ""){
                //console.log("close combo")
                popupCombo.close()
            }
        }
    }

    background: Rectangle {
        color: "transparent"
    }
    popup:
        Popup {
            id: popupCombo
            y: comboFilter1.height - 1
            width: comboFilter1.width
            implicitHeight: contentItem.implicitHeight
            padding: 1

            contentItem: ListView {
                id: listCombo
                clip: true
                implicitHeight: contentHeight
                model: comboFilter1.delegateModel//comboFilter1.popup.visible ? comboFilter1.delegateModel : null
                currentIndex: comboFilter1.highlightedIndex
                //visible: false
                ScrollIndicator.vertical: ScrollIndicator { }
            }

            background: Rectangle {
                border.color: "#21be2b"
                radius: 2
            }
        }
        /*Popup {
        id: popupCombo
        y: comboFilter1.height
        x:-5
        width: comboFilter1.width
        implicitHeight: contentItem.implicitHeight +2
        padding: 1
        enter: Transition {
            NumberAnimation { property: "opacity"; from: 0.0; to: 1.0 }}


        exit:Transition {
            NumberAnimation { property: "opacity"; from: 1.0; to: 0.0 }}

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: comboFilter1.popup.visible ? comboFilter1.model: null


            currentIndex: 0
            delegate: TextField {
                padding:0
                leftPadding:3
                height: comboFilter1.displayText !== modelData?implicitHeight : 1
                text: modelData

                MouseArea{
                    anchors.fill: parent
                    onClicked: comboFilter1.displayText = modelData
                }
                background: Rectangle{

                    color:"green"
                    width: comboFilter1.width - 5
                    height:comboFilter1.height + 2
                    radius: 5

                }
                visible:comboFilter1.displayText !== modelData
            }

            ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle {
            color:"transparent"
            radius: 5
        }
    }*/

}
