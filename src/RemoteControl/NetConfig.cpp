#include "NetConfig.h"

NetConfig::NetConfig(QDialog *parent, const bool& bIsWifi)
	: QDialog(parent)
{
	/* 网络配置界面-初始化 */
	this->setFixedSize(700, 516);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

	/* 子界面-初始化 */
	m_pWidgetChild = new QWidget(this);
	m_pWidgetChild->setGeometry(0, 0, 700, 516);
	m_pWidgetChild->setObjectName("NetConfig_WidgetChild");

	/* 窗口部件-初始化 */
	m_pLabTitle = new QLabel;
	m_pBtnClose = new QPushButton;
	m_pRadioAuto = new QRadioButton;
	m_pLabAuto = new QLabel;
	m_pRadioManual = new QRadioButton;
	m_pLabManual = new QLabel;
	m_pLabIP = new QLabel;
	m_pEditIP = new QLineEdit;
	m_pLabMask = new QLabel;
	m_pEditMask = new QLineEdit;
	m_pLabGway = new QLabel;
	m_pEditGway = new QLineEdit;
	m_pBtnReturn = new QPushButton;
	m_pBtnNext = new QPushButton;
	m_pLabTitle->setObjectName("NetConfig_LabTitle");
	m_pBtnClose->setObjectName("NetConfig_BtnClose");
	m_pRadioAuto->setObjectName("NetConfig_RadioAuto");
	m_pLabAuto->setObjectName("NetConfig_LabAuto");
	m_pRadioManual->setObjectName("NetConfig_RadioManual");
	m_pLabManual->setObjectName("NetConfig_LabManual");
	m_pLabIP->setObjectName("NetConfig_LabIP");
	m_pEditIP->setObjectName("NetConfig_EditIP");
	m_pLabMask->setObjectName("NetConfig_LabMask");
	m_pEditMask->setObjectName("NetConfig_EditMask");
	m_pLabGway->setObjectName("NetConfig_LabGway");
	m_pEditGway->setObjectName("NetConfig_EditGway");
	m_pBtnReturn->setObjectName("NetConfig_BtnReturn");
	m_pBtnNext->setObjectName("NetConfig_BtnNext");
	if(bIsWifi)
		m_pLabTitle->setText("IP设置-无线");
	else
		m_pLabTitle->setText("IP设置-有线");
	m_pLabAuto->setText("自动获取IP地址");
	m_pLabManual->setText("使用下面的IP地址");
	m_pLabIP->setText("IP地址");
	m_pLabMask->setText("子网掩码");
	m_pLabGway->setText("默认网关");
	m_pBtnReturn->setText("返回");
	m_pBtnNext->setText("确定");
	m_pEditIP->setFixedSize(400, 48);
	m_pBtnClose->setFixedSize(42, 42);
	m_pEditMask->setFixedSize(400, 48);
	m_pEditGway->setFixedSize(400, 48);
	m_pBtnReturn->setFixedSize(160, 56);
	m_pBtnNext->setFixedSize(160, 56);
	m_pEditIP->setValidator(new QRegExpValidator(QRegExp(REGEXP_IP)));
	m_pEditMask->setValidator(new QRegExpValidator(QRegExp(REGEXP_IP)));
	m_pEditGway->setValidator(new QRegExpValidator(QRegExp(REGEXP_IP)));

	/* 标题栏-水平布局 */
	QHBoxLayout *pHLayoutTitle = new QHBoxLayout;
	pHLayoutTitle->addSpacing(10);
	pHLayoutTitle->addWidget(m_pLabTitle);
	pHLayoutTitle->addStretch(1);
	pHLayoutTitle->addWidget(m_pBtnClose);
	pHLayoutTitle->addSpacing(10);

	/* 单选框相关-水平布局 */
	QHBoxLayout *pHLayoutRadio = new QHBoxLayout;
	pHLayoutRadio->addStretch(1);
	pHLayoutRadio->addWidget(m_pRadioAuto);
	pHLayoutRadio->addSpacing(25);
	pHLayoutRadio->addWidget(m_pLabAuto);
	pHLayoutRadio->addSpacing(60);
	pHLayoutRadio->addWidget(m_pRadioManual);
	pHLayoutRadio->addSpacing(25);
	pHLayoutRadio->addWidget(m_pLabManual);
	pHLayoutRadio->addStretch(1);

	/* 文本框相关-网格布局 */
	QGridLayout *pGLayoutEdit = new QGridLayout;
	pGLayoutEdit->addWidget(m_pLabIP, 0, 0);
	pGLayoutEdit->addWidget(m_pEditIP, 0, 1);
	pGLayoutEdit->addWidget(m_pLabMask, 1, 0);
	pGLayoutEdit->addWidget(m_pEditMask, 1, 1);
	pGLayoutEdit->addWidget(m_pLabGway, 2, 0);
	pGLayoutEdit->addWidget(m_pEditGway, 2, 1);
	pGLayoutEdit->setHorizontalSpacing(28);
	pGLayoutEdit->setVerticalSpacing(20);
	pGLayoutEdit->setColumnStretch(2, 1);
	pGLayoutEdit->setContentsMargins(80, 0, 0, 0);

	/* 按钮相关-水平布局 */
	QHBoxLayout *pHLayoutBtn = new QHBoxLayout;
	pHLayoutBtn->addStretch(1);
	pHLayoutBtn->addWidget(m_pBtnReturn);
	pHLayoutBtn->addSpacing(40);
	pHLayoutBtn->addWidget(m_pBtnNext);
	pHLayoutBtn->addStretch(1);

	/* 主窗口-垂直布局 */
	QVBoxLayout *pVLayoutMain = new QVBoxLayout(m_pWidgetChild);
	pVLayoutMain->addSpacing(6);
	pVLayoutMain->addLayout(pHLayoutTitle);
	pVLayoutMain->addSpacing(50);
	pVLayoutMain->addLayout(pHLayoutRadio);
	pVLayoutMain->addSpacing(50);
	pVLayoutMain->addLayout(pGLayoutEdit);
	pVLayoutMain->addSpacing(50);
	pVLayoutMain->addLayout(pHLayoutBtn);
	pVLayoutMain->addSpacing(30);

	m_bIsWifi = bIsWifi;

	// 关闭按钮-点击槽函数
	QObject::connect(m_pBtnClose, &QPushButton::clicked, [=]() {
		this->reject();
		emit StackedWidgetClose();
	});

	// 自动获取IP单选按钮-点击槽函数
	QObject::connect(m_pRadioAuto, &QPushButton::clicked, [=]() {
		m_isManualFlag = false;
		m_pLabIP->setStyleSheet("color: #999999;");
		m_pEditIP->setStyleSheet("border: 1px solid rgb(153, 153, 153);");
		m_pEditIP->setEnabled(false);
		m_pEditIP->clear();
		m_pLabMask->setStyleSheet("color: #999999;");
		m_pEditMask->setStyleSheet("border: 1px solid rgb(153, 153, 153);");
		m_pEditMask->setEnabled(false);
		m_pEditMask->clear();
		m_pLabGway->setStyleSheet("color: #999999;");
		m_pEditGway->setStyleSheet("border: 1px solid rgb(153, 153, 153);");
		m_pEditGway->setEnabled(false);
		m_pEditGway->clear();
	});
	// 默认为自动连接，隐藏文本框相关
	m_pRadioAuto->setChecked(true);
	emit m_pRadioAuto->clicked();

	// 手动获取IP单选按钮-点击槽函数
	QObject::connect(m_pRadioManual, &QPushButton::clicked, [=]() {
		m_isManualFlag = true;
		m_pLabIP->setStyleSheet("color: #222222;");
		m_pEditIP->setStyleSheet("border: 1px solid rgb(139, 184, 250);");
		m_pEditIP->setEnabled(true);
		m_pEditIP->setText("172.10.1.198");
		m_pLabMask->setStyleSheet("color: #222222;");
		m_pEditMask->setStyleSheet("border: 1px solid rgb(139, 184, 250);");
		m_pEditMask->setEnabled(true);
		m_pEditMask->setText("255.255.0.0");
		m_pLabGway->setStyleSheet("color: #222222;");
		m_pEditGway->setStyleSheet("border: 1px solid rgb(139, 184, 250);");
		m_pEditGway->setEnabled(true);
		m_pEditGway->setText("172.10.10.1");
	});

	// 返回按钮-点击槽函数
	QObject::connect(m_pBtnReturn, &QPushButton::clicked, [=]() {
		this->close();
		emit BtnReturnClicked();
	});

	// 连接槽函数
	connect(m_pBtnNext, SIGNAL(clicked()), this, SLOT(NextSlot()));
}

