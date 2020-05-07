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
	0: ��ɫ
	1: ��ɫ
	2: ��ɫ
	[value]:����ֵ0-100
	*/
	BatteryItem(QWidget *parent, int value, int color = 0);

	/*
	[value]:����ֵ0-100
	*/
	void setBatteryValue(int value);
	/*
	[color]
	0: ��ɫ
	1: ��ɫ
	2: ��ɫ
	*/
	void setBatteryColor(int color);

	/*
	[flg]
	0:����ʾ����
	1:��ʾ�ٷֱ�
	2:��ʾ�Զ�������
	[str]
	str:�Զ�������
	*/
	void setShowText(int flg = 0, QString str = "");

private:
	int m_value;
	QColor m_color = QColor(0, 255, 0);
	int m_showTextFlg = 0; // ��ʾ����Flg
	QString m_showText; // ��ʾ���ı�����

protected:
	virtual void paintEvent(QPaintEvent * event) override;
};
