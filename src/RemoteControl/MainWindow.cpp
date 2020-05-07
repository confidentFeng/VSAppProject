#include "MainWindow.h"

MainWindow::MainWindow(QDialog *parent)
	: QDialog(parent)
{
	/* 主界面-初始化 */
	this->setFixedSize(WIN_WIDTH, WIN_HEIGHT);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->setAttribute(Qt::WA_DeleteOnClose);
	//this->resize(deskWidth, deskHeight);

	/* 顶栏、底栏子界面-初始化 */
	m_pWidgetTop = new QWidget;
	m_pWidgetBottom = new QWidget;
	m_pWidgetTop->setObjectName("MainWindow_WidgetTop");
	m_pWidgetBottom->setObjectName("MainWindow_WidgetBottom");
	m_pWidgetTop->setFixedSize(1920, 70);
	m_pWidgetBottom->setFixedSize(1920, 130);

	/* 顶栏-初始化 */
	m_pLabTime = new QLabel;
	m_pLabIPText = new QLabel;
	m_pLabIP = new QLabel;
	m_pLabHardDiskText = new QLabel;
	m_pLabHardDisk = new QLabel;
	m_pBatteryItem = new BatteryItem;
	m_pBtnNetwork = new QPushButton;
	m_pBtnSysSet = new QPushButton;
	m_pBtnShutdown = new QPushButton;
	m_pLabTime->setObjectName("MainWindow_LabTime");
	m_pLabIPText->setObjectName("MainWindow_LabIPText");
	m_pLabIP->setObjectName("MainWindow_LabIP");
	m_pLabHardDiskText->setObjectName("MainWindow_LabHardDiskText");
	m_pLabHardDisk->setObjectName("MainWindow_LabHardDisk");
	m_pBatteryItem->setObjectName("MainWindow_BatteryItem");
	m_pBtnNetwork->setObjectName("MainWindow_BtnNetwork");
	m_pBtnSysSet->setObjectName("MainWindow_BtnSysSet");
	m_pBtnShutdown->setObjectName("MainWindow_BtnShutdown");
	m_pLabIPText->setText("IP地址：");
	m_pLabHardDiskText->setText("硬盘容量：");
	m_pLabHardDisk->setText("000GB/000GB");
	m_pBatteryItem->setFixedSize(60, 31);
	m_pBtnNetwork->setFixedSize(50, 36);
	m_pBtnSysSet->setFixedSize(38, 38);
	m_pBtnShutdown->setFixedSize(38, 38);
	m_pBatteryItem->setBatteryValue(30);
	m_pBatteryItem->setShowText(1);
	m_pBatteryItem->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BatteryItem.png)");

	/* 侧边栏-初始化 */
	m_pBtnReview = new QPushButton;
	m_pBtnSplitSet = new QPushButton;
	m_pBtnOSD = new QPushButton;
	m_pBtnReview->setObjectName("MainWindow_BtnReview");
	m_pBtnSplitSet->setObjectName("MainWindow_BtnSplitSet");
	m_pBtnOSD->setObjectName("MainWindow_BtnOSD");
	m_pBtnReview->setFixedSize(90, 100);
	m_pBtnSplitSet->setFixedSize(90, 100);
	m_pBtnOSD->setFixedSize(90, 100);
	m_pBtnReview->setCheckable(true);
	m_pBtnSplitSet->setCheckable(true);
	m_pBtnOSD->setCheckable(true);

	/* 视频播放Frame窗口-初始化*/
	m_pVedioFrame = new QFrame;
	m_pVideoWidget = new QWidget(m_pVedioFrame);
	m_pVideoWidget->setFixedSize(1920, 1080); // 1080P：1.777的横竖比  1720 934 1660 934
	m_pVideoWidget->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
		"background-color: rgb(0, 0, 0);\n"
		"border:none;"));
	// 初始化mpvPlayer
	mpvPlayer = new MpvPlayer(m_pVideoWidget);

	/* 底栏 */
	m_pBtnRecord = new QPushButton;
	m_pLabRecord = new QLabel;
	m_pBtnPause = new QPushButton;
	m_pBtnLockVGA = new QPushButton;
	m_pBtnLive = new QPushButton;
	m_pBtnSwitch = new QPushButton;
	m_pBtnTrack = new QPushButton;
	m_pBtnLockScr = new QPushButton;
	m_pBtnRecord->setObjectName("MainWindow_BtnRecord");
	m_pLabRecord->setObjectName("MainWindow_LabRecord");
	m_pBtnPause->setObjectName("MainWindow_BtnPause");
	m_pBtnLockVGA->setObjectName("MainWindow_BtnLockVGA");
	m_pBtnLive->setObjectName("MainWindow_BtnLive");
	m_pBtnSwitch->setObjectName("MainWindow_BtnSwitch");
	m_pBtnTrack->setObjectName("MainWindow_BtnTrack");
	m_pBtnLockScr->setObjectName("MainWindow_BtnLockScr");
	m_pLabRecord->setText("   录制   ");
	m_pBtnRecord->setFixedSize(62, 56);
	m_pLabRecord->setFixedSize(24 * 8, 24);
	m_pBtnPause->setFixedSize(60, 98);
	m_pBtnLockVGA->setFixedSize(98, 98);
	m_pBtnLive->setFixedSize(58, 98);
	m_pBtnSwitch->setFixedSize(98, 98);
	m_pBtnTrack->setFixedSize(98, 98);
	m_pBtnLockScr->setFixedSize(50, 98);
	m_pBtnRecord->setCheckable(true);
	m_pBtnPause->setCheckable(true);
	m_pBtnLockVGA->setCheckable(true);
	m_pBtnLive->setCheckable(true);
	m_pBtnSwitch->setCheckable(true);
	m_pBtnTrack->setCheckable(true);
	m_pBtnLockScr->setCheckable(true);

	/* 顶栏-水平布局 */
	QHBoxLayout *pHLayoutTop = new QHBoxLayout(m_pWidgetTop);
	pHLayoutTop->addSpacing(300);
	pHLayoutTop->addWidget(m_pLabTime);
	pHLayoutTop->addStretch(1);	
	pHLayoutTop->addWidget(m_pLabIPText);
	pHLayoutTop->addWidget(m_pLabIP);
	pHLayoutTop->addStretch(1);
	pHLayoutTop->addWidget(m_pLabHardDiskText);
	pHLayoutTop->addWidget(m_pLabHardDisk);
	pHLayoutTop->addStretch(1);
	pHLayoutTop->addWidget(m_pBatteryItem);
	pHLayoutTop->addSpacing(72);
	pHLayoutTop->addWidget(m_pBtnNetwork);
	pHLayoutTop->addSpacing(36);
	pHLayoutTop->addWidget(m_pBtnSysSet);
	pHLayoutTop->addSpacing(36);
	pHLayoutTop->addWidget(m_pBtnShutdown);
	pHLayoutTop->addSpacing(24);

	/* 侧边栏-垂直布局 */
	QVBoxLayout *pVLayoutSide = new QVBoxLayout;
	pVLayoutSide->addWidget(m_pBtnReview);
	pVLayoutSide->addWidget(m_pBtnSplitSet);
	pVLayoutSide->addWidget(m_pBtnOSD);

	/* 录制-垂直布局 */
	m_pWidgetRecord = new QWidget;
	m_pWidgetRecord->setFixedSize(120, 112);
	QVBoxLayout *pVLayoutRecord = new QVBoxLayout(m_pWidgetRecord);
	pVLayoutRecord->addWidget(m_pBtnRecord, 0, Qt::AlignCenter);
	pVLayoutRecord->addWidget(m_pLabRecord);

	/* 底栏-水平布局 */
	QHBoxLayout *pHLayoutBottom = new QHBoxLayout(m_pWidgetBottom);
	pHLayoutBottom->addSpacing(328);
	pHLayoutBottom->addWidget(m_pWidgetRecord);
	pHLayoutBottom->addSpacing(100);
	pHLayoutBottom->addWidget(m_pBtnPause);
	pHLayoutBottom->addSpacing(110);
	pHLayoutBottom->addWidget(m_pBtnLockVGA);
	pHLayoutBottom->addSpacing(100);
	pHLayoutBottom->addWidget(m_pBtnLive);
	pHLayoutBottom->addSpacing(90);
	pHLayoutBottom->addWidget(m_pBtnSwitch);
	pHLayoutBottom->addSpacing(110);
	pHLayoutBottom->addWidget(m_pBtnTrack);
	pHLayoutBottom->addSpacing(110);
	pHLayoutBottom->addWidget(m_pBtnLockScr);
	pHLayoutBottom->addSpacing(154);

	/* 主布局 */
