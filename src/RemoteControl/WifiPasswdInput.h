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
	QWidget *m_pWidgetChild; // �ӽ���
	QPushButton *m_pBtnClose; // �رհ�ť
	QLabel *m_pLabPasswd; // �����ǩ
	QLineEdit *m_pEditPasswd; // �����ı���
	QPushButton *m_pBtnOK; // ȷ����ť
	QPushButton *m_pBtnCancel; // ȡ����ť
};
