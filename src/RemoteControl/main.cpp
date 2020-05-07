#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QFileInfo>
#include "BindHost.h"
#include "NetConfig.h"
#include "WirelessCon.h"
#include <QStackedWidget>
#include "WifiItemWidget.h"
#include "WifiPasswdInput.h"
#include "ForgetPasswd.h"
#include "MainWindow.h"

// 将字符串的编码修改为"utf-8"，便于显示中文以及允许http的Get方式传输中文
#pragma execution_character_set("utf-8")

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// 应用全局加载样式表
	QFile qssFile(QApplication::applicationDirPath() + "/image/myStyleSheet.qss");
	//QFile qssFile("./image/myStyleSheet.qss");
	qssFile.open(QFile::ReadOnly);
	qApp->setStyleSheet(qssFile.readAll());

	// 显示主界面
	MainWindow *m_pMainWindow = new MainWindow;
	m_pMainWindow->show();

	return a.exec();
}