#if IS_DEBUG
	QVBoxLayout *pVLayoutMain = new QVBoxLayout(this);
	pVLayoutMain->addWidget(m_pWidgetTop);
	pVLayoutMain->addWidget(m_pVideoWidget);
	pVLayoutMain->addWidget(m_pWidgetBottom);
	pVLayoutMain->setSpacing(0);
	pVLayoutMain->setContentsMargins(0, 0, 0, 0);
#else
	QVBoxLayout *pVLayoutMain = new QVBoxLayout(this);
	pVLayoutMain->addWidget(m_pWidgetTop);
	pVLayoutMain->addWidget(m_pVideoWidget);
	pVLayoutMain->addWidget(m_pWidgetBottom);
	pVLayoutMain->setSpacing(0);
	pVLayoutMain->setContentsMargins(0, 0, 0, 0);
#endif

	/* 标志位-初始化 */
	m_isLive = false;
	m_isRecord = false;
	m_isPause = false;
	m_isLockVGA = false;
	m_isSwitch = false;
	m_isTrack = false;

	/* 直播\录制定时器-初始化 */
	m_pTimeRecord;
	m_pTimerRecord = new QTimer(this);
	connect(m_pTimerRecord, SIGNAL(timeout()), this, SLOT(RecordTimeOutSlot()));
	connect(this, &MainWindow::PauseSignal, this, &MainWindow::PauseSlot);

	/* 顶栏-连接槽函数 */
	connect(m_pBtnNetwork, SIGNAL(clicked()), this, SLOT(NetSetSlot()));
	connect(m_pBtnSysSet, SIGNAL(clicked()), this, SLOT(SysSetSlot()));
	connect(m_pBtnShutdown, SIGNAL(clicked()), this, SLOT(ShutdownSlot()));

	/* 底栏-连接槽函数 */
	connect(m_pBtnRecord, SIGNAL(clicked()), this, SLOT(RecordSlot()));
	connect(m_pBtnPause, SIGNAL(clicked()), this, SLOT(PauseSlot()));
	connect(m_pBtnLockVGA, SIGNAL(clicked()), this, SLOT(LockVGASlot()));
	connect(m_pBtnLive, SIGNAL(clicked()), this, SLOT(LiveSlot()));
	connect(m_pBtnSwitch, SIGNAL(clicked()), this, SLOT(SwitchSlot()));
	connect(m_pBtnTrack, SIGNAL(clicked()), this, SLOT(TrackSlot()));
	connect(m_pBtnLockScr, SIGNAL(clicked()), this, SLOT(LockScrSlot()));

	/* 开机设置系统时间 */
	QDateTime *datatime = new QDateTime(QDateTime::currentDateTime());
	QString str = datatime->toString("yyyy-MM-dd hh:mm:ss");
	m_pLabTime->setText(str);
	// 初始化系统时间定时器
	m_pSysTimer = new QTimer;
	m_pSysTimer->setInterval(1000);
	m_pSysTimer->start();
	connect(m_pSysTimer, SIGNAL(timeout()), this, SLOT(timeoutSlot()));

	// 初始化电量控件
	InitPowerMonitoring();

	// 创建UDP套接字对象
	m_UdpSocket = new QUdpSocket();
	// 连接服务器(第二个参数表示允许其它地址链接该广播)
	if (m_UdpSocket->bind(6601, QUdpSocket::ShareAddress))
		connect(m_UdpSocket, SIGNAL(readyRead()), this, SLOT(RecvUdpData()));
	else
		qDebug() << "UDP绑定失败！";
	// 开机发送UDP连接信号
	UdpClient::Get()->SendData(1, 1, 0);

	// 初始化网络相关
	InitNetwork();

	// 开始一个定时器检查网络
	timeIDNetCheck = this->startTimer(1000 * 3);

	// 开始一个定时器检查录制状态
	timeIDRecord = this->startTimer(1000 * 5);
}

