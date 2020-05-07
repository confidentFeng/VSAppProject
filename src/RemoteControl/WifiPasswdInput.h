#pragma once
#include "common.h"
#include "XmlHelper.h"
#include "MyPromptBox.h"

class WifiPasswdInput : public QDialog
{
	Q_OBJECT

public:
	WifiPasswdInput(QDialog *parent = Q_NULLPTR, const QString& strWifiName="");
	~WifiPasswdInput();

private:
	QWidget *m_pWidgetChild; // 子界面
	QPushButton *m_pBtnClose; // 关闭按钮
	QLabel *m_pLabPasswd; // 密码标签
	QLineEdit *m_pEditPasswd; // 密码文本框
	QPushButton *m_pBtnOK; // 确定按钮
	QPushButton *m_pBtnCancel; // 取消按钮
};
