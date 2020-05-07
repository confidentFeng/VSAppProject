#include "MainWindow.h"

MainWindow::MainWindow(QDialog *parent)
	: QDialog(parent)
{
	/* ������-��ʼ�� */
	this->setFixedSize(WIN_WIDTH, WIN_HEIGHT);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->setAttribute(Qt::WA_DeleteOnClose);
	//this->resize(deskWidth, deskHeight);

	/* �����������ӽ���-��ʼ�� */
	m_pWidgetTop = new QWidget;
	m_pWidgetBottom = new QWidget;
	m_pWidgetTop->setObjectName("MainWindow_WidgetTop");
	m_pWidgetBottom->setObjectName("MainWindow_WidgetBottom");
	m_pWidgetTop->setFixedSize(1920, 70);
	m_pWidgetBottom->setFixedSize(1920, 130);

	/* ����-��ʼ�� */
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
	m_pLabIPText->setText("IP��ַ��");
	m_pLabHardDiskText->setText("Ӳ��������");
	m_pLabHardDisk->setText("000GB/000GB");
	m_pBatteryItem->setFixedSize(60, 31);
	m_pBtnNetwork->setFixedSize(50, 36);
	m_pBtnSysSet->setFixedSize(38, 38);
	m_pBtnShutdown->setFixedSize(38, 38);
	m_pBatteryItem->setBatteryValue(30);
	m_pBatteryItem->setShowText(1);
	m_pBatteryItem->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BatteryItem.png)");

	/* �����-��ʼ�� */
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

	/* ��Ƶ����Frame����-��ʼ��*/
	m_pVedioFrame = new QFrame;
	m_pVideoWidget = new QWidget(m_pVedioFrame);
	m_pVideoWidget->setFixedSize(1920, 1080); // 1080P��1.777�ĺ�����  1720 934 1660 934
	m_pVideoWidget->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
		"background-color: rgb(0, 0, 0);\n"
		"border:none;"));
	// ��ʼ��mpvPlayer
	mpvPlayer = new MpvPlayer(m_pVideoWidget);

	/* ���� */
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
	m_pLabRecord->setText("   ¼��   ");
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

	/* ����-ˮƽ���� */
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

	/* �����-��ֱ���� */
	QVBoxLayout *pVLayoutSide = new QVBoxLayout;
	pVLayoutSide->addWidget(m_pBtnReview);
	pVLayoutSide->addWidget(m_pBtnSplitSet);
	pVLayoutSide->addWidget(m_pBtnOSD);

	/* ¼��-��ֱ���� */
	m_pWidgetRecord = new QWidget;
	m_pWidgetRecord->setFixedSize(120, 112);
	QVBoxLayout *pVLayoutRecord = new QVBoxLayout(m_pWidgetRecord);
	pVLayoutRecord->addWidget(m_pBtnRecord, 0, Qt::AlignCenter);
	pVLayoutRecord->addWidget(m_pLabRecord);

	/* ����-ˮƽ���� */
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

	/* ������ */
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

	/* ��־λ-��ʼ�� */
	m_isLive = false;
	m_isRecord = false;
	m_isPause = false;
	m_isLockVGA = false;
	m_isSwitch = false;
	m_isTrack = false;

	/* ֱ��\¼�ƶ�ʱ��-��ʼ�� */
	m_pTimeRecord;
	m_pTimerRecord = new QTimer(this);
	connect(m_pTimerRecord, SIGNAL(timeout()), this, SLOT(RecordTimeOutSlot()));
	connect(this, &MainWindow::PauseSignal, this, &MainWindow::PauseSlot);

	/* ����-���Ӳۺ��� */
	connect(m_pBtnNetwork, SIGNAL(clicked()), this, SLOT(NetSetSlot()));
	connect(m_pBtnSysSet, SIGNAL(clicked()), this, SLOT(SysSetSlot()));
	connect(m_pBtnShutdown, SIGNAL(clicked()), this, SLOT(ShutdownSlot()));

	/* ����-���Ӳۺ��� */
	connect(m_pBtnRecord, SIGNAL(clicked()), this, SLOT(RecordSlot()));
	connect(m_pBtnPause, SIGNAL(clicked()), this, SLOT(PauseSlot()));
	connect(m_pBtnLockVGA, SIGNAL(clicked()), this, SLOT(LockVGASlot()));
	connect(m_pBtnLive, SIGNAL(clicked()), this, SLOT(LiveSlot()));
	connect(m_pBtnSwitch, SIGNAL(clicked()), this, SLOT(SwitchSlot()));
	connect(m_pBtnTrack, SIGNAL(clicked()), this, SLOT(TrackSlot()));
	connect(m_pBtnLockScr, SIGNAL(clicked()), this, SLOT(LockScrSlot()));

	/* ��������ϵͳʱ�� */
	QDateTime *datatime = new QDateTime(QDateTime::currentDateTime());
	QString str = datatime->toString("yyyy-MM-dd hh:mm:ss");
	m_pLabTime->setText(str);
	// ��ʼ��ϵͳʱ�䶨ʱ��
	m_pSysTimer = new QTimer;
	m_pSysTimer->setInterval(1000);
	m_pSysTimer->start();
	connect(m_pSysTimer, SIGNAL(timeout()), this, SLOT(timeoutSlot()));

	// ��ʼ�������ؼ�
	InitPowerMonitoring();

	// ����UDP�׽��ֶ���
	m_UdpSocket = new QUdpSocket();
	// ���ӷ�����(�ڶ���������ʾ����������ַ���Ӹù㲥)
	if (m_UdpSocket->bind(6601, QUdpSocket::ShareAddress))
		connect(m_UdpSocket, SIGNAL(readyRead()), this, SLOT(RecvUdpData()));
	else
		qDebug() << "UDP��ʧ�ܣ�";
	// ��������UDP�����ź�
	UdpClient::Get()->SendData(1, 1, 0);

	// ��ʼ���������
	InitNetwork();

	// ��ʼһ����ʱ���������
	timeIDNetCheck = this->startTimer(1000 * 3);

	// ��ʼһ����ʱ�����¼��״̬
	timeIDRecord = this->startTimer(1000 * 5);
}

