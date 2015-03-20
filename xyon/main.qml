import QtQuick 2.4
import QtQuick.Window 2.2
import QtMultimedia 5.0
import QtQuick.Controls 1.2

Window {
    visible: true
    title: "AudioTest"
    width: 400
    height: 550
    id: rootWindow

    Rectangle {
        id: inputArea
        color: "yellow"
        width: parent.width
        height: 22

        TextInput {
            id: input
            anchors.fill: parent
            onEditingFinished: controller.search(text)
            focus: true
        }
    }

    Rectangle {
        height: parent.height - inputArea.height - navigation.height
        width: parent.width
        anchors.top: inputArea.bottom
        clip: true
        color: "wheat"

        ListView {
            anchors.fill: parent
            model: searchList
            delegate: MouseArea {
                height: 25
                width: parent.width
                //color: "white"

                Text {
                    text: object.title
                }

                onDoubleClicked: controller.playId(object.id)
            }
        }
    }

    Item {
        id: navigation
        height: 100
        width: parent.width
        anchors.bottom: parent.bottom

        Item {
            width: parent.width
            height: 50
            Button {
                anchors.left: parent.left
                height: parent.height
                width: parent.height
                text: "<"
            }

            Text {
                id: pos
                anchors.left: parent.left
                anchors.leftMargin: 100
                text: mediaPlayer.position
            }

            Text {
                id: delim
                text: "/"
                anchors.left: pos.right
            }

            Text {
                id: duration
                anchors.left: delim.right
                text: mediaPlayer.duration
            }

            Text {
                text: mediaPlayer.seekable
                anchors.left: parent.left
                anchors.leftMargin: 100
                anchors.top: pos.bottom
            }

            Button {
                anchors.right: parent.right
                height: parent.height
                width: parent.height
                text: ">"
                onClicked: controller.test()
            }
        }

        Item {
            height: 50
            width: parent.width
            anchors.bottom: parent.bottom
            Slider {
                anchors.fill: parent
                maximumValue: mediaPlayer.duration
                minimumValue: 0
                value: mediaPlayer.position
                enabled: mediaPlayer.seekable
                onValueChanged: {
                    if (mediaPlayer.position > value + 25 || mediaPlayer.position < value - 25)
                    {
                        mediaPlayer.setPosition(value)
                    }
                }
            }
        }
    }

//    Button {
//        id: button
//        anchors.right: parent.right
//        anchors.bottom: parent.bottom
//        onClicked: controller.search(input.text)
//        text: "Search"
//        isDefault: true
//    }

    property variant clickPos

    MouseArea {
        anchors.fill: parent

        onPressed: {
            clickPos  = Qt.point(mouse.x,mouse.y)
        }

        onPositionChanged: {
            console.log(mouse.x, mouse.y);
            var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
            rootWindow.x = rootWindow.x+delta.x;
            rootWindow.y = rootWindow.y+delta.y;
            clickPos = delta
        }
    }
}
