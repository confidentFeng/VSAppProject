#include "WirelessCon.h"

WirelessCon::WirelessCon(QDialog *parent)
	: QDialog(parent)
{
	/* 无线连接窗口-初始化 */
	this->setFixedSize(700, 516);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

	/* 子界面-初始化 */
	m_pWidgetChild = new QWidget(this);
	m_pWidgetChild->setGeometry(0, 0, 700, 516);
	m_pWidgetChild->setObjectName("WirelessCon_WidgetChild");

	/* 成员变量-初始化*/
	m_lastItem = new QListWidgetItem;
	m_conIndex = -1;

	/* wifi列表-初始化*/
	pListWidgetWifi = new QListWidget;
	pListWidgetWifi->setFixedSize(700, 70*6);
	pListWidgetWifi->setFrameShape(QListWidget::NoFrame);
	// 滚动平滑
	pListWidgetWifi->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	pListWidgetWifi->setVerticalScrollMode(QListWidget::ScrollPerPixel);
	pListWidgetWifi->setFocusPolicy(Qt::NoFocus); // 设置为无焦点，让currentRow开始不默认为0
	connect(pListWidgetWifi, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(clickedWifiItem(QListWidgetItem*)));
	// 滚动条美化
	//pListWidgetWifi->setStyleSheet("QScrollBar{width:40px;}");
	QFile qssFile(QApplication::applicationDirPath() + "/image/myStyleSheet.qss");
	qssFile.open(QFile::ReadOnly);
	pListWidgetWifi->setStyleSheet(qssFile.readAll());

	// 1. 查找出已连接wifi的名称
	QString strCmdCon = Common::Get()->ExecuteCmd("netsh wlan show interface");
	QStringList strListCon = strCmdCon.split("\r\n");
	QString strConWifiName = "null"; // 避免列表中有名称为""的wifi
	if (strListCon.size() > 15) // 有连接wifi的话，输出行数会有24行，否则只有14行
	{
		QStringList strListWifiName = strListCon[19].split(": ");
		strConWifiName = strListWifiName[1].remove(" ");
	}

	// 2. 提取出所有wifi的名称，并在已连接wifi一项"打勾"
	int index = 0;
	QString strCmdOut = Common::Get()->ExecuteCmd("netsh wlan show networks");
	QStringList strListOut = strCmdOut.split("\r\n");
	for (int i = 0; i < strListOut.size(); i++)
	{
		if (strListOut[i].contains("SSID"))
		{
			QStringList strListWifi = strListOut[i].split(" : ");

			// 去掉名称为""的wifi
			if (strListWifi[1] == "")
				continue;
			// 去掉名称乱码（实际是中文）的wifi
			if (strListWifi[1].contains(QRegExp("[\\x4e00-\\x9fa5]+")))
				continue;
			// 去掉长度过长的wifi
			if (strListWifi[1].length() > 24)
				continue;

			// QListWidget包含自定义列表项WifiOptionWidget
			WifiItemWidget *pWifiOptionWidget = new WifiItemWidget;
			pWifiOptionWidget->SetWifiName(strListWifi[1]);
			if (strListWifi[1] == strConWifiName)
			{
				pWifiOptionWidget->SetConStatus(true);
				// 获得已连接wifi的索引
				m_conIndex = index;
			}
			QListWidgetItem *item = new QListWidgetItem(pListWidgetWifi);
			pListWidgetWifi->setItemWidget(item, pWifiOptionWidget);
			item->setSizeHint(QSize(0, 70));
			pListWidgetWifi->addItem(item);

			// 将wifi名称添加到m_strListWifi
			m_strListWifi.append(strListWifi[1]);

			index++;
		}
	}

	/* 窗口部件-初始化 */
	m_pLabTitle = new QLabel;
	m_pBtnClose = new QPushButton;
	m_pBtnWired = new QPushButton;
	m_pLabTitle->setObjectName("WirelessCon_LabTitle");
	m_pBtnClose->setObjectName("WirelessCon_BtnClose");
	m_pBtnWired->setObjectName("WirelessCon_BtnWired");
	m_pLabTitle->setText("无线连接");
	m_pBtnWired->setText("有线连接");
	m_pBtnClose->setFixedSize(42, 42);

	/* 标题栏-水平布局 */
	QHBoxLayout *pHLayoutTitle = new QHBoxLayout;
	pHLayoutTitle->addSpacing(10);
	pHLayoutTitle->addWidget(m_pLabTitle);
	pHLayoutTitle->addStretch(1);
	pHLayoutTitle->addWidget(m_pBtnClose);
	pHLayoutTitle->addSpacing(10);

	/* 有线连接按钮-水平布局 */
	QHBoxLayout *pHLayoutWired = new QHBoxLayout;
	pHLayoutWired->addSpacing(70);
	pHLayoutWired->addWidget(m_pBtnWired);
	pHLayoutWired->addStretch(1);

	/* 主窗口-垂直布局 */
	QVBoxLayout *pVLayoutMain = new QVBoxLayout(m_pWidgetChild);
	pVLayoutMain->addSpacing(10);
	pVLayoutMain->addLayout(pHLayoutTitle);
	pVLayoutMain->addSpacing(10);
	pVLayoutMain->addWidget(pListWidgetWifi);
	pVLayoutMain->addStretch(1);
	pVLayoutMain->addLayout(pHLayoutWired);
	pVLayoutMain->addSpacing(10);
	pVLayoutMain->setContentsMargins(0, 0, 0, 0);

	// 关闭按钮-点击槽函数
	QObject::connect(m_pBtnClose, &QPushButton::clicked, [=]() {
		emit StackedWidgetClose();
	});

	// 有线连接按钮-点击槽函数
	QObject::connect(m_pBtnWired, &QPushButton::clicked, [=]() {
		// 检测网线是否接入
		if(IsCableAccess() == true)
		{
			// 关闭该界面，进入网络配置界面-有线连接
			//this->reject();
			emit BtnNextWired();
		}
	});
}