NetConfig::~NetConfig()
{

}

void NetConfig::showEvent(QShowEvent * event)
{
	// 1. 获取以太网卡或者wifi网卡的MAC地址
	QString Mac;
	QList<QNetworkInterface> iface = QNetworkInterface::allInterfaces();
	for (int i = 0; i < iface.size(); i++)
	{		
		QNetworkInterface var = iface.at(i);
		//qDebug() << "var.humanReadableName(): " << var.humanReadableName();

		if (!m_bIsWifi)
		{
			if (var.humanReadableName() == "以太网")
			{
				humanReadableName = var.humanReadableName();
				Mac = var.hardwareAddress();
			}
		}
		else
		{
			if (var.humanReadableName() == "WLAN")
			{
				humanReadableName = var.humanReadableName();
				Mac = var.hardwareAddress();
			}
			else if (var.humanReadableName() == "WLAN 2")
			{
				humanReadableName = var.humanReadableName();
				Mac = var.hardwareAddress();
			}
		}
	}

	// 2. 判断是静态IP 还是动态IP
	if (isDhcpEnabled(Mac))
	{
		// 2.2 动态IP
		m_pRadioAuto->setChecked(true);
		m_pRadioManual->setChecked(false);
		qDebug() << "动态IP";
	}
	else
	{
		// 2.1 静态IP
		m_pRadioAuto->setChecked(false);
		m_pRadioManual->setChecked(true);
		emit m_pRadioManual->clicked();
		qDebug() << "静态IP";
	}
}

