#pragma once
#include <QStackedWidget>
#include "common.h"
#include "NetConfig.h"
#include "WirelessCon.h"
#include "MyPromptBox.h"
#include "BindHost.h"

class StackedWidget : public QDialog
{
	Q_OBJECT

public:
	StackedWidget(QDialog *parent = Q_NULLPTR);
	~StackedWidget();
	void SetStackCurIndex(const int& index); // 设置分页Widget的当前索引

private:
	WirelessCon *m_pWirelessCon; // 无线连接窗口
	NetConfig *m_pNetConfigWifi; // 网络配置窗口-无线连接
	//NetConfig *m_pNetConfigWired; // 网络配置窗口-有线连接
	QStackedWidget *m_pStackedWidget; // 分页Widget
};
