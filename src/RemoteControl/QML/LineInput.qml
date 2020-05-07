import QtQuick 2.0

FocusScope {
    id: wrapper

    // 定义可通过元对象系统访问的属性
    property alias text: input.text
    property alias hint: hint.text
    property int fontSize: 18

    // 自定义信号
    signal accepted

    Rectangle {
        anchors.fill: parent
        border.color: "#707070"
        color: "#c1c1c1"
        radius: 4

        // 输入栏隐藏文本
        Text {
            id: hint
            anchors { fill: parent; leftMargin: 14 }
            verticalAlignment: Text.AlignVCenter
            text: "Enter word"
            font.pixelSize: fontSize
            color: "#707070"
            opacity: input.length ? 0 : 1
        }

        TextInput {
            id: input
            focus: true
            anchors { left: parent.left; leftMargin: 14; right: parent.right; top: parent.top; bottom: parent.bottom }
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: fontSize
            color: "black"
            maximumLength: 8

            onAccepted: wrapper.accepted()
        }
    }
}
