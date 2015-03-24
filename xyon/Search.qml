import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Rectangle {

    TextField {
        id: searchField
        width: parent.width - 20
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 10
        anchors.topMargin: 10
        placeholderText: "Search..."
        //verticalAlignment: TextInput.AlignBottom
        style: TextFieldStyle {
            textColor: "black"
            background: Rectangle {
                radius: 2
                implicitWidth: 100
                implicitHeight: 24
                border.color: "#494949"
                border.width: 1
                color: "#dbdbdb"
            }
        }
        onAccepted: controller.search(text)
    }

    Item {
        anchors.top: searchField.bottom
        width: parent.width
        height: parent.height - searchField.height - 10

        ScrollView {
            anchors.fill: parent
            anchors.topMargin: 10

            ListView {
                anchors.fill: parent
                model: searchList
                //spacing: 5
                delegate: Item {
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    height: 50
                    width: parent.width - 20
                    //clip: true

                    Text {
                        anchors.left: addButton.right
                        anchors.leftMargin: hoverArea.containsMouse ? 5 : 0
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        text: object.title
                        color: "#dbdbdb"
                        elide: Text.ElideRight
                        width: parent.width - addButton.width - (hoverArea.containsMouse ? 5 : 0)
                    }
                    Text {
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 5
                        text: object.time
                        color: "#dbdbdb"

                        Rectangle {
                            width: parent.width
                            height: 5
                            color: "#494949"
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: -5
                        }
                    }

                    Rectangle {
                        id: addButton
                        width: hoverArea.containsMouse ? 40 : 0
                        height: parent.height
                        color: addMouseArea.pressed ? Qt.lighter("#494949") : "#494949"
                        clip: true

                        Text {
                            text: "+"
                            font.pixelSize: parent.height / 2
                            anchors.centerIn: parent
                            color: "#dbdbdb"
                        }

                        MouseArea {
                            id: addMouseArea
                            anchors.fill: parent
                            onClicked: {
                                console.log(object);
                                controller.playlist.addYoutubeEntry(object);
                            }
                        }

                        Behavior on width {
                            NumberAnimation { duration: 50 }
                        }
                    }

                    Rectangle {
                        width: parent.width
                        height: 1
                        color: "#494949"
                        anchors.bottom: parent.bottom
                    }

                    MouseArea {
                        id: hoverArea
                        anchors.fill: parent
                        hoverEnabled: true
                        onPressed: {
                            mouse.accepted = false;
                        }
                    }
                }
            }
        }
    }

    //                    Rectangle {
    //                        width: 30
    //                        height: 30
    //                        anchors.left: parent.left
    //                        anchors.bottom: parent.bottom
    //                        color: "transparent"

    //                        Text {
    //                            text: "+"
    //                            font.pixelSize: parent.width * 0.75
    //                            color: "white"
    //                            anchors.centerIn: parent
    //                        }
    //                    }



    //    Rectangle {
    //        anchors.top: parent.top
    //        anchors.left: parent.left
    //        anchors.topMargin: 10
    //        anchors.leftMargin: 10
    //        color: "black"
    //        width: parent.width - 20
    //        height: 25

    //        TextInput {
    //            id: input
    //            anchors.fill: parent
    //            clip: true
    //            color: "white"
    //            height: parent.height
    //            anchors.verticalCenter: parent.verticalCenter
    //        }
    //    }


}

