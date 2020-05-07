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
	void SetWifiName(const QString& strWifiName); // 设置wifi名称
	void SetConStatus(const bool& bStatus); // 设置连接状态
	QString GetWifiName(); // 获得wifi名称
	
private:
	bool eventFilter(QObject *obj, QEvent *event); // 事件过滤器

	QLabel *m_pLabCheck; // 选择对勾标签
	QLabel *m_pLabName; // wifi名称标签
	QLabel *m_pLabLock; // 锁图标标签
	QLabel *m_pLabWifi; // wifi图标按钮
};