MainWindow::~MainWindow()
{

}

// ��ʼ���������
void MainWindow::InitNetwork()
{
	// 1. ����Ĭ����ѡ������������������������
	CmdThread *cmdCmdThread1 = new CmdThread("netsh interface set interface name=\"��̫��\" admin=ENABLED");
	cmdCmdThread1->start();
	CmdThread *cmdCmdThread2 = new CmdThread("netsh interface set interface name=\"WLAN 2\" admin=ENABLED");
	cmdCmdThread2->start();

	// 2. ���������̫�����������簴ť��ͼ��
	bool bHaveWired = false;
	bool bHaveWifi = false;
	QString strCmdOut = Common::Get()->ExecuteCmd2("netsh interface ipv4 show ipaddress interface=��̫��");
	QStringList strCmdOutList = strCmdOut.split("\r\n");
	for (int i = 0; i<strCmdOutList.size(); i++)
	{
		if (strCmdOutList[i].contains("��ѡ��")) // �����������߲��룬������;��������
		{
			bHaveWired = true;
			break;
		}
	}

	// 3. �������wifi���������簴ť��ͼ��
	QString strCmdOutWifi = Common::Get()->ExecuteCmd2("netsh interface ipv4 show ipaddress interface=\"WLAN 2\"");
	QStringList strCmdOutListWifi = strCmdOutWifi.split("\r\n");
	for (int i = 0; i<strCmdOutListWifi.size(); i++)
	{
		if (strCmdOutListWifi[i].contains("��ѡ��")) // ��wifi
		{
			bHaveWifi = true;
			break;
		}
	}

	// 4. ��������ͼ��
	if (bHaveWired == true)
		m_pBtnNetwork->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWindow_BtnNetwork_1.png)");
	else if (bHaveWired == false && bHaveWifi == false)
		m_pBtnNetwork->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWindow_BtnNetwork_2.png)");
	else
		m_pBtnNetwork->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWindow_BtnNetwork_0.png)");
}