MainWindow::~MainWindow()
{

}

// 初始化网络相关
void MainWindow::InitNetwork()
{
	// 1. 开机默认先选择启用有线网卡和无线网卡
	CmdThread *cmdCmdThread1 = new CmdThread("netsh interface set interface name=\"以太网\" admin=ENABLED");
	cmdCmdThread1->start();
	CmdThread *cmdCmdThread2 = new CmdThread("netsh interface set interface name=\"WLAN 2\" admin=ENABLED");
	cmdCmdThread2->start();

	// 2. 开机检测以太网已设置网络按钮的图标
	bool bHaveWired = false;
	bool bHaveWifi = false;
	QString strCmdOut = Common::Get()->ExecuteCmd2("netsh interface ipv4 show ipaddress interface=以太网");
	QStringList strCmdOutList = strCmdOut.split("\r\n");
	for (int i = 0; i<strCmdOutList.size(); i++)
	{
		if (strCmdOutList[i].contains("首选项")) // 开机就有网线插入，或者中途插入网线
		{
			bHaveWired = true;
			break;
		}
	}

	// 3. 开机检测wifi已设置网络按钮的图标
	QString strCmdOutWifi = Common::Get()->ExecuteCmd2("netsh interface ipv4 show ipaddress interface=\"WLAN 2\"");
	QStringList strCmdOutListWifi = strCmdOutWifi.split("\r\n");
	for (int i = 0; i<strCmdOutListWifi.size(); i++)
	{
		if (strCmdOutListWifi[i].contains("首选项")) // 有wifi
		{
			bHaveWifi = true;
			break;
		}
	}

	// 4. 设置网络图标
	if (bHaveWired == true)
		m_pBtnNetwork->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWindow_BtnNetwork_1.png)");
	else if (bHaveWired == false && bHaveWifi == false)
		m_pBtnNetwork->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWindow_BtnNetwork_2.png)");
	else
		m_pBtnNetwork->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWindow_BtnNetwork_0.png)");
}

