import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

ApplicationWindow {
    visible: true
    width: 400
    height: 300
    title: "QML File Dialog Example"

    Button {
        text: "Choose File"
        anchors.centerIn: parent
        onClicked: fileDialog.open()
    }

    FileDialog {
        id: fileDialog
        title: "Select a File"
        onAccepted: {
            console.log("Selected file: " + fileDialog.selectedFile)
        }
        onRejected: {
            console.log("No file was selected")
        }
    }

}