// 下一步槽函数
void NetConfig::NextSlot()
{
	// 1.判断 自动获取IP按钮 状态
	if (!m_isManualFlag)
	{
		// 1.1 勾选 设置网络为DHCP
		QProcess cmd;
		cmd.start(QString("netsh interface ip set address \"%1\" dhcp").arg(humanReadableName));
		cmd.waitForStarted();
		cmd.waitForFinished();
		QString strCmdOut = QString::fromLocal8Bit(cmd.readAllStandardOutput());
		qDebug() << "m_bIsWifi: " << m_bIsWifi <<" netCard: " << humanReadableName;
		qDebug() << "strCmdOut: " << strCmdOut;
		// 有时候执行命令后等待时间太短，已连接wifi还没来得及可以正常使用，则会返回"\r\n"
		// 但实际已经成功启用DHCP。（必须先连接wifi，才能正常启用DHCP）
		if (strCmdOut.contains("已在此接口上启用 DHCP。") || strCmdOut == "\r\n")
		{
			MyPromptBox *pPromptBox = new MyPromptBox;
			pPromptBox->setLabInfo("自动获取IP成功", SuccessIcon);
			pPromptBox->exec();

			this->accept();
			emit NetConfigSuc(); // 发射网络配置成功的信号
		}
		else
		{
			MyPromptBox *pPromptBox = new MyPromptBox;
			pPromptBox->setLabInfo("自动获取IP失败", FailIcon);
			pPromptBox->exec();

			this->reject();
			emit NetConfigSuc(); // 发射网络配置成功的信号(虽然自动获取失败了)
		}
	}
	else
	{
		// 要求各文本框都要有输入
		if (m_pEditIP->text() == "" || m_pEditMask->text() == "" || m_pEditGway->text() == "")
		{
			MyPromptBox *pPromptBox = new MyPromptBox;
			pPromptBox->setLabInfo("各输入栏都要有输入", PromptIcon);
			pPromptBox->exec();
		}

		// 1.2 非勾选 设置为静态IP
		QString strCommand("netsh interface ip set address ");

		// 1.3 执行CMD命令
		strCommand += QString("\"%1\" ").arg(humanReadableName);
		strCommand += QString("static %1 ").arg(m_pEditIP->text());
		strCommand += QString("%1 ").arg(m_pEditMask->text());
		strCommand += QString("%1").arg(m_pEditGway->text());
		QProcess cmd;
		cmd.start(strCommand);
		cmd.waitForStarted();
		cmd.waitForFinished();
		// cmd.readAllStandardError()这些信息只能输出一次，所以要赋值给临时QString
		// 有线连接和wifi网卡的IP不能设置为一样的，否则会提示："对象已存在"
		QString strCmdOut = QString::fromLocal8Bit(cmd.readAllStandardOutput());
		QString strError = QString::fromLocal8Bit(cmd.readAllStandardError());
		qDebug() << "设置为静态IP_strCmdOut: " << strCmdOut;
		qDebug() << "设置为静态IP_error: " << strError;
		// 判断cmd是否执行成功
		if (strCmdOut.contains("address"))
		{
			MyPromptBox *pPromptBox = new MyPromptBox;
			pPromptBox->setLabInfo("无效IP参数", PromptIcon);
			pPromptBox->exec();
		}
		else if (strCmdOut.contains("mask"))
		{
			MyPromptBox *pPromptBox = new MyPromptBox;
			pPromptBox->setLabInfo("无效mask参数", PromptIcon);
			pPromptBox->exec();
		}
		else if (strCmdOut.contains("gateway"))
		{
			MyPromptBox *pPromptBox = new MyPromptBox;
			pPromptBox->setLabInfo("无效gateway参数", PromptIcon);
			pPromptBox->exec();
		}
		else if (strCmdOut == "\r\n" && strError == "")
		{
			MyPromptBox *pPromptBox = new MyPromptBox;
			pPromptBox->setLabInfo("手动设置成功", SuccessIcon);
			pPromptBox->exec();

			this->accept();
			emit NetConfigSuc(); // 发射网络配置成功的信号
		}
		else if (strCmdOut.contains("对象已存在。"))
		{
			MyPromptBox *pPromptBox = new MyPromptBox;
			pPromptBox->setLabInfo("网络配置未改动", SuccessIcon);
			pPromptBox->exec();

			this->accept();
			emit NetConfigSuc(); // 发射网络配置成功的信号
		}
		else
		{
			MyPromptBox *pPromptBox = new MyPromptBox;
			pPromptBox->setLabInfo("手动设置失败", FailIcon);
			pPromptBox->exec();
		}
	}
}