// 初始化电量控件
void MainWindow::InitPowerMonitoring()
{
	// 首次获取系统电量
	SYSTEM_POWER_STATUS PowerSatus;
	if (GetSystemPowerStatus(&PowerSatus))
	{
		if (m_pBatteryItem)
		{
			if ((int)PowerSatus.ACLineStatus)
				// 充电
				m_pBatteryItem->setShowText(3);
			else
				m_pBatteryItem->setShowText(1);

			int npower = (int)PowerSatus.BatteryLifePercent;
			m_pBatteryItem->setBatteryValue(npower);
			if (npower <= 20)
				m_pBatteryItem->setBatteryColor(2);// 红色

			if (npower > 20)
				m_pBatteryItem->setBatteryColor(0);//绿色
		}
	}

	// 开始一个定时器检查电量
	timeIDPower = this->startTimer(1000 * 3);
}

// 更新窗口
void MainWindow::updataWin()
{
	// 更新窗口时，再次发送UDP连接信号
	UdpClient::Get()->SendData(1, 1, 0);

	/* 主界面显示时，才读取配置文件中的信息(下面也一样) */
	QString iniFilePath = QApplication::applicationDirPath() + "/config.ini";
	QSettings *iniRead = new QSettings(iniFilePath, QSettings::IniFormat);
	m_hostIP = iniRead->value("hostIP").toString();
	qDebug() << "updataWin_hostIP: " << m_hostIP;
	delete iniRead;

	// RTMP拉流
	mpvPlayer->play(QString("rtmp://%1/live/main").arg(m_hostIP));

	/* 开机设置IP和硬盘容量 */
	m_pLabIP->setText(m_hostIP);

	// http发送“获取硬盘存储信息”
	HttpClient(QString("http://%1/ROCPOW.cgi?type=77").arg(m_hostIP)).success([&](const QString &response) {
		m_strFreeCap = QString(response).section(QRegExp("[,]"), 0, 0).section(QRegExp("[:]"), 2, 2);
		m_strTotalCap = QString(response).section(QRegExp("[}]"), 0, 0).section(QRegExp("[:]"), 3, 3);
	}).fail([](const QString &error, int errorCode) {
		qDebug().noquote() << "error: " << error << errorCode << endl;
	}).get();
}

// 检查以太网和wifi，已确定网络图标
void MainWindow::CheckNet()
{
	CmdThread *cmdCmdThread1 = new CmdThread("netsh interface ipv4 show ipaddress interface=以太网");
	cmdCmdThread1->start();
	connect(cmdCmdThread1, SIGNAL(resultReady(QString)), this, SLOT(WiredNetSlot(QString)));

	CmdThread *cmdCmdThread2 = new CmdThread("netsh interface ipv4 show ipaddress interface=\"WLAN 2\"");
	cmdCmdThread2->start();
	connect(cmdCmdThread2, SIGNAL(resultReady(QString)), this, SLOT(WifiNetSlot(QString)));
}

// 以太网检测槽函数
void MainWindow::WiredNetSlot(const QString &strCmdOut)
{
	// 检测以太网已设置网络按钮的图标
	static bool bAllowFlag = true;
	QStringList strCmdOutList = strCmdOut.split("\r\n");
	if (strCmdOutList[7].contains("首选项")) // 中途插入网线
	{
		bHaveWired = true;

		// 当不是有线连接图标时，检测到中途插入网线，则弹出IP配置窗口，避免重复弹出
		if (bAllowFlag && m_pBtnNetwork->styleSheet() != "border-image: url(:/MainWindow/image/MainWindow/MainWindow_BtnNetwork_1.png)")
		{
			bAllowFlag = false;

			if (m_bHaveWifi)
			{
				MyMessageBox *pMyMessageBox = new MyMessageBox(this);
				pMyMessageBox->ShowControl(false, true, "有线连接");
				pMyMessageBox->SetInfoText("系统检测到您已插入网线，是否修改网络设置");
				int res = pMyMessageBox->exec();
				if (res == QDialog::Rejected)
					return;
			}

			NetConfig *m_pNetConfigWired = new NetConfig(this, false);
			m_pNetConfigWired->SetBtnReturnText("取消");
			int res = m_pNetConfigWired->exec();
			if (res == QDialog::Accepted)
			{
				// 按下确定按钮后，才切换为有线连接图标
				m_pBtnNetwork->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWindow_BtnNetwork_1.png)");

				// 有两种情况：一是断网状态，不处理；而是wifi状态，需要查找已连接wifi并断开
				// 1. 查找出已连接wifi的名称
				QString strCmdCon = Common::Get()->ExecuteCmd2("netsh wlan show interface");
				QStringList strListCon = strCmdCon.split("\r\n");
				QString strConWifiName = "null"; // 避免列表中有名称为""的wifi
				if (strListCon.size() > 15) // 有连接wifi的话，输出行数会有24行，否则只有14行
				{
					QStringList strListWifiName = strListCon[19].split(": ");
					strConWifiName = strListWifiName[1].remove(" ");

					// 2. 将已连接wifi断开
					Common::Get()->ExecuteCmd2(QString("netsh wlan delete profile name=%1").arg(strConWifiName));
				}

				// 非阻塞延时一段时间，等待修改IP后网络切换成功
				QEventLoop eventloop;
				QTimer::singleShot(2500, &eventloop, SLOT(quit()));
				eventloop.exec();

				// 更新窗口
				updataWin();
			}
		}
	}
	else if(strCmdOutList[7].contains("反对")) // 中途拔出网线
	{
		bAllowFlag = true;
		bHaveWired = false;

		if(!m_bHaveWifi)
			m_pBtnNetwork->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWindow_BtnNetwork_2.png)");
	}
}

