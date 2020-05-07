import QtQuick 2.9

Rectangle {
    id: loginWin
    width: 320
    height: 480
    SystemPalette { id: activePalette }

    // 背景图片
    Image
    {
        id: background
        anchors { top: parent.top; bottom: parent.bottom }
        anchors.fill: parent
        //source: "./background.jpeg"
        fillMode: Image.PreserveAspectCrop
    }

    // 顶栏
    Item
    {
        id: topBar
        width: loginWin.width; height: loginWin.height*0.05
        anchors.top: loginWin.top
        anchors.topMargin: 20

        Text
        {
            id: title
            anchors { top: parent.top; horizontalCenter: parent.horizontalCenter }
            text: "绑定录播主机"
            font.bold: true
            font.pointSize: loginWin.height * 0.05 * 0.7
            color: "black"
        }
    }

    // 空白栏
    Item
    {
        id: space
        width: loginWin.width; height: loginWin.height * 0.1
        anchors.top: topBar.bottom
    }

    // 登录框
    Rectangle {
        id: loginRect
        width: loginWin.width * 0.8
        height: loginWin.height * 0.6
        anchors { top: space.bottom; horizontalCenter: parent.horizontalCenter }
        border.color: "#707070"
        color: "transparent"

        LineInput
        {
            id: line
            width: loginRect.width * 0.8; height: loginRect.height * 0.1
            fontSize:height * 0.3
            anchors { horizontalCenter: loginRect.horizontalCenter; top: loginRect.top; topMargin: 8 }
            hint: "请输入录播主机IP"

        }

        LineInput
        {
            width: loginRect.width * 0.8; height: loginRect.height * 0.1
            fontSize:height * 0.3
            anchors { horizontalCenter: loginRect.horizontalCenter; bottom: loginButton.top;  bottomMargin: loginRect.height * 0.1 }
            hint: "请输入录播主机端口号"
        }

//        LineInput
//        {
//            width: loginRect.width * 0.8; height: loginRect.height * 0.1
//            fontSize:height * 0.3
//            anchors { horizontalCenter: loginRect.horizontalCenter; bottom: loginButton.top;  bottomMargin: loginRect.height * 0.1 }
//            hint: "请输入录播主机端口号"
//        }

        Button
        {
            id: loginButton
            width: loginRect.width * 0.35; height: loginRect.height * 0.2
            anchors { left: loginRect.left; leftMargin: 28; bottom: loginRect.bottom; bottomMargin: 8 }
            text: "保存"
            //onClicked: sameGame.startNewGame()
            color: "#409EFF"
        }
    }
}
