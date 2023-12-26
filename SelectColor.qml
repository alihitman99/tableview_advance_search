import QtQuick
import QtQuick.Controls.Fusion
import QtQuick.Layouts

RowLayout{
    spacing: 8
    Text{
        Layout.leftMargin: 8
        font.pointSize: 12
        text: "Color"
    }
    Button{
        id: btnPre
        //text: "<"
        //anchors.right: frame.left
        //anchors.top: frame.top
        //width: 20
        //height: 20
        background: Rectangle{
            anchors.fill: parent
            //height: 20
            //width: height
            //Layout.alignment: Qt.AlignVCenter
            //radius: height
            color: "#e1e5fc"
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
            }
        }
        contentItem: Text{
            //anchors.fill: parent
            anchors.centerIn: parent
            text: "<"
            font.pointSize: 12

        }


        onClicked: {
            if(hbar.position > 0)
                hbar.position -= 0.15
            console.log(hbar.position)
        }
    }
    Rectangle {
        id: frame
        clip: true
        width: 140
        height: 30
        //border.color: "black"
        color: "#DEE3E6"




            RowLayout{
                spacing: 15
                x: -hbar.position * width
                //y: -vbar.position * height


                Repeater{
                    model: myProxyModel.getColorFilter()
                    Rectangle{
                        id: colorRect1
                        height: 20
                        width: height
                        //Layout.alignment: Qt.AlignVCenter
                        radius: height
                        color: modelData


                        Text{
                            id: txtColorRect
                            text: modelData
                            visible: false
                        }

                        MouseArea{
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                //myProxyModel.searchColor(txtColorRedRect.text)
                                console.log(modelData)
                                //myProxyModel.searchColor(modelData)
                                //myProxyModel.addTag("searchColor", "color", modelData)
                                myProxyModel.addTag("filter", "color", modelData)
                                tagsModel.append({ name: "color", signLogical: " : " , value1: modelData, isTo:'', value2:'', filter:"colorFilter" })
                                myProxyModel.getColorFilter()


                            }

                        }
                    }

                }
            }

        ScrollBar {
                id: hbar
                hoverEnabled: true
                active: hovered || pressed
                orientation: Qt.Horizontal
                //size: frame.width / colorRect1.width
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                visible: false
            }
}
    Button{
        id: btnNext
        //text: ">"
        //width: 20
        //height: 20
        background: Rectangle{
            anchors.fill: parent
            //height: 20
            //width: height
            //Layout.alignment: Qt.AlignVCenter
            //radius: height
            color: "#e1e5fc"
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
            }
        }
        contentItem: Text{
            //anchors.fill: parent
            anchors.centerIn: parent
            text: ">"
            font.pointSize: 12

        }
        onClicked: {

            if(hbar.position < 0.9){
                hbar.position += 0.15

            }
            console.log(hbar.position)
        }
    }
}