// wifi检测槽函数
void MainWindow::WifiNetSlot(const QString &strCmdOut)
{
	static bool bAllowWifiFlag = true;
	m_bHaveWifi = false;

	// 检测wifi已设置网络按钮的图标
	QStringList strCmdOutListWifi = strCmdOut.split("\r\n");
	if (strCmdOutListWifi[7].contains("首选项")) // 中途连接wifi
	{
		m_bHaveWifi = true;
		if (bAllowWifiFlag && !bHaveWired)
		{
			bAllowWifiFlag = false;
			m_pBtnNetwork->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWindow_BtnNetwork_0.png)");

			// 更新窗口
			updataWin();
		}
	}
	else if (strCmdOutListWifi[7].contains("反对")) // 无连接wifi
		bAllowWifiFlag = true;
}

// 显示事件：解决设置了Qt::FramelessWindowHint，界面不能自主刷新的问题
void MainWindow::showEvent(QShowEvent *event)
{
	updataWin(); // 开机更新窗口

	this->setAttribute(Qt::WA_Mapped);
	QWidget::showEvent(event);
}

// 键盘按下事件:用于按Alt+M键关闭程序
void MainWindow::keyPressEvent(QKeyEvent * event)
{
	// 先检测Alt键是否按下
	if (event->modifiers() == Qt::AltModifier)
	{
		// 如果是，那么再检测M键是否按下
		if (event->key() == Qt::Key_M)
		{
			this->close();
		}
	}
}

// 定时器事件
void MainWindow::timerEvent(QTimerEvent* event)
{
	if (event->timerId() == timeIDPower)
	{
		// 获取系统电量
		SYSTEM_POWER_STATUS PowerSatus;
		if (GetSystemPowerStatus(&PowerSatus))
		{
			if ((int)PowerSatus.ACLineStatus)
				// 充电
				m_pBatteryItem->setShowText(3);
			else
				m_pBatteryItem->setShowText(1);

			int npower = (int)PowerSatus.BatteryLifePercent;
			m_pBatteryItem->setBatteryValue(npower);
			if (npower <= 20)
				m_pBatteryItem->setBatteryColor(2);// 红色

			if (npower > 20)
				m_pBatteryItem->setBatteryColor(0);// 绿色
		}
	}

	// 监测网络
	if (event->timerId() == timeIDNetCheck)
	{
		// 检查以太网和wifi，已确定网络图标
		CheckNet();
	}

	// 监测录制状态
	if (event->timerId() == timeIDRecord)
	{
		//// http发送“获取录制信息”
		//HttpClient(QString("http://%1/ROCPOW.cgi?type=16").arg(m_hostIP)).success([&](const QString &response) {
		//	//m_strFreeCap = QString(response).section(QRegExp("[,]"), 0, 0).section(QRegExp("[:]"), 2, 2);
		//	//m_strTotalCap = QString(response).section(QRegExp("[}]"), 0, 0).section(QRegExp("[:]"), 3, 3);
		//}).fail([](const QString &error, int errorCode) {
		//	qDebug().noquote() << "error: " << error << errorCode << endl;
		//}).get();
	}
}