// ��ʼ�������ؼ�
void MainWindow::InitPowerMonitoring()
{
	// �״λ�ȡϵͳ����
	SYSTEM_POWER_STATUS PowerSatus;
	if (GetSystemPowerStatus(&PowerSatus))
	{
		if (m_pBatteryItem)
		{
			if ((int)PowerSatus.ACLineStatus)
				// ���
				m_pBatteryItem->setShowText(3);
			else
				m_pBatteryItem->setShowText(1);

			int npower = (int)PowerSatus.BatteryLifePercent;
			m_pBatteryItem->setBatteryValue(npower);
			if (npower <= 20)
				m_pBatteryItem->setBatteryColor(2);// ��ɫ

			if (npower > 20)
				m_pBatteryItem->setBatteryColor(0);//��ɫ
		}
	}

	// ��ʼһ����ʱ��������
	timeIDPower = this->startTimer(1000 * 3);
}

// ���´���
void MainWindow::updataWin()
{
	// ���´���ʱ���ٴη���UDP�����ź�
	UdpClient::Get()->SendData(1, 1, 0);

	/* ��������ʾʱ���Ŷ�ȡ�����ļ��е���Ϣ(����Ҳһ��) */
	QString iniFilePath = QApplication::applicationDirPath() + "/config.ini";
	QSettings *iniRead = new QSettings(iniFilePath, QSettings::IniFormat);
	m_hostIP = iniRead->value("hostIP").toString();
	qDebug() << "updataWin_hostIP: " << m_hostIP;
	delete iniRead;

	// RTMP����
	mpvPlayer->play(QString("rtmp://%1/live/main").arg(m_hostIP));

	/* ��������IP��Ӳ������ */
	m_pLabIP->setText(m_hostIP);

	// http���͡���ȡӲ�̴洢��Ϣ��
	HttpClient(QString("http://%1/ROCPOW.cgi?type=77").arg(m_hostIP)).success([&](const QString &response) {
		m_strFreeCap = QString(response).section(QRegExp("[,]"), 0, 0).section(QRegExp("[:]"), 2, 2);
		m_strTotalCap = QString(response).section(QRegExp("[}]"), 0, 0).section(QRegExp("[:]"), 3, 3);
	}).fail([](const QString &error, int errorCode) {
		qDebug().noquote() << "error: " << error << errorCode << endl;
	}).get();
}

// �����̫����wifi����ȷ������ͼ��
void MainWindow::CheckNet()
{
	CmdThread *cmdCmdThread1 = new CmdThread("netsh interface ipv4 show ipaddress interface=��̫��");
	cmdCmdThread1->start();
	connect(cmdCmdThread1, SIGNAL(resultReady(QString)), this, SLOT(WiredNetSlot(QString)));

	CmdThread *cmdCmdThread2 = new CmdThread("netsh interface ipv4 show ipaddress interface=\"WLAN 2\"");
	cmdCmdThread2->start();
	connect(cmdCmdThread2, SIGNAL(resultReady(QString)), this, SLOT(WifiNetSlot(QString)));
}

