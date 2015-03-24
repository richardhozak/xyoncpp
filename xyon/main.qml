import QtQuick 2.4
import QtQuick.Window 2.2
import QtMultimedia 5.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Window {
    visible: true
    //title: "AudioTest"
    width: 400
    height: 600
    id: window
    //flags: Qt.Drawer
    color: "dodgerblue"
    minimumWidth: width
    minimumHeight: height
    maximumWidth: width
    maximumHeight: height

    ListView {
        anchors.fill: parent
        model: controller.playlist.items
        delegate: Text {
            text: object.title
        }
    }

    Component.onCompleted: {
        console.log("controller playlist", controller.playlist);
        console.log("controller playlist items", controller.playlist.items);
    }

    Search {
        id: search
        height: parent.height
        width: 350
        color: "#242424"
        x: isExpanded ? 0 : -width
        property bool isExpanded: false

        Behavior on x {
            NumberAnimation { duration: 200; easing.type: Easing.OutCubic }
        }

        Image {
            anchors.left: parent.right
            width: 50
            height: 50
            //color: "white"
            source: "images/diamond.png"
            rotation: search.isExpanded ? 90 : -90


            Behavior on rotation {
                NumberAnimation { duration: 100 }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: search.isExpanded = !search.isExpanded
            }
        }
    }
}
