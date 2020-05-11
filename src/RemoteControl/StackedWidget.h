#pragma once
#include <QStackedWidget>
#include "common.h"
#include "NetConfig.h"
#include "WirelessCon.h"
#include "MyPromptBox.h"

class StackedWidget : public QDialog
{
	Q_OBJECT

public:
	StackedWidget(QDialog *parent = Q_NULLPTR);
	~StackedWidget();
	void SetStackCurIndex(const int& index); // ���÷�ҳWidget�ĵ�ǰ����

private:
	WirelessCon *m_pWirelessCon; // �������Ӵ���
	NetConfig *m_pNetConfigWifi; // �������ô���-��������
	QStackedWidget *m_pStackedWidget; // ��ҳWidget
};
