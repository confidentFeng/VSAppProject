#pragma once
#include <QPainter>
#include "common.h"

class BatteryItem : public QWidget
{
	Q_OBJECT

public:
	BatteryItem(QWidget *parent = 0);
	~BatteryItem();

	/*
	[color]
	0: 绿色
	1: 黄色
	2: 红色
	[value]:电量值0-100
	*/
	BatteryItem(QWidget *parent, int value, int color = 0);

	/*
	[value]:电量值0-100
	*/
	void setBatteryValue(int value);
	/*
	[color]
	0: 绿色
	1: 黄色
	2: 红色
	*/
	void setBatteryColor(int color);

	/*
	[flg]
	0:不显示文字
	1:显示百分比
	2:显示自定义文字
	[str]
	str:自定义文字
	*/
	void setShowText(int flg = 0, QString str = "");

private:
	int m_value;
	QColor m_color = QColor(0, 255, 0);
	int m_showTextFlg = 0; // 显示文字Flg
	QString m_showText; // 显示的文本文字

protected:
	virtual void paintEvent(QPaintEvent * event) override;
};