WirelessCon::~WirelessCon()
{
	
}

// 检测网线是否接入
bool WirelessCon::IsCableAccess()
{
	QString strCmdOut = Common::Get()->ExecuteCmd("netsh interface ipv4 show ipaddress interface=以太网");
	// 注意，如果str是空字符串，list1会增加一个空字符串到列表里，其size=1
	QStringList strCmdOutList = strCmdOut.split("\r\n"); 
	for (int i = 0; i<strCmdOutList.size(); i++)
	{
		if (strCmdOutList[i] == "DAD 状态           : 首选项")
			return true;
	}

	return false;
}

// WifiItemWidget点击事件-响应函数
void WirelessCon::clickedWifiItem(QListWidgetItem* curItem)
{
	// 获得当前item的索引
	int index = pListWidgetWifi->currentRow();

	// 当前项wifi还未连接
	if (index != m_conIndex)
	{
		WifiPasswdInput* pWifiPasswdInput = new WifiPasswdInput(this, m_strListWifi[index]);
		pWifiPasswdInput->setGeometry((WIN_WIDTH - 700) / 2 - 10, (WIN_HEIGHT - 516) / 2 - 40, 700, 516);
		int res = pWifiPasswdInput->exec();
		if (res == QDialog::Accepted)
		{
			// 不是第一次连接到wifi，要隐藏前一次连接wifi项的"对勾"图标
			WifiItemWidget *pWifiItemLast = new WifiItemWidget;
			pListWidgetWifi->setItemWidget(m_lastItem, pWifiItemLast);
			pWifiItemLast->SetWifiName(m_strLastWifiName);
			pWifiItemLast->SetConStatus(false);

			// 在当前index处重新设置QListWidget项，并设置选中
			WifiItemWidget *pWifiOptionWidget = new WifiItemWidget;
			pListWidgetWifi->setItemWidget(curItem, pWifiOptionWidget);
			pWifiOptionWidget->SetWifiName(m_strListWifi[index]);
			pWifiOptionWidget->SetConStatus(true);
			m_conIndex = index;

			// 获得上一次连接wifi项
			m_lastItem = curItem;
			m_strLastWifiName = m_strListWifi[index];

			// 关闭该界面，进入网络配置界面-无线
			//this->accept();
			emit BtnNextWifi();
		}
	}
	else
	{
		// 当前项wifi已经连接
		ForgetPasswd* pForgetPasswd = new ForgetPasswd(this, m_strListWifi[index]);
		pForgetPasswd->setGeometry((WIN_WIDTH - 700) / 2 - 10, (WIN_HEIGHT - 516) / 2 - 40, 700, 516);
		int res = pForgetPasswd->exec();
		if (res == QDialog::Accepted)
		{
			// 在当前index处重新设置QListWidget项，并设置不选中
			WifiItemWidget *pWifiOptionWidget = new WifiItemWidget(this);
			pListWidgetWifi->setItemWidget(curItem, pWifiOptionWidget);
			pWifiOptionWidget->SetWifiName(m_strListWifi[index]);
			pWifiOptionWidget->SetConStatus(false);

			// 设置"连接成功wifi项的索引"为-1，避免"忘记密码"后，再点击该项重复进入
			m_conIndex = -1;
		}
	}
}
