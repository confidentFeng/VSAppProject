#pragma once

#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSettings>
#include <QKeyEvent>
#include <QProcess>
#include <QTimer>
#include <QDebug>

using namespace std;

// 将字符串的编码修改为"utf-8"，便于显示中文以及允许http的Get方式传输中文
#pragma execution_character_set("utf-8")

#define IS_DEBUG 0 // 是否为Debug开发版本

#define WIN_WIDTH 1920
#if IS_DEBUG
#define WIN_HEIGHT 1080
#else
#define WIN_HEIGHT 1280
#endif

#define REGEXP_IP "((?:(?:25[0-5]|2[0-4]\\d|[01]?\\d?\\d)\\.){3}(?:25[0-5]|2[0-4]\\d|[01]?\\d?\\d))"
#define REGEXP_PORT "^[0-9]{1,4}"
#define REGEXP_ACCOUNT "^[A-Za-z0-9]{0,15}$"
#define REGEXP_PASSWD "^[A-Za-z0-9]+${6,15}$"

#define HTTP_TEST 1

#define BINDHOST_OUTTIME 500 // 至少350ms

class Common
{
public:
	Common();
	~Common();
	static Common *Get()
	{
		static Common ct;
		return &ct;
	}
	QString ExecuteCmd(const QString& strCmd); // 执行cmd命令
};