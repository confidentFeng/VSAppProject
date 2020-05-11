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

// ���ַ����ı����޸�Ϊ"utf-8"��������ʾ����
#pragma execution_character_set("utf-8")

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// Ӧ��ȫ�ּ�����ʽ��
	QFile qssFile(QApplication::applicationDirPath() + "/image/myStyleSheet.qss");
	//QFile qssFile("./image/myStyleSheet.qss");
	qssFile.open(QFile::ReadOnly);
	qApp->setStyleSheet(qssFile.readAll());

	// ʹ��QStackedWidget�л�������ʾ
	StackedWidget *pMainWidget = new StackedWidget;
	pMainWidget->SetStackCurIndex(0);
	int res = pMainWidget->exec();

	return a.exec();
}