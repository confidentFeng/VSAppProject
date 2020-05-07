#pragma once
#include "common.h"

class ForgetPasswd : public QDialog
{
	Q_OBJECT

public:
	ForgetPasswd(QDialog *parent = Q_NULLPTR, const QString& strWifiName = "");
	~ForgetPasswd();

private:
	QWidget *m_pWidgetChild; // �ӽ���
	QPushButton *m_pBtnClose; // �رհ�ť
	QLabel *m_pLabIcon; // ͼ���ǩ
	QLabel *m_pLabWifi; // wifi���Ʊ�ǩ
	QPushButton *m_pBtnForget; // �������밴ť
	QPushButton *m_pBtnCancel; // ȡ����ť
};
