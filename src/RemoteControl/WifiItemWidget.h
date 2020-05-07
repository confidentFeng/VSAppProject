#pragma once
#include <QPainter>
#include <QColor>
#include "common.h"
#include "WifiItemWidget.h"
#include <QListWidgetItem>

class WifiItemWidget : public QWidget
{
	Q_OBJECT

public:
	WifiItemWidget(QWidget *parent = Q_NULLPTR);
	~WifiItemWidget();
	void SetWifiName(const QString& strWifiName); // ����wifi����
	void SetConStatus(const bool& bStatus); // ��������״̬
	QString GetWifiName(); // ���wifi����
	
private:
	bool eventFilter(QObject *obj, QEvent *event); // �¼�������

	QLabel *m_pLabCheck; // ѡ��Թ���ǩ
	QLabel *m_pLabName; // wifi���Ʊ�ǩ
	QLabel *m_pLabLock; // ��ͼ���ǩ
	QLabel *m_pLabWifi; // wifiͼ�갴ť
};
