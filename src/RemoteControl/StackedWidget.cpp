#include "StackedWidget.h"

StackedWidget::StackedWidget(QDialog *parent)
	: QDialog(parent)
{
	/* ��ҳ����-��ʼ�� */
	this->setFixedSize(700, 516);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->setAttribute(Qt::WA_DeleteOnClose);

	/* ������-��ʼ�� */
	m_pWirelessCon = new WirelessCon(this);
	m_pNetConfigWifi = new NetConfig(this, true);

	/* ��ҳWidget-��ʼ�� */
	m_pStackedWidget = new QStackedWidget;
	m_pStackedWidget->insertWidget(0, m_pWirelessCon);
	m_pStackedWidget->insertWidget(1, m_pNetConfigWifi);
	m_pStackedWidget->setContentsMargins(0, 0, 0, 0);

	/* ������-��ֱ���� */
	QHBoxLayout *pHLayoutMain = new QHBoxLayout(this);
	pHLayoutMain->addWidget(m_pStackedWidget);
	// ���߾඼���ó�0������QStackedWidget���ܻ���Щ��϶
	pHLayoutMain->setContentsMargins(0, 0, 0, 0);

	// ��һ������wifi���ý�����ź�-���ղۺ���
	QObject::connect(m_pWirelessCon, &WirelessCon::BtnNextWifi, [=]() {
		m_pStackedWidget->setCurrentIndex(1);
	});

	// ��һ�����������������ý�����ź�-���ղۺ���
	QObject::connect(m_pWirelessCon, &WirelessCon::BtnNextWired, [=]() {
		m_pStackedWidget->setCurrentIndex(2);
	});

	// wifi�������ý���ķ��ذ�ť�ź�-���ղۺ���
	QObject::connect(m_pNetConfigWifi, &NetConfig::BtnReturnClicked, [=]() {
		m_pStackedWidget->setCurrentIndex(0);
	});

	// �������ӽ���رհ�ť�ĵ���ź�-���ղۺ���
	QObject::connect(m_pWirelessCon, &WirelessCon::StackedWidgetClose, [=]() {
		m_pStackedWidget->close();
		delete this;
	});

	// wifi�������ý���رհ�ť�ĵ���ź�-���ղۺ���
	QObject::connect(m_pNetConfigWifi, &NetConfig::StackedWidgetClose, [=]() {
		m_pStackedWidget->close();
		delete this;
	});

	// wifi�������ý���رհ�ť�ĵ���ź�-���ղۺ���
	QObject::connect(m_pNetConfigWifi, &NetConfig::NetConfigSuc, [=]() {
		this->accept(); // ��delete this;��ͻ����ȥ��delete this;
		m_pStackedWidget->close();
	});
}


StackedWidget::~StackedWidget()
{

}

// ���÷�ҳWidget�ĵ�ǰ����
void StackedWidget::SetStackCurIndex(const int& index)
{
	m_pStackedWidget->setCurrentIndex(index);
}
