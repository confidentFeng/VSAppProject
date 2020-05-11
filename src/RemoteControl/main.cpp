#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QFileInfo>
#include <QStackedWidget>
#include "StackedWidget.h"
#include "NetConfig.h"
#include "WirelessCon.h"
#include "WifiItemWidget.h"
#include "WifiPasswdInput.h"
#include "ForgetPasswd.h"

// 将字符串的编码修改为"utf-8"，便于显示中文
#pragma execution_character_set("utf-8")

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// 应用全局加载样式表
	QFile qssFile(QApplication::applicationDirPath() + "/image/myStyleSheet.qss");
	//QFile qssFile("./image/myStyleSheet.qss");
	qssFile.open(QFile::ReadOnly);
	qApp->setStyleSheet(qssFile.readAll());

	// 使用QStackedWidget切换界面显示
	StackedWidget *pMainWidget = new StackedWidget;
	pMainWidget->SetStackCurIndex(0);
	int res = pMainWidget->exec();

	return a.exec();
}