// ��̫�����ۺ���
void MainWindow::WiredNetSlot(const QString &strCmdOut)
{
	// �����̫�����������簴ť��ͼ��
	static bool bAllowFlag = true;
	QStringList strCmdOutList = strCmdOut.split("\r\n");
	if (strCmdOutList[7].contains("��ѡ��")) // ��;��������
	{
		bHaveWired = true;

		// ��������������ͼ��ʱ����⵽��;�������ߣ��򵯳�IP���ô��ڣ������ظ�����
		if (bAllowFlag && m_pBtnNetwork->styleSheet() != "border-image: url(:/MainWindow/image/MainWindow/MainWindow_BtnNetwork_1.png)")
		{
			bAllowFlag = false;

			if (m_bHaveWifi)
			{
				MyMessageBox *pMyMessageBox = new MyMessageBox(this);
				pMyMessageBox->ShowControl(false, true, "��������");
				pMyMessageBox->SetInfoText("ϵͳ��⵽���Ѳ������ߣ��Ƿ��޸���������");
				int res = pMyMessageBox->exec();
				if (res == QDialog::Rejected)
					return;
			}

			NetConfig *m_pNetConfigWired = new NetConfig(this, false);
			m_pNetConfigWired->SetBtnReturnText("ȡ��");
			int res = m_pNetConfigWired->exec();
			if (res == QDialog::Accepted)
			{
				// ����ȷ����ť�󣬲��л�Ϊ��������ͼ��
				m_pBtnNetwork->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWindow_BtnNetwork_1.png)");

				// �����������һ�Ƕ���״̬������������wifi״̬����Ҫ����������wifi���Ͽ�
				// 1. ���ҳ�������wifi������
				QString strCmdCon = Common::Get()->ExecuteCmd2("netsh wlan show interface");
				QStringList strListCon = strCmdCon.split("\r\n");
				QString strConWifiName = "null"; // �����б���������Ϊ""��wifi
				if (strListCon.size() > 15) // ������wifi�Ļ��������������24�У�����ֻ��14��
				{
					QStringList strListWifiName = strListCon[19].split(": ");
					strConWifiName = strListWifiName[1].remove(" ");

					// 2. ��������wifi�Ͽ�
					Common::Get()->ExecuteCmd2(QString("netsh wlan delete profile name=%1").arg(strConWifiName));
				}

				// ��������ʱһ��ʱ�䣬�ȴ��޸�IP�������л��ɹ�
				QEventLoop eventloop;
				QTimer::singleShot(2500, &eventloop, SLOT(quit()));
				eventloop.exec();

				// ���´���
				updataWin();
			}
		}
	}
	else if(strCmdOutList[7].contains("����")) // ��;�γ�����
	{
		bAllowFlag = true;
		bHaveWired = false;

		if(!m_bHaveWifi)
			m_pBtnNetwork->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWindow_BtnNetwork_2.png)");
	}
}

// wifi���ۺ���
void MainWindow::WifiNetSlot(const QString &strCmdOut)
{
	static bool bAllowWifiFlag = true;
	m_bHaveWifi = false;

	// ���wifi���������簴ť��ͼ��
	QStringList strCmdOutListWifi = strCmdOut.split("\r\n");
	if (strCmdOutListWifi[7].contains("��ѡ��")) // ��;����wifi
	{
		m_bHaveWifi = true;
		if (bAllowWifiFlag && !bHaveWired)
		{
			bAllowWifiFlag = false;
			m_pBtnNetwork->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWindow_BtnNetwork_0.png)");

			// ���´���
			updataWin();
		}
	}
	else if (strCmdOutListWifi[7].contains("����")) // ������wifi
		bAllowWifiFlag = true;
}

// ��ʾ�¼������������Qt::FramelessWindowHint�����治������ˢ�µ�����
void MainWindow::showEvent(QShowEvent *event)
{
	updataWin(); // �������´���

	this->setAttribute(Qt::WA_Mapped);
	QWidget::showEvent(event);
}

// ���̰����¼�:���ڰ�Alt+M���رճ���
void MainWindow::keyPressEvent(QKeyEvent * event)
{
	// �ȼ��Alt���Ƿ���
	if (event->modifiers() == Qt::AltModifier)
	{
		// ����ǣ���ô�ټ��M���Ƿ���
		if (event->key() == Qt::Key_M)
		{
			this->close();
		}
	}
}

