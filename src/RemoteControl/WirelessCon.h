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
	bool IsCableAccess(); // 检测网线是否接入

signals:
	void BtnNextWifi(); // 下一步进入无线网络配置界面的信号
	void BtnNextWired(); // 下一步进入有线网络配置界面的信号
	void StackedWidgetClose(); // StackedWidget界面关闭的信号

public slots:
	void clickedWifiItem(QListWidgetItem* curItem); // WifiItemWidget点击事件-响应函数

private:
	QWidget *m_pWidgetChild; // 子界面
	QLabel *m_pLabTitle; // 标题标签
	QPushButton *m_pBtnClose; // 关闭按钮
	QLabel *m_pLabInfo; // 信息标签
	QPushButton *m_pBtnWired; // 有线连接按钮

	QListWidget *pListWidgetWifi;
	QListWidgetItem *m_lastItem;
	QString m_strLastWifiName;

	QStringList m_strListWifi; // 存放wifi名称
	int m_conIndex; // 连接成功wifi项的索引
};
