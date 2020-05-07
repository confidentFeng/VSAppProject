#pragma once
#include <QPainter>
#include <QListWidgetItem>
#include <QList>
#include "common.h"
#include "NetConfig.h"
#include "MyMessageBox.h"
#include "WifiItemWidget.h"
#include "WifiPasswdInput.h"
#include "ForgetPasswd.h"
#include "CmdThread.h"

class WirelessCon : public QDialog
{
	Q_OBJECT

public:
	WirelessCon(QDialog *parent = Q_NULLPTR);
	~WirelessCon();
	bool IsCableAccess(); // ��������Ƿ����

signals:
	void BtnNextWifi(); // ��һ�����������������ý�����ź�
	void BtnNextWired(); // ��һ�����������������ý�����ź�
	void StackedWidgetClose(); // StackedWidget����رյ��ź�

public slots:
	void clickedWifiItem(QListWidgetItem* curItem); // WifiItemWidget����¼�-��Ӧ����

private:
	QWidget *m_pWidgetChild; // �ӽ���
	QLabel *m_pLabTitle; // �����ǩ
	QPushButton *m_pBtnClose; // �رհ�ť
	QLabel *m_pLabInfo; // ��Ϣ��ǩ
	QPushButton *m_pBtnWired; // �������Ӱ�ť

	QListWidget *pListWidgetWifi;
	QListWidgetItem *m_lastItem;
	QString m_strLastWifiName;

	QStringList m_strListWifi; // ���wifi����
	int m_conIndex; // ���ӳɹ�wifi�������
};