// 网络设置的槽函数
void MainWindow::NetSetSlot()
{
	// 如果是有线连接状态，则无法修改为wifi连接，点击按钮无效
	if (m_pBtnNetwork->styleSheet() == "border-image: url(:/MainWindow/image/MainWindow/MainWindow_BtnNetwork_1.png)")
		return;

	// 使用QStackedWidget切换界面显示
	StackedWidget *pMainWidget = new StackedWidget(this);
	pMainWidget->SetStackCurIndex(0);
	int res = pMainWidget->exec();

	if (res == QDialog::Accepted)
	{
		m_pBtnNetwork->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWindow_BtnNetwork_0.png)");

		// 非阻塞延时一段时间，等待修改IP后网络切换成功(每次打开无线连接界面都执行下面程序，不会黑屏)
		QEventLoop eventloop;
		QTimer::singleShot(3000, &eventloop, SLOT(quit())); // 2500
		eventloop.exec();

		updataWin(); // 更新窗口
	}
}

// 系统设置的槽函数
void MainWindow::SysSetSlot()
{
	/* 读配置文件，用于初始化BindHost界面 */
	QString iniFilePath = QApplication::applicationDirPath() + "/config.ini";
	QSettings *iniRead = new QSettings(iniFilePath, QSettings::IniFormat);
	QString hostIP = iniRead->value("hostIP").toString();
	int hostPort = iniRead->value("hostPort").toInt();
	QString hostAccount = iniRead->value("hostAccount").toString();
	QString hostPasswd = iniRead->value("hostPasswd").toString();
	delete iniRead;

	// 模态显示配置界面
	BindHost *bindHost = new BindHost(this);
	bindHost->IsFirstOpen(false);
	bindHost->SetHostIP(hostIP);
	bindHost->SetHostPort(hostPort);
	bindHost->SetHostAccount(hostAccount);
	bindHost->SetHostPasswd(hostPasswd);
	int res = bindHost->exec();
	if (res == QDialog::Accepted)
	{
		updataWin(); // 更新窗口
	}
}

// 关机的槽函数
void MainWindow::ShutdownSlot()
{
	// 模态显示消息框界面
	MyMessageBox *pMyMessageBox = new MyMessageBox(this);
	if (m_isLive == true || m_isRecord == true)
		pMyMessageBox->SetInfoText("当前正在直播或录制，是否停止并关闭本机？\n（此操作仅关闭本机，不会导致录播主机关机）");
	else
		pMyMessageBox->SetInfoText("此操作仅关闭本机，不会导致录播主机关机！");
	int res = pMyMessageBox->exec();
	// 检测是否点击了确认按钮
	if (res == QDialog::Accepted)
	{
		system("shutdown -s -t 00");
	}
}

// 录制视频
void MainWindow::RecordSlot()
{
	if (!m_isRecord)
	{
		// 模态显示输入录制信息界面
		InputRecInfo *pInputRecInfo = new InputRecInfo(this);
		int res = pInputRecInfo->exec();

		// 检测"输入录制信息界面"是否点击保存按钮后关闭了
		if (res == QDialog::Accepted)
		{
			m_isRecord = true;

			m_recordTime = 0;
			// 切换录制按钮的样式和文本
			m_pBtnRecord->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnRecord_1.png)");
			m_pLabRecord->setText("00:00:00");
			// 1.点击开始后获取到当前的时间并且赋值给m_pTimeRecord				
			m_pTimeRecord = m_pTimeRecord.currentTime();
			// 2.启动定时器m_pTimerRecord, 间隔1s
			m_pTimerRecord->start(1);

			#if HTTP_TEST
			// http发送“开始录制”
			HttpClient(QString("http://%1/ROCPOW.cgi?type=15&state=1").arg(m_hostIP)).success([](const QString &response) {
				qDebug().noquote() << "开始录制: " << response << endl;
			}).fail([](const QString &error, int errorCode) {
				qDebug().noquote() << "error: " << error << errorCode << endl;
			}).get();
			#endif
		}
	}
	else
	{	
		// 模态显示消息框界面
		MyMessageBox *pMyMessageBox = new MyMessageBox(this);
		pMyMessageBox->SetInfoText("是否停止录制？");
		int res = pMyMessageBox->exec();

		// 检测"输入消息框界面"是否点击保存按钮后关闭了
		if (res == QDialog::Accepted)
		{
			m_isRecord = false;

			// 恢复录制按钮的样式和文本
			m_pBtnRecord->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnRecord_0.png)");
			m_pLabRecord->setText("   录制   ");
			// 停止录制计时
			m_pTimerRecord->stop();

			// 停止录制后,如果还在暂停，则发送"暂停录制信号"，暂停录制
			if (m_isPause)
				emit PauseSignal();

			#if HTTP_TEST
			// http发送“停止录制”
			HttpClient(QString("http://%1/ROCPOW.cgi?type=15&state=0").arg(m_hostIP)).success([](const QString &response) {
				qDebug().noquote() << "开始录制: " << response << endl;
			}).fail([](const QString &error, int errorCode) {
				qDebug().noquote() << "error: " << error << errorCode << endl;
			}).get();
			#endif
		}
	}
}