// ��ʱ���¼�
void MainWindow::timerEvent(QTimerEvent* event)
{
	if (event->timerId() == timeIDPower)
	{
		// ��ȡϵͳ����
		SYSTEM_POWER_STATUS PowerSatus;
		if (GetSystemPowerStatus(&PowerSatus))
		{
			if ((int)PowerSatus.ACLineStatus)
				// ���
				m_pBatteryItem->setShowText(3);
			else
				m_pBatteryItem->setShowText(1);

			int npower = (int)PowerSatus.BatteryLifePercent;
			m_pBatteryItem->setBatteryValue(npower);
			if (npower <= 20)
				m_pBatteryItem->setBatteryColor(2);// ��ɫ

			if (npower > 20)
				m_pBatteryItem->setBatteryColor(0);// ��ɫ
		}
	}

	// �������
	if (event->timerId() == timeIDNetCheck)
	{
		// �����̫����wifi����ȷ������ͼ��
		CheckNet();
	}

	// ���¼��״̬
	if (event->timerId() == timeIDRecord)
	{
		//// http���͡���ȡ¼����Ϣ��
		//HttpClient(QString("http://%1/ROCPOW.cgi?type=16").arg(m_hostIP)).success([&](const QString &response) {
		//	//m_strFreeCap = QString(response).section(QRegExp("[,]"), 0, 0).section(QRegExp("[:]"), 2, 2);
		//	//m_strTotalCap = QString(response).section(QRegExp("[}]"), 0, 0).section(QRegExp("[:]"), 3, 3);
		//}).fail([](const QString &error, int errorCode) {
		//	qDebug().noquote() << "error: " << error << errorCode << endl;
		//}).get();
	}
}

// �������õĲۺ���
void MainWindow::NetSetSlot()
{
	// �������������״̬�����޷��޸�Ϊwifi���ӣ������ť��Ч
	if (m_pBtnNetwork->styleSheet() == "border-image: url(:/MainWindow/image/MainWindow/MainWindow_BtnNetwork_1.png)")
		return;

	// ʹ��QStackedWidget�л�������ʾ
	StackedWidget *pMainWidget = new StackedWidget(this);
	pMainWidget->SetStackCurIndex(0);
	int res = pMainWidget->exec();

	if (res == QDialog::Accepted)
	{
		m_pBtnNetwork->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWindow_BtnNetwork_0.png)");

		// ��������ʱһ��ʱ�䣬�ȴ��޸�IP�������л��ɹ�(ÿ�δ��������ӽ��涼ִ��������򣬲������)
		QEventLoop eventloop;
		QTimer::singleShot(3000, &eventloop, SLOT(quit())); // 2500
		eventloop.exec();

		updataWin(); // ���´���
	}
}

// ϵͳ���õĲۺ���
void MainWindow::SysSetSlot()
{
	/* �������ļ������ڳ�ʼ��BindHost���� */
	QString iniFilePath = QApplication::applicationDirPath() + "/config.ini";
	QSettings *iniRead = new QSettings(iniFilePath, QSettings::IniFormat);
	QString hostIP = iniRead->value("hostIP").toString();
	int hostPort = iniRead->value("hostPort").toInt();
	QString hostAccount = iniRead->value("hostAccount").toString();
	QString hostPasswd = iniRead->value("hostPasswd").toString();
	delete iniRead;

	// ģ̬��ʾ���ý���
	BindHost *bindHost = new BindHost(this);
	bindHost->IsFirstOpen(false);
	bindHost->SetHostIP(hostIP);
	bindHost->SetHostPort(hostPort);
	bindHost->SetHostAccount(hostAccount);
	bindHost->SetHostPasswd(hostPasswd);
	int res = bindHost->exec();
	if (res == QDialog::Accepted)
	{
		updataWin(); // ���´���
	}
}

// �ػ��Ĳۺ���
void MainWindow::ShutdownSlot()
{
	// ģ̬��ʾ��Ϣ�����
	MyMessageBox *pMyMessageBox = new MyMessageBox(this);
	if (m_isLive == true || m_isRecord == true)
		pMyMessageBox->SetInfoText("��ǰ����ֱ����¼�ƣ��Ƿ�ֹͣ���رձ�����\n���˲������رձ��������ᵼ��¼�������ػ���");
	else
		pMyMessageBox->SetInfoText("�˲������رձ��������ᵼ��¼�������ػ���");
	int res = pMyMessageBox->exec();
	// ����Ƿ�����ȷ�ϰ�ť
	if (res == QDialog::Accepted)
	{
		system("shutdown -s -t 00");
	}
}

