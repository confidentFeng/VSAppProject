#include "BatteryItem.h"

BatteryItem::BatteryItem(QWidget *parent)
	: QWidget(parent)
{
	this->setAttribute(Qt::WA_StyledBackground);
}
BatteryItem::BatteryItem(QWidget *parent, int value, int color /*= 0*/)
	: QWidget(parent)
{

}

BatteryItem::~BatteryItem()
{
}

void BatteryItem::setBatteryValue(int value)
{
	if (value < 0)
	{
		value = 0;
	}
	if (value > 100)
	{
		value = 100;
	}
	m_value = value;

	//更新界面
	update();
}

void BatteryItem::setBatteryColor(int color)
{
	if (color<0 || color>2)
	{
		color = 0;
	}

	switch (color)
	{
	case 0: // 绿色
		m_color = QColor(107, 204, 3);
		break;
	case 1:// 黄色		
		m_color = QColor(218, 165, 32);
		// m_color = QColor(255, 255, 0);
		break;
	case 2:// 红色
		m_color = QColor(255, 0, 0);
		break;
	}
	// 更新界面
	update();
}

void BatteryItem::setShowText(int flg, QString str)
{
	m_showTextFlg = flg;
	m_showText = str;
	update();
}

void BatteryItem::paintEvent(QPaintEvent *event)
{
	QSize itemSize = this->size();
	const int margin = 3; // 外框的余量
	int w = itemSize.width();
	int h = itemSize.height();

	int battery = (m_value / 100.0) * 41;
	QPainter painter(this);
	QPen pen;
	painter.setPen(m_color);
	pen = painter.pen();
	pen.setWidth(2); // 设置线框宽度
	painter.setPen(pen);
	painter.setBrush(m_color);
	painter.drawRoundedRect(12+ (41-battery), 6, 41- (41-battery), 19, 1, 1);

	switch (m_showTextFlg)
	{
	case 0: // 0:不显示文字
		   //do nothing
		break;
	case 1: // 1:显示百分比
		painter.setPen(QColor(112, 112, 112));
		painter.setFont(QFont("微软雅黑", 8, QFont::Bold));
		painter.drawText(18, 10, 31, 10,
			Qt::AlignHCenter | Qt::AlignVCenter,
			QString::asprintf("%d%%", m_value));
		break;
	case 2: // 2:显示自定义文字
		// painter.drawText(x0, y0, w0, h0,
		// Qt::AlignHCenter | Qt::AlignVCenter,
		// m_showText);
		break;
	case 3: // 显示图片
		painter.drawPixmap(25, 7, QPixmap(":/MainWindow/image/MainWindow/MainWidget_BatCharging.png"));
	}
	
	QWidget::paintEvent(event);
}