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

// ���ַ����ı����޸�Ϊ"utf-8"��������ʾ�����Լ�����http��Get��ʽ��������
#pragma execution_character_set("utf-8")

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// Ӧ��ȫ�ּ�����ʽ��
	QFile qssFile(QApplication::applicationDirPath() + "/image/myStyleSheet.qss");
	//QFile qssFile("./image/myStyleSheet.qss");
	qssFile.open(QFile::ReadOnly);
	qApp->setStyleSheet(qssFile.readAll());

	// ��ʾ������
	MainWindow *m_pMainWindow = new MainWindow;
	m_pMainWindow->show();

	return a.exec();
}