// ¼����Ƶ
void MainWindow::RecordSlot()
{
	if (!m_isRecord)
	{
		// ģ̬��ʾ����¼����Ϣ����
		InputRecInfo *pInputRecInfo = new InputRecInfo(this);
		int res = pInputRecInfo->exec();

		// ���"����¼����Ϣ����"�Ƿ������水ť��ر���
		if (res == QDialog::Accepted)
		{
			m_isRecord = true;

			m_recordTime = 0;
			// �л�¼�ư�ť����ʽ���ı�
			m_pBtnRecord->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnRecord_1.png)");
			m_pLabRecord->setText("00:00:00");
			// 1.�����ʼ���ȡ����ǰ��ʱ�䲢�Ҹ�ֵ��m_pTimeRecord				
			m_pTimeRecord = m_pTimeRecord.currentTime();
			// 2.������ʱ��m_pTimerRecord, ���1s
			m_pTimerRecord->start(1);

			#if HTTP_TEST
			// http���͡���ʼ¼�ơ�
			HttpClient(QString("http://%1/ROCPOW.cgi?type=15&state=1").arg(m_hostIP)).success([](const QString &response) {
				qDebug().noquote() << "��ʼ¼��: " << response << endl;
			}).fail([](const QString &error, int errorCode) {
				qDebug().noquote() << "error: " << error << errorCode << endl;
			}).get();
			#endif
		}
	}
	else
	{	
		// ģ̬��ʾ��Ϣ�����
		MyMessageBox *pMyMessageBox = new MyMessageBox(this);
		pMyMessageBox->SetInfoText("�Ƿ�ֹͣ¼�ƣ�");
		int res = pMyMessageBox->exec();

		// ���"������Ϣ�����"�Ƿ������水ť��ر���
		if (res == QDialog::Accepted)
		{
			m_isRecord = false;

			// �ָ�¼�ư�ť����ʽ���ı�
			m_pBtnRecord->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnRecord_0.png)");
			m_pLabRecord->setText("   ¼��   ");
			// ֹͣ¼�Ƽ�ʱ
			m_pTimerRecord->stop();

			// ֹͣ¼�ƺ�,���������ͣ������"��ͣ¼���ź�"����ͣ¼��
			if (m_isPause)
				emit PauseSignal();

			#if HTTP_TEST
			// http���͡�ֹͣ¼�ơ�
			HttpClient(QString("http://%1/ROCPOW.cgi?type=15&state=0").arg(m_hostIP)).success([](const QString &response) {
				qDebug().noquote() << "��ʼ¼��: " << response << endl;
			}).fail([](const QString &error, int errorCode) {
				qDebug().noquote() << "error: " << error << errorCode << endl;
			}).get();
			#endif
		}
	}
}

// ��ͣ/�ָ�¼��
void MainWindow::PauseSlot()
{
	// ������¼�Ʋſ�����ͣ
	static QTime pauseTime;
	if (!m_isPause && m_isRecord==true)
	{
		m_isPause = true;

		// �л���ͣ��ť����ʽ
		m_pBtnPause->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnPause_1.png)");
		
		// �����ͣʱ��ʱ�䣬����¼�Ƽ�ʱ
		pauseTime = QTime::currentTime();
		// ��ʱ�ر�¼�Ƽ�ʱ��
		m_pTimerRecord->stop();

		#if HTTP_TEST
		// http���͡���ͣ¼�ơ�
		HttpClient(QString("http://%1/ROCPOW.cgi?type=15&state=2").arg(m_hostIP)).success([](const QString &response) {
			qDebug().noquote() << "��ͣ¼��: " << response << endl;
		}).fail([](const QString &error, int errorCode) {
			qDebug().noquote() << "error: " << error << errorCode << endl;
		}).get();
		#endif
	}
	else
	{
		m_isPause = false;

		// �ָ���ͣ��ť����ʽ
		m_pBtnPause->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnPause_0.png)");

		// ���в�ֵ���㲢�ָ���¼�Ƽ�ʱ��
		QTime cut = QTime::currentTime();
		int t = pauseTime.msecsTo(cut);
		m_pTimeRecord = m_pTimeRecord.addMSecs(t);
		// ��¼�ƽ��е�����£��Ŵ�¼�Ƽ�ʱ��
		if(m_isRecord)
			m_pTimerRecord->start();

		#if HTTP_TEST
		// http���͡���ʼ¼�ơ�(�ָ�¼��)
		HttpClient(QString("http://%1/ROCPOW.cgi?type=15&state=1").arg(m_hostIP)).success([](const QString &response) {
			qDebug().noquote() << "�ָ�¼��: " << response << endl;
		}).fail([](const QString &error, int errorCode) {
			qDebug().noquote() << "error: " << error << errorCode << endl;
		}).get();
		#endif
	}
}

// ¼�ƶ�ʱ����ʱ����
void MainWindow::RecordTimeOutSlot()
{
	/*
	* 1.�����ʼ���ȡ����ǰ��ʱ�䲢�Ҹ�ֵ��m_pTimeRecord
	* 2.������ʱ��m_pTimerRecord,���1s
	* 3.��ʱ�ۺ������ٴλ�ȡ��ǰ��ʱ��currTime
	* 4.��������ʱ��Ĳ�ֵt,��¼��ʱ��
	*/
	QTime currTime = QTime::currentTime();
	int t = m_pTimeRecord.msecsTo(currTime);

	//recordTime++;
	m_recordTime = t / 1000;
	char buf[1024] = { 0 };
	sprintf(buf, "%02d:%02d:%02d", m_recordTime / 3600, m_recordTime / 60, m_recordTime % 60);
	m_pLabRecord->setText(buf);
}

// ����VGA�Ĳۺ���
void MainWindow::LockVGASlot()
{
	if (!m_isLockVGA)
	{
		m_isLockVGA = true;
		m_pBtnLockVGA->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnLockVGA_1.png)");

		// UDP����"����VGA����"����
		UdpClient::Get()->SendData(15, 1, 0);

		#if HTTP_TEST
		// http���͡������л�ֱ�����桱(view����ͷ�����±꣬��1��ʼ����)
		HttpClient(QString("http://%1/ROCPOW.cgi?type=90&view=8").arg(m_hostIP)).success([](const QString &response) {
			qDebug().noquote() << "�����л�ֱ������: " << response << endl;
		}).fail([](const QString &error, int errorCode) {
			qDebug().noquote() << "error: " << error << errorCode << endl;
		}).get();
		#endif
	}
	else
	{
		m_isLockVGA = false;
		m_pBtnLockVGA->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnLockVGA_0.png)");

		// UDP����"ȡ��VGA����"����
		UdpClient::Get()->SendData(15, 0, 0);
	}
}

// ֱ������/�رյĲۺ���
void MainWindow::LiveSlot()
{
	if (!m_isLive)
	{
		m_isLive = true;
		m_pBtnLive->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnLive_1.png)");

		// UDP����"����ֱ��"����
		UdpClient::Get()->SendData(51, 1, 0);

#if 1
		// http���͡����õ�����ֱ������������
		HttpClient(QString("http://%1/ROCPOW.cgi?type=50&token=xx&pushstat=1").arg(m_hostIP)).success([](const QString &response) {
			qDebug().noquote() << "���õ�����ֱ������: " << response << endl;
		}).fail([](const QString &error, int errorCode) {
			qDebug().noquote() << "error: " << error << errorCode << endl;
		}).get();
#endif
	}
	else
	{
		m_isLive = false;
		m_pBtnLive->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnLive_0.png)");

		// UDP����"�ر�ֱ��"����
		UdpClient::Get()->SendData(51, 0, 0);

		#if 1
		// UDP����"�رյ�����ֱ������"����
		HttpClient(QString("http://%1/ROCPOW.cgi?type=50&token=xx&pushstat=0").arg(m_hostIP)).success([](const QString &response) {
			qDebug().noquote() << "�رյ�����ֱ������: " << response << endl;
		}).fail([](const QString &error, int errorCode) {
			qDebug().noquote() << "error: " << error << errorCode << endl;
		}).get();
		#endif
	}
}

// �Զ��л�����/�رյĲۺ���
void MainWindow::SwitchSlot()
{
	if (!m_isSwitch)
	{
		m_isSwitch = true;
		m_pBtnSwitch->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnSwitch_1.png)");

		// UDP����"�����Զ��л�"����
		UdpClient::Get()->SendData(3, m_isTrack, 1);
	}
	else
	{
		m_isSwitch = false;
		m_pBtnSwitch->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnSwitch_0.png)");

		// UDP����"�ر��Զ��л�"����
		UdpClient::Get()->SendData(3, m_isTrack, 0);
	}
}

