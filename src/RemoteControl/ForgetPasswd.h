#pragma once
#include "common.h"

class ForgetPasswd : public QDialog
{
	Q_OBJECT

public:
	ForgetPasswd(QDialog *parent = Q_NULLPTR, const QString& strWifiName = "");
	~ForgetPasswd();

private:
	QWidget *m_pWidgetChild; // 子界面
	QPushButton *m_pBtnClose; // 关闭按钮
	QLabel *m_pLabIcon; // 图标标签
	QLabel *m_pLabWifi; // wifi名称标签
	QPushButton *m_pBtnForget; // 忘记密码按钮
	QPushButton *m_pBtnCancel; // 取消按钮
};
