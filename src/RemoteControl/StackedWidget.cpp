#include "StackedWidget.h"

StackedWidget::StackedWidget(QDialog *parent)
	: QDialog(parent)
{
	/* 分页窗口-初始化 */
	this->setFixedSize(700, 516);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

	/* 各界面-初始化 */
	m_pWirelessCon = new WirelessCon(this);
	m_pNetConfigWifi = new NetConfig(this, true);
	//m_pNetConfigWired = new NetConfig(this, false);

	/* 分页Widget-初始化 */
	m_pStackedWidget = new QStackedWidget;
	m_pStackedWidget->insertWidget(0, m_pWirelessCon);
	m_pStackedWidget->insertWidget(1, m_pNetConfigWifi);
	//m_pStackedWidget->insertWidget(2, m_pNetConfigWired);
	m_pStackedWidget->setContentsMargins(0, 0, 0, 0);

	/* 主界面-垂直布局 */
	QHBoxLayout *pHLayoutMain = new QHBoxLayout(this);
	pHLayoutMain->addWidget(m_pStackedWidget);
	// 各边距都设置成0，否则QStackedWidget四周会留些间隙
	pHLayoutMain->setContentsMargins(0, 0, 0, 0);

	// 下一步进入wifi配置界面的信号-接收槽函数
	QObject::connect(m_pWirelessCon, &WirelessCon::BtnNextWifi, [=]() {
		m_pStackedWidget->setCurrentIndex(1);
	});

	// 下一步进入有线网络配置界面的信号-接收槽函数
	QObject::connect(m_pWirelessCon, &WirelessCon::BtnNextWired, [=]() {
		m_pStackedWidget->setCurrentIndex(2);
	});

	// wifi网络配置界面的返回按钮信号-接收槽函数
	QObject::connect(m_pNetConfigWifi, &NetConfig::BtnReturnClicked, [=]() {
		m_pStackedWidget->setCurrentIndex(0);
	});

	//// 有线网络配置界面的返回按钮信号-接收槽函数
	//QObject::connect(m_pNetConfigWired, &NetConfig::BtnReturnClicked, [=]() {
	//	m_pStackedWidget->setCurrentIndex(0);
	//});

	// 无线连接界面关闭按钮的点击信号-接收槽函数
	QObject::connect(m_pWirelessCon, &WirelessCon::StackedWidgetClose, [=]() {
		m_pStackedWidget->close();
		delete this;
	});

	// wifi网络配置界面关闭按钮的点击信号-接收槽函数
	QObject::connect(m_pNetConfigWifi, &NetConfig::StackedWidgetClose, [=]() {
		m_pStackedWidget->close();
		delete this;
	});

	//// 有线网络配置界面关闭按钮的点击信号-接收槽函数
	//QObject::connect(m_pNetConfigWired, &NetConfig::StackedWidgetClose, [=]() {
	//	m_pStackedWidget->close();
	//	delete this;
	//});

	// wifi网络配置界面关闭按钮的点击信号-接收槽函数
	QObject::connect(m_pNetConfigWifi, &NetConfig::NetConfigSuc, [=]() {
		this->accept(); // 与delete this;冲突，故去掉delete this;
		m_pStackedWidget->close();
	});

	//// 有线网络配置界面关闭按钮的点击信号-接收槽函数
	//QObject::connect(m_pNetConfigWired, &NetConfig::NetConfigSuc, [=]() {
	//	this->accept();
	//	m_pStackedWidget->close();
	//});
}


StackedWidget::~StackedWidget()
{

}

// 设置分页Widget的当前索引
void StackedWidget::SetStackCurIndex(const int& index)
{
	m_pStackedWidget->setCurrentIndex(index);
}
