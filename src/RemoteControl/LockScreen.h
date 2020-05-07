#pragma once
#include <QRegExpValidator>
#include "common.h"
#include "MyPromptBox.h"

class LockScreen : public QWidget
{
	Q_OBJECT

public:
	LockScreen(QWidget *parent = Q_NULLPTR);
	~LockScreen();

private slots:
	void EnterSlot(); // 文本框回车键响应的槽函数

private:
	QWidget *m_pWidgetChild; // 子界面
	QLabel *m_pLabHead; // 头像标签
	QLabel *m_pLabAccount; // 录播主机账号标签
	QLineEdit *m_pEditPasswd; // 录播主机密码文本框
};