// 暂停/恢复录制
void MainWindow::PauseSlot()
{
	// 有流在录制才可以暂停
	static QTime pauseTime;
	if (!m_isPause && m_isRecord==true)
	{
		m_isPause = true;

		// 切换暂停按钮的样式
		m_pBtnPause->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnPause_1.png)");
		
		// 获得暂停时的时间，用于录制计时
		pauseTime = QTime::currentTime();
		// 暂时关闭录制计时器
		m_pTimerRecord->stop();

		#if HTTP_TEST
		// http发送“暂停录制”
		HttpClient(QString("http://%1/ROCPOW.cgi?type=15&state=2").arg(m_hostIP)).success([](const QString &response) {
			qDebug().noquote() << "暂停录制: " << response << endl;
		}).fail([](const QString &error, int errorCode) {
			qDebug().noquote() << "error: " << error << errorCode << endl;
		}).get();
		#endif
	}
	else
	{
		m_isPause = false;

		// 恢复暂停按钮的样式
		m_pBtnPause->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnPause_0.png)");

		// 进行差值计算并恢复打开录制计时器
		QTime cut = QTime::currentTime();
		int t = pauseTime.msecsTo(cut);
		m_pTimeRecord = m_pTimeRecord.addMSecs(t);
		// 在录制进行的情况下，才打开录制计时器
		if(m_isRecord)
			m_pTimerRecord->start();

		#if HTTP_TEST
		// http发送“开始录制”(恢复录制)
		HttpClient(QString("http://%1/ROCPOW.cgi?type=15&state=1").arg(m_hostIP)).success([](const QString &response) {
			qDebug().noquote() << "恢复录制: " << response << endl;
		}).fail([](const QString &error, int errorCode) {
			qDebug().noquote() << "error: " << error << errorCode << endl;
		}).get();
		#endif
	}
}

// 录制定时器超时函数
void MainWindow::RecordTimeOutSlot()
{
	/*
	* 1.点击开始后获取到当前的时间并且赋值给m_pTimeRecord
	* 2.启动定时器m_pTimerRecord,间隔1s
	* 3.超时槽函数中再次获取当前的时间currTime
	* 4.计算两个时间的差值t,即录制时间
	*/
	QTime currTime = QTime::currentTime();
	int t = m_pTimeRecord.msecsTo(currTime);

	//recordTime++;
	m_recordTime = t / 1000;
	char buf[1024] = { 0 };
	sprintf(buf, "%02d:%02d:%02d", m_recordTime / 3600, m_recordTime / 60, m_recordTime % 60);
	m_pLabRecord->setText(buf);
}

// 锁定VGA的槽函数
void MainWindow::LockVGASlot()
{
	if (!m_isLockVGA)
	{
		m_isLockVGA = true;
		m_pBtnLockVGA->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnLockVGA_1.png)");

		// UDP发送"启用VGA锁定"命令
		UdpClient::Get()->SendData(15, 1, 0);

		#if HTTP_TEST
		// http发送“导播切换直播画面”(view：镜头画面下标，从1开始计算)
		HttpClient(QString("http://%1/ROCPOW.cgi?type=90&view=8").arg(m_hostIP)).success([](const QString &response) {
			qDebug().noquote() << "导播切换直播画面: " << response << endl;
		}).fail([](const QString &error, int errorCode) {
			qDebug().noquote() << "error: " << error << errorCode << endl;
		}).get();
		#endif
	}
	else
	{
		m_isLockVGA = false;
		m_pBtnLockVGA->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnLockVGA_0.png)");

		// UDP发送"取消VGA锁定"命令
		UdpClient::Get()->SendData(15, 0, 0);
	}
}

// 直播开启/关闭的槽函数
void MainWindow::LiveSlot()
{
	if (!m_isLive)
	{
		m_isLive = true;
		m_pBtnLive->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnLive_1.png)");

		// UDP发送"开启直播"命令
		UdpClient::Get()->SendData(51, 1, 0);

#if 1
		// http发送“启用第三方直播推流”命令
		HttpClient(QString("http://%1/ROCPOW.cgi?type=50&token=xx&pushstat=1").arg(m_hostIP)).success([](const QString &response) {
			qDebug().noquote() << "启用第三方直播推流: " << response << endl;
		}).fail([](const QString &error, int errorCode) {
			qDebug().noquote() << "error: " << error << errorCode << endl;
		}).get();
#endif
	}
	else
	{
		m_isLive = false;
		m_pBtnLive->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnLive_0.png)");

		// UDP发送"关闭直播"命令
		UdpClient::Get()->SendData(51, 0, 0);

		#if 1
		// UDP发送"关闭第三方直播推流"命令
		HttpClient(QString("http://%1/ROCPOW.cgi?type=50&token=xx&pushstat=0").arg(m_hostIP)).success([](const QString &response) {
			qDebug().noquote() << "关闭第三方直播推流: " << response << endl;
		}).fail([](const QString &error, int errorCode) {
			qDebug().noquote() << "error: " << error << errorCode << endl;
		}).get();
		#endif
	}
}

