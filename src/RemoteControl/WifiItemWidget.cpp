#include "WifiItemWidget.h"

WifiItemWidget::WifiItemWidget(QWidget *parent)
	: QWidget(parent)
{
	/* wifiѡ��Frame-��ʼ��(��Ҫ���ñ���ɫ���������QListWidget�쳣) */
	this->setFixedSize(700, 70);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->installEventFilter(this);

	/* ���ڲ���-��ʼ�� */
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

	/* ������-ˮƽ���� */
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

// �¼���������Qt���¼�������Ĭ���ǰѸ��������ӿؼ��Ļ�ͼ�¼���������
bool WifiItemWidget::eventFilter(QObject *obj, QEvent *event)
{
	// ���Ӵ���m_pWidgetChild�»���һ��ֱ��
	if (event->type() == QEvent::Paint)
	{
		QPainter painter(this);
		painter.setPen(QColor(0, 160, 230));
		painter.drawLine(QPoint(70, 69), QPoint(590, 69));
	}

	return QWidget::eventFilter(obj, event);
}

// ����wifi����
void WifiItemWidget::SetWifiName(const QString& strWifiName)
{
	m_pLabName->setText(strWifiName);
}

// ��������״̬
void WifiItemWidget::SetConStatus(const bool& bStatus)
{
	// Ĭ��m_pLabCheck������ͼ�꣬ѡ�к�����"�Թ�"ͼ�꣬ȡ��ѡ�����ÿհ�͸��ͼ�꣬�൱������
	if (bStatus)
		m_pLabCheck->setStyleSheet("border-image: url(:/Network/image/Network/WifiOptionFrame_LabCheck.png)");
	else
		m_pLabCheck->setStyleSheet("border-image: url(no.png)");
}

// ���wifi����
QString WifiItemWidget::GetWifiName()
{
	return m_pLabName->text();
}
