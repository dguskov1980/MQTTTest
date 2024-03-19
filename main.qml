import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 500
    height: 500
    title: "TEST MQTT"

    ColumnLayout {
        anchors.fill: parent
        spacing: 10
        TextField {
            id:host
            Layout.fillWidth: true
            placeholderText: "Host"
            text:"emqx.public-broker.com"
        }
        TextField {
            id:port
            Layout.fillWidth: true
            placeholderText: "Port"
            text:"1883"
        }
        TextField {
            id:username
            Layout.fillWidth: true
            placeholderText: "Username"
        }

        TextField {
            id:password
            Layout.fillWidth: true
            placeholderText: "Password"
            echoMode: TextInput.Password
        }
        TextField {
            id:topic
            Layout.fillWidth: true
            placeholderText: "Topic"
            text:"qmqtt/test_data"
        }
        TextField {
            id:filepath
            Layout.fillWidth: true
            placeholderText: "Filepath"
            text:"H:/qtmqtt-dev/test_mqtt.txt"
        }
        Text {
            id: displayText
            Layout.fillWidth: true
            text: "Данные будут отображаться здесь"
        }
        Text {
            id: subsciberData
            Layout.fillWidth: true
            text: "Данные будут отображаться здесь"
        }
        Button {
            Layout.alignment: Qt.AlignHCenter
            text: "RUN"
            onClicked: {
                // Логика для обработки нажатия кнопки RUN
                displayText.text = "";
                PublisherThread.doWork(host.text,username.text, password.text, port.text, topic.text,filepath.text);
                console.log("Кнопка RUN нажата")
            }
        }
    }
    Connections {
        target: PublisherThread
        onSetData: {
            displayText.text = data
        }
        onSetSubsciberData: {
            subsciberData.text = data
        }
    }
}