// 自动切换开启/关闭的槽函数
void MainWindow::SwitchSlot()
{
	if (!m_isSwitch)
	{
		m_isSwitch = true;
		m_pBtnSwitch->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnSwitch_1.png)");

		// UDP发送"启用自动切换"命令
		UdpClient::Get()->SendData(3, m_isTrack, 1);
	}
	else
	{
		m_isSwitch = false;
		m_pBtnSwitch->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnSwitch_0.png)");

		// UDP发送"关闭自动切换"命令
		UdpClient::Get()->SendData(3, m_isTrack, 0);
	}
}

// 自动跟踪开启/关闭的槽函数
void MainWindow::TrackSlot()
{
	if (!m_isTrack)
	{
		m_isTrack = true;
		m_pBtnTrack->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnTrack_1.png)");

		// UDP发送"启用自动跟踪"命令
		UdpClient::Get()->SendData(3, 1, m_isSwitch);
	}
	else
	{
		m_isTrack = false;
		m_pBtnTrack->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnTrack_0.png)");

		// UDP发送"关闭自动跟踪"命令
		UdpClient::Get()->SendData(3, 0, m_isSwitch);
	}
}

// 锁屏的槽函数
void MainWindow::LockScrSlot()
{
	// 显示锁屏界面
	LockScreen *pLockScreen = new LockScreen(this);
	pLockScreen->show();
}

// 定时器超时槽函数：用于实时获取时间和硬盘容量
void MainWindow::timeoutSlot()
{
	QDateTime *datatime = new QDateTime(QDateTime::currentDateTime());
	QString str = datatime->toString("yyyy-MM-dd hh:mm:ss");
	m_pLabTime->setText(str);
	
	// 分别显示硬盘占用和总容量，超过阈值(70%)显示红色
	QString occupyCap = QString::number(m_strTotalCap.toInt() - m_strFreeCap.toInt());
	m_pLabHardDisk->setText(QString("%1GB/%2GB").arg(occupyCap).arg(m_strTotalCap));
	if (occupyCap.toFloat() / m_strTotalCap.toFloat() > 0.7)
		m_pLabHardDisk->setStyleSheet("color:red");
	else
		m_pLabHardDisk->setStyleSheet("color:black");
}

// 接收数据的槽函数
void MainWindow::RecvUdpData()
{
	QByteArray array;
	array.resize(m_UdpSocket->bytesAvailable());//根据可读数据来设置空间大小
	m_UdpSocket->readDatagram(array.data(), array.size()); //读取数据
	//qDebug() << "udp: " << array << " size:" << array.size();

	// 0x03-跟踪类型  0x0F-VGA锁定状态  '3'(0x51)-第三方直播推流状态
	if (array[16] == '\x03')
	{
		if (array[20] == '\x00')
		{
			//qDebug() << "不同步自动跟踪状态";
			m_isTrack = false;
			m_pBtnTrack->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnTrack_0.png)");
		}
		else
		{
			//qDebug() << "同步自动跟踪状态";
			m_isTrack = true;
			m_pBtnTrack->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnTrack_1.png)");
		}
		if (array[24] == '\x00')
		{
			//qDebug() << "不同步智能切换状态";
			m_isSwitch = false;
			m_pBtnSwitch->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnSwitch_0.png)");
		}
		else
		{
			//qDebug() << "同步智能切换状态";
			m_isSwitch = true;
			m_pBtnSwitch->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnSwitch_1.png)");
		}
	}
	else if (array[16] == '\x0F')
	{
		if (array[20] == '\x00')
		{
			//qDebug() << "不同步VGA锁定状态";
			m_isLockVGA = false;
			m_pBtnLockVGA->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnLockVGA_0.png)");
		}
		else
		{
			//qDebug() << "同步VGA锁定状态";
			m_isLockVGA = true;
			m_pBtnLockVGA->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnLockVGA_1.png)");
		}
	}
	else if (array[16] == '3')
	{
		if (array[20] == '\x00')
		{
			//qDebug() << "不同步直播推流状态";
			m_isLive = false;
			m_pBtnLive->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnLive_0.png)");
		}
		else
		{
			//qDebug() << "同步直播推流状态";
			m_isLive = true;
			m_pBtnLive->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnLive_1.png)");
		}
	}
}
