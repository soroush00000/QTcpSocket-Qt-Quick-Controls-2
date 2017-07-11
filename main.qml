import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.1
ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    property var sit : true
    property var space: 540
    signal sendTextToC(string a)
    title: qsTr("Clinet")

    ListModel {
        id: messageModel
    }

    ColumnLayout {
        anchors { fill: parent; margins: 8 }
        spacing: 16


        ListView {
            Layout.fillWidth: true; height: 420
            model: messageModel
            delegate: ItemDelegate { text: model.message; checked: true}
            preferredHighlightEnd: ListView.StrictlyEnforceRange
            clip: true

        }

        RowLayout {
            spacing: 16
            y:200
            Layout.fillWidth: true; Layout.fillHeight: false
            x:300

                TextField {
                    id: textField
                    Layout.fillWidth: true; Layout.fillHeight: true
                    placeholderText: "Write a message..."
                    background: null
                    focus: true
                    Keys.onPressed: {
                            if (event.key == Qt.Key_Enter) {
                                messageModel.append({message: textField.text});
                                sendTextToC(textField.text)
                                textField.text = ""
                            }
                    }
                }
            Button {
                id: send
                Material.foreground: "white"; Material.background: Material.DeepOrange
                Layout.fillHeight: true
                text: "Send"
                onClicked: {
                    if(textField.text != "")
                    messageModel.append({message: textField.text});
                    textField.text = ""
                    sendTextToC(textField.text)
                }


            }
        }
    }
    Page1{}

}