// �Զ����ٿ���/�رյĲۺ���
void MainWindow::TrackSlot()
{
	if (!m_isTrack)
	{
		m_isTrack = true;
		m_pBtnTrack->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnTrack_1.png)");

		// UDP����"�����Զ�����"����
		UdpClient::Get()->SendData(3, 1, m_isSwitch);
	}
	else
	{
		m_isTrack = false;
		m_pBtnTrack->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnTrack_0.png)");

		// UDP����"�ر��Զ�����"����
		UdpClient::Get()->SendData(3, 0, m_isSwitch);
	}
}

// �����Ĳۺ���
void MainWindow::LockScrSlot()
{
	// ��ʾ��������
	LockScreen *pLockScreen = new LockScreen(this);
	pLockScreen->show();
}

// ��ʱ����ʱ�ۺ���������ʵʱ��ȡʱ���Ӳ������
void MainWindow::timeoutSlot()
{
	QDateTime *datatime = new QDateTime(QDateTime::currentDateTime());
	QString str = datatime->toString("yyyy-MM-dd hh:mm:ss");
	m_pLabTime->setText(str);
	
	// �ֱ���ʾӲ��ռ�ú���������������ֵ(70%)��ʾ��ɫ
	QString occupyCap = QString::number(m_strTotalCap.toInt() - m_strFreeCap.toInt());
	m_pLabHardDisk->setText(QString("%1GB/%2GB").arg(occupyCap).arg(m_strTotalCap));
	if (occupyCap.toFloat() / m_strTotalCap.toFloat() > 0.7)
		m_pLabHardDisk->setStyleSheet("color:red");
	else
		m_pLabHardDisk->setStyleSheet("color:black");
}

// �������ݵĲۺ���
void MainWindow::RecvUdpData()
{
	QByteArray array;
	array.resize(m_UdpSocket->bytesAvailable());//���ݿɶ����������ÿռ��С
	m_UdpSocket->readDatagram(array.data(), array.size()); //��ȡ����
	//qDebug() << "udp: " << array << " size:" << array.size();

	// 0x03-��������  0x0F-VGA����״̬  '3'(0x51)-������ֱ������״̬
	if (array[16] == '\x03')
	{
		if (array[20] == '\x00')
		{
			//qDebug() << "��ͬ���Զ�����״̬";
			m_isTrack = false;
			m_pBtnTrack->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnTrack_0.png)");
		}
		else
		{
			//qDebug() << "ͬ���Զ�����״̬";
			m_isTrack = true;
			m_pBtnTrack->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnTrack_1.png)");
		}
		if (array[24] == '\x00')
		{
			//qDebug() << "��ͬ�������л�״̬";
			m_isSwitch = false;
			m_pBtnSwitch->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnSwitch_0.png)");
		}
		else
		{
			//qDebug() << "ͬ�������л�״̬";
			m_isSwitch = true;
			m_pBtnSwitch->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnSwitch_1.png)");
		}
	}
	else if (array[16] == '\x0F')
	{
		if (array[20] == '\x00')
		{
			//qDebug() << "��ͬ��VGA����״̬";
			m_isLockVGA = false;
			m_pBtnLockVGA->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnLockVGA_0.png)");
		}
		else
		{
			//qDebug() << "ͬ��VGA����״̬";
			m_isLockVGA = true;
			m_pBtnLockVGA->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnLockVGA_1.png)");
		}
	}
	else if (array[16] == '3')
	{
		if (array[20] == '\x00')
		{
			//qDebug() << "��ͬ��ֱ������״̬";
			m_isLive = false;
			m_pBtnLive->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnLive_0.png)");
		}
		else
		{
			//qDebug() << "ͬ��ֱ������״̬";
			m_isLive = true;
			m_pBtnLive->setStyleSheet("border-image: url(:/MainWindow/image/MainWindow/MainWidget_BtnLive_1.png)");
		}
	}
}
