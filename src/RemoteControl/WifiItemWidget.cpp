#include "WifiItemWidget.h"

WifiItemWidget::WifiItemWidget(QWidget *parent)
	: QWidget(parent)
{
	/* wifi选项Frame-初始化(不要设置背景色，否则加入QListWidget异常) */
	this->setFixedSize(700, 70);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->installEventFilter(this);

	/* 窗口部件-初始化 */
	m_pLabCheck = new QLabel;
	m_pLabName = new QLabel;
	m_pLabLock = new QLabel;
	m_pLabWifi = new QLabel;
	m_pLabCheck->setObjectName("WifiOptionFrame_LabCheck");
	m_pLabName->setObjectName("WifiOptionFrame_LabName");
	m_pLabLock->setObjectName("WifiOptionFrame_LabLock");
	m_pLabWifi->setObjectName("WifiOptionFrame_LabWifi");
	m_pLabCheck->setFixedSize(30, 21);//50, 35
	m_pLabLock->setFixedSize(26, 34);
	m_pLabWifi->setFixedSize(36, 25);

	/* 主窗口-水平布局 */
	QHBoxLayout *pHLayoutMain = new QHBoxLayout(this);
	pHLayoutMain->addSpacing(12);
	pHLayoutMain->addWidget(m_pLabCheck);
	pHLayoutMain->addSpacing(12);
	pHLayoutMain->addWidget(m_pLabName);
	pHLayoutMain->addStretch(1);
	pHLayoutMain->addWidget(m_pLabLock);
	pHLayoutMain->addSpacing(20);
	pHLayoutMain->addWidget(m_pLabWifi);
	pHLayoutMain->addSpacing(100);
}

WifiItemWidget::~WifiItemWidget()
{

}

// 事件过滤器：Qt的事件过滤器默认是把父窗口下子控件的绘图事件给过滤了
bool WifiItemWidget::eventFilter(QObject *obj, QEvent *event)
{
	// 在子窗口m_pWidgetChild下绘制一条直线
	if (event->type() == QEvent::Paint)
	{
		QPainter painter(this);
		painter.setPen(QColor(0, 160, 230));
		painter.drawLine(QPoint(70, 69), QPoint(590, 69));
	}

	return QWidget::eventFilter(obj, event);
}

// 设置wifi名称
void WifiItemWidget::SetWifiName(const QString& strWifiName)
{
	m_pLabName->setText(strWifiName);
}

// 设置连接状态
void WifiItemWidget::SetConStatus(const bool& bStatus)
{
	// 默认m_pLabCheck不设置图标，选中后设置"对勾"图标，取消选中设置空白透明图标，相当于隐藏
	if (bStatus)
		m_pLabCheck->setStyleSheet("border-image: url(:/Network/image/Network/WifiOptionFrame_LabCheck.png)");
	else
		m_pLabCheck->setStyleSheet("border-image: url(no.png)");
}

// 获得wifi名称
QString WifiItemWidget::GetWifiName()
{
	return m_pLabName->text();
}
