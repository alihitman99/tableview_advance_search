import QtQuick
import QtQuick.Controls.Fusion


Button {
    id: btnMainTag
    property string name: 'default'
    property string signLogical: ':'
    property string value1: 'red'
    property string isTo: ''
    property string value2: ''
    property string filter: "color"

    function btnTagColor(valueColor){
        btnTagg.border.color = valueColor; txtCloseTag.color = valueColor;
        txtTagName.color = valueColor; txtTagSign.color = valueColor; txtTagValue1.color = valueColor;
        txtTagIsTo.color = valueColor; txtTagValue2.color = valueColor
    }

    checkable: true

    contentItem: Text{
        Row{
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 10
            Text{
                id: txtTagName
                text: name
                color: "#01AED6"
            }
            Text{
                id: txtTagSign
                text: signLogical
                color: "#01AED6"
            }
            Text{
                id: txtTagValue1
                text: value1
                color: "#01AED6"
            }
            Text{
                id: txtTagIsTo
                text: isTo
                color: "#01AED6"
            }
            Text{
                id: txtTagValue2
                text: value2
                color: "#01AED6"
            }
        }
    }

    background: Rectangle {
        id: btnTagg
        implicitWidth: 100
        implicitHeight: 20
        //width: 100
        //height: 18
        color: btnTagg.down ? "#DEE3E6" : "#DEE3E6"
        border.color: "#01AED6"
        border.width: 1
        radius: btnTagg.implicitWidth //btnTag.width //btnTag.implicitWidth



    }
    Rectangle{
        id: btnCloseTagg

        anchors.right: btnTagg.right

        //anchors.bottom: btnTagg.bottom
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 5
        implicitWidth: btnTagg.implicitWidth / 5//btnTag.width / 5 //btnTag.implicitWidth / 5
        implicitHeight: btnTagg.implicitHeight
        //radius: btnTag.implicitWidth / 5
        color: "#DEE3E6"
        radius: btnCloseTagg.implicitHeight
        Text{
            id: txtCloseTag
            anchors.centerIn: parent
            text: "X"
            color: "#01AED6"

        }
        MouseArea{
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                //remove the Tag
                //indexToRemove = model.index
                console.log("remove tag: ",model.index)
                //console.log(filter)
                myProxyModel.removeTag(filter, name, value1)
                tagsModel.remove(model.index, 1)
            }
        }
    }
    onClicked: {
        if(checkable){
            console.log(name, "disable!!")
            myProxyModel.removeTag(filter, name, value1)
            btnTagColor("#003569")
            //btnTagg.border.color = "#003569"
            btnMainTag.checkable = false
        }
        else{
            console.log(name ,"enable!!!")
            if(filter === "colorFilter")
                myProxyModel.addTag("filter", name, value1)
            else if(filter === "filter1")
                myProxyModel.addTag1("filter", name, value1)
            else if(filter === "filter2")
                myProxyModel.addTag2("filter", name, value1, value2)
            else if(filter === "filter3")
                myProxyModel.addTag3("filter", name, value1, signLogical)
            btnTagColor("#01AED6")
            //btnTagg.border.color = "#01AED6"
            btnMainTag.checkable = true
        }
    }


}