// 设置返回按钮的文本
void NetConfig::SetBtnReturnText(const QString& strText)
{
	m_pBtnReturn->setText(strText);
}

// 检查DHCP服务是否开启
bool NetConfig::isDhcpEnabled(QString mac)
{
	mac.remove(":");
	// PIP_ADAPTER_INFO结构体指针存储本机网卡信息
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
	// 得到结构体大小,用于GetAdaptersInfo参数
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);
	// 调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量;其中stSize参数既是一个输入量也是一个输出量
	int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);

	// 记录每张网卡上的IP地址数量
	int IPnumPerNetCard = 0;
	if (ERROR_BUFFER_OVERFLOW == nRel)
	{
		// 如果函数返回的是ERROR_BUFFER_OVERFLOW
		// 则说明GetAdaptersInfo参数传递的内存空间不够,同时其传出stSize,表示需要的空间大小
		// 这也是说明为什么stSize既是一个输入量也是一个输出量
		// 释放原来的内存空间
		delete pIpAdapterInfo;
		// 重新申请内存空间用来存储所有网卡信息
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		// 再次调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量
		nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	}
	if (ERROR_SUCCESS == nRel)
	{
		QString macaddress;
		// 循环判断网卡 取出MAC地址对比是否是我们要找的网卡地址
		while (pIpAdapterInfo)
		{
			char tmpStr[MAX_ADAPTER_ADDRESS_LENGTH] = { 0 };
			QByteArray ba((char*)pIpAdapterInfo->Address, pIpAdapterInfo->AddressLength);
			macaddress = ba.toHex();
			mac.toUpper();
			macaddress.toUpper();
			if (macaddress.toUpper() == mac.toUpper())
			{
				// 检索到我们的网卡 检查DHCP是否有开启
				if (pIpAdapterInfo->DhcpEnabled)
					return true;
				else
					return false;
			}

			pIpAdapterInfo = pIpAdapterInfo->Next;
		}
	}
	// 释放内存空间
	if (pIpAdapterInfo)
	{
		delete pIpAdapterInfo;
	}

	return false;
}
