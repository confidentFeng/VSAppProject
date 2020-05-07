#pragma once
#include <windows.h>
#include <QPainter>
#include <QNetworkInterface>
#include <IPHlpApi.h>
#include <IPTypes.h>
#include <QRegExpValidator>
#include "common.h"
#include "MyPromptBox.h"
#include "XmlHelper.h"

#pragma comment (lib,"IPHlpApi.Lib")

class NetConfig : public QDialog
{
	Q_OBJECT

public:
	NetConfig(QDialog *parent = Q_NULLPTR, const bool& bIsWifi = true);
	~NetConfig();
	void SetBtnReturnText(const QString& strText); // ���÷��ذ�ť���ı�

signals:
	void BtnNextClicked(); // ��һ����ť�ĵ���ź�
	void BtnReturnClicked();
	void StackedWidgetClose(); // StackedWidget����رյ��ź�
	void NetConfigSuc(); // �������óɹ����ź�

private slots:
	void NextSlot(); // ��һ���ۺ���

private:
	void showEvent(QShowEvent * event); // ��ʾ�¼�
	bool isDhcpEnabled(QString mac); // ���DHCP�����Ƿ���

	QWidget *m_pWidgetChild; // �ӽ���
	QLabel *m_pLabTitle; // �����ǩ
	QPushButton *m_pBtnClose; // �رհ�ť
	QRadioButton *m_pRadioAuto; // �Զ���ȡIP��ѡ��
	QLabel *m_pLabAuto; // �Զ���ȡIP��ǩ
	QRadioButton *m_pRadioManual; // �ֶ���ȡIP��ѡ��
	QLabel *m_pLabManual; // �ֶ���ȡIP��ǩ
	QLabel *m_pLabIP; // IP��ǩ
	QLineEdit *m_pEditIP; // IP�ı���
	QLabel *m_pLabMask; // ���������ǩ
	QLineEdit *m_pEditMask; // ���������ı���
	QLabel *m_pLabGway; // Ĭ�����ر�ǩ
	QLineEdit *m_pEditGway; // Ĭ�������ı���
	QPushButton *m_pBtnReturn; // ���ذ�ť
	QPushButton *m_pBtnNext; // ��һ����ť

	QString humanReadableName; // ��������
	bool m_isManualFlag; // �Ƿ�Ϊ�ֶ���ȡ�ı�־λ
	bool m_bIsWifi; // �Ƿ�Ϊwifi�ı�־λ
};
