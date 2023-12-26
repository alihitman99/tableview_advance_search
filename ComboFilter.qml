import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

    ComboBox {
        id: control
        model: myProxyModel.getDataComboBox()

        delegate: ItemDelegate {
            id: delegate

            required property var model
            required property int index

            width: control.width
            contentItem: Text {
                text: delegate.model[control.textRole]
                color: "#21be2b"
                font: control.font
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
            }
            highlighted: control.highlightedIndex === index
        }

        indicator:Rectangle{
            x: control.width - width - control.rightPadding
            y: control.topPadding + (control.availableHeight - height) / 2
            width: 12
            height: 8
            //color: "green"
        }
            /*Canvas {
            id: canvas
            x: control.width - width - control.rightPadding
            y: control.topPadding + (control.availableHeight - height) / 2
            width: 12
            height: 8
            contextType: "2d"

            Connections {
                target: control
                function onPressedChanged() { canvas.requestPaint(); }
            }

            onPaint: {
                context.reset();
                context.moveTo(0, 0);
                context.lineTo(width, 0);
                context.lineTo(width / 2, height);
                context.closePath();
                context.fillStyle = control.pressed ? "#17a81a" : "#21be2b";
                context.fill();
            }
        }*/

        contentItem: TextField {
            id: txtContentItem
            leftPadding: 0
            rightPadding: control.indicator.width + control.spacing

            text: "a"
            font: control.font
            color: control.pressed ? "#17a81a" : "#21be2b"
            verticalAlignment: Text.AlignVCenter
            //elide: Text.ElideRight
            onTextChanged:  {
                if(txtContentItem.text !== ""){
                    for(var i = 0; i < control.count; ++i){
                        //console.log(control.textAt(i))
                        if(control.textAt(i) === txtContentItem.text){
                            control.textAt(1).visible = false
                        }

                    }
                    control.delegateModel.remove(1)
                    //console.log(control.textAt(1))
                    myProxyModel.setSearchCombo(txtContentItem.text)

                    //console.log(listCombo.model.append({"aaaa"}))
                    popupCombo.open()
                }
                if(txtContentItem.text === ""){
                    console.log("close")
                    popupCombo.close()
                }
            }
        }

        background: Rectangle {
            implicitWidth: 120
            implicitHeight: 40
            border.color: control.pressed ? "#17a81a" : "#21be2b"
            border.width: control.visualFocus ? 2 : 1
            radius: 2
        }

        popup: Popup {
            id: popupCombo
            y: control.height - 1
            width: control.width
            implicitHeight: contentItem.implicitHeight
            padding: 1

            contentItem: ListView {
                id: listCombo
                clip: true
                implicitHeight: contentHeight
                model: control.delegateModel//control.popup.visible ? control.delegateModel : null
                currentIndex: control.highlightedIndex

                ScrollIndicator.vertical: ScrollIndicator { }
            }

            background: Rectangle {
                border.color: "#21be2b"
                radius: 2
            }
        }
    }

