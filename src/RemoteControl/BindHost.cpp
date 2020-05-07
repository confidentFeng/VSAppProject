#include "BindHost.h"

BindHost::BindHost(QDialog *parent)
	: QDialog(parent)
{
	/* 绑定录播主机窗口-初始化 */
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

	/* 配置页面-初始化 */
	m_pWidgetCfgPage = new QWidget(this);
	m_pWidgetCfgPage->setObjectName("ConfigPage_WidgetCfgPage");

	/* 顶栏-初始化 */
	m_pLabTitle = new QLabel;
	m_pBtnClose = new QPushButton;
	m_pLabTitle->setObjectName("ConfigPage_LabTitle");
	m_pBtnClose->setObjectName("ConfigPage_BtnClose");
	m_pLabTitle->setText("绑定录播主机");
	m_pBtnClose->setFixedSize(42, 42);

	/* 中部窗口-初始化 */
	m_pLabIP = new QLabel;
	m_pEditIP = new QLineEdit;
	m_pLabPort = new QLabel;
	m_pEditPort = new QLineEdit;
	m_pLabAccount = new QLabel;
	m_pEditAccount = new QLineEdit;
	m_pLabPasswd = new QLabel;
	m_pEditPasswd = new QLineEdit;
	m_pLabIP->setObjectName("ConfigPage_LabIP");
	m_pEditIP->setObjectName("ConfigPage_EditIP");
	m_pLabPort->setObjectName("ConfigPage_LabPort");
	m_pEditPort->setObjectName("ConfigPage_EditPort");
	m_pLabAccount->setObjectName("ConfigPage_LabAccount");
	m_pEditAccount->setObjectName("ConfigPage_EditAccount");
	m_pLabPasswd->setObjectName("ConfigPage_LabPasswd");
	m_pEditPasswd->setObjectName("ConfigPage_EditPasswd");
	m_pLabIP->setText("录播主机IP");
	m_pLabPort->setText("录播主机端口号");
	m_pLabAccount->setText("录播主机账号");
	m_pLabPasswd->setText("录播主机密码");
	m_pEditIP->setFixedSize(400, 48);
	m_pEditPort->setFixedSize(400, 48);
	m_pEditAccount->setFixedSize(400, 48);
	m_pEditPasswd->setFixedSize(400, 48);
	m_pEditIP->setValidator(new QRegExpValidator(QRegExp(REGEXP_IP)));
	m_pEditPort->setValidator(new QRegExpValidator(QRegExp(REGEXP_PORT)));
	m_pEditAccount->setValidator(new QRegExpValidator(QRegExp(REGEXP_ACCOUNT)));
	m_pEditPasswd->setValidator(new QRegExpValidator(QRegExp(REGEXP_PASSWD)));
	m_pEditPasswd->setEchoMode(QLineEdit::Password);

	/* 底栏-初始化 */
	m_pBtnReturn = new QPushButton;
	m_pBtnCfgSave = new QPushButton;
	m_pBtnUse = new QPushButton;
	m_pBtnReturn->setObjectName("ConfigPage_BtnReturn");
	m_pBtnCfgSave->setObjectName("ConfigPage_BtnCfgSave");
	m_pBtnUse->setObjectName("ConfigPage_BtnUse");
	m_pBtnCfgSave->setText("保存");
	m_pBtnUse->setText("使用说明");
	m_pBtnReturn->setFixedSize(136, 48);
	m_pBtnCfgSave->setFixedSize(136, 48);

	/* 顶栏-水平布局 */
	QHBoxLayout *pHLayoutTop = new QHBoxLayout;
	pHLayoutTop->addWidget(m_pLabTitle);
	pHLayoutTop->addStretch();
	pHLayoutTop->addWidget(m_pBtnClose);

	/* 中部窗口-网格布局 */
	QGridLayout *pGLayoutCenter = new QGridLayout;
	pGLayoutCenter->addWidget(m_pLabIP, 0, 0, Qt::AlignRight);
	pGLayoutCenter->addWidget(m_pEditIP, 0, 1);
	pGLayoutCenter->addWidget(m_pLabPort, 1, 0, Qt::AlignRight);
	pGLayoutCenter->addWidget(m_pEditPort, 1, 1);
	pGLayoutCenter->addWidget(m_pLabAccount, 2, 0, Qt::AlignRight);
	pGLayoutCenter->addWidget(m_pEditAccount, 2, 1);
	pGLayoutCenter->addWidget(m_pLabPasswd, 3, 0, Qt::AlignRight);
	pGLayoutCenter->addWidget(m_pEditPasswd, 3, 1);
	pGLayoutCenter->setContentsMargins(66, 58, 140, 40);
	pGLayoutCenter->setSpacing(20);

	/* 底栏-水平布局 */
	QHBoxLayout *pHLayoutBottom = new QHBoxLayout;
	pHLayoutBottom->addStretch(3);
	pHLayoutBottom->addWidget(m_pBtnReturn);
	pHLayoutBottom->addSpacing(30);
	pHLayoutBottom->addWidget(m_pBtnCfgSave);
	pHLayoutBottom->addSpacing(30);
	pHLayoutBottom->addWidget(m_pBtnUse, 0, Qt::AlignBottom);
	pHLayoutBottom->addStretch(1);

	/* 主布局 */
	QVBoxLayout *pVLayoutMain = new QVBoxLayout(m_pWidgetCfgPage);
	pVLayoutMain->addSpacing(5);
	pVLayoutMain->addLayout(pHLayoutTop);
	pVLayoutMain->addStretch();
	pVLayoutMain->addLayout(pGLayoutCenter);
	pVLayoutMain->addStretch();
	pVLayoutMain->addLayout(pHLayoutBottom);
	pVLayoutMain->addSpacing(30);

	// 解决按回车键窗口退出的问题，因为按钮默认设置成了StrongFocus
	m_pBtnClose->setFocusPolicy(Qt::NoFocus);
	m_pBtnReturn->setFocusPolicy(Qt::NoFocus);

	// 初始化http定时器
	m_pHttpTimer = new QTimer;
	m_pHttpTimer->setInterval(BINDHOST_OUTTIME); // 时间太短，有可能来不及接收到http返回消息
	connect(m_pHttpTimer, SIGNAL(timeout()), this, SLOT(timeoutSlot()));

	// 连接槽函数
	connect(m_pBtnClose, SIGNAL(clicked()), this, SLOT(CloseSlot()));
	connect(m_pBtnReturn, SIGNAL(clicked()), this, SLOT(ReturnSlot()));
	connect(m_pBtnCfgSave, SIGNAL(clicked()), this, SLOT(SaveSlot()));
	connect(m_pBtnUse, SIGNAL(clicked()), this, SLOT(UseSlot()));
}

BindHost::~BindHost()
{

}

// 键盘按下事件：解决按Esc键窗口退出的问题
void BindHost::keyPressEvent(QKeyEvent *event)
{
	// 什么都不用做
}

// 是否显示关闭按钮
void BindHost::IsFirstOpen(bool isFirstFlag)
{
	if (isFirstFlag)
	{
		this->setFixedSize(WIN_WIDTH, WIN_HEIGHT);
		m_pWidgetCfgPage->setGeometry((WIN_WIDTH-700)/2, (WIN_HEIGHT-516)/2, 700, 516);

		m_pBtnClose->hide();
		m_pBtnReturn->setText("返回");
	}
	else
	{
		this->setFixedSize(700, 516);
		m_pWidgetCfgPage->setGeometry(0, 0, 700, 516);

		m_pBtnReturn->setText("取消");
	}
}

// 关闭槽函数
void BindHost::CloseSlot()
{
	this->close();
	delete this;
}

// 返回槽函数
void BindHost::ReturnSlot()
{
	// 按下录播主机配置按钮的情况下，需要关闭本窗口
	this->close();

	emit BtnReturnClicked(); // 返回按钮的点击信号
}

// 配置保存槽函数
void BindHost::SaveSlot()
{
	// 判断各输入栏是否有输入
	if (m_pEditIP->text().isEmpty() || m_pEditPort->text().isEmpty() || m_pEditAccount->text().isEmpty() \
		|| m_pEditPasswd->text().isEmpty())
	{
		MyPromptBox *pPromptBox = new MyPromptBox;
		pPromptBox->setLabInfo("各输入栏都要有输入", PromptIcon);
		pPromptBox->exec();
		return;
	}

#if 1
	// http发送“登录请求”(与主线程异步执行，所以会在定时器超时函数中进行判断)
	HttpClient(QString("http://%1/ROCPOW.cgi?type=1&account=%2&password=%3").arg(m_pEditIP->text())\
		.arg(m_pEditAccount->text()).arg(m_pEditPasswd->text())).success([&](const QString &response) {
		strReturn = response;	
	}).fail([](const QString &error, int errorCode) {
		qDebug().noquote() << "error: " << error << errorCode << endl;
	}).get();

	m_pHttpTimer->start();
#endif
}

// 定时器超时槽函数
void BindHost::timeoutSlot()
{
	m_pHttpTimer->stop();

	// 会比http发送先执行，想想如何解决：
	if (strReturn.contains("\"result\":0")) //"result":0
	{
		MyPromptBox *pPromptBox = new MyPromptBox;
		pPromptBox->setLabInfo("绑定录播主机成功", SuccessIcon);
		pPromptBox->exec();

		// 绑定录播主机成功，才写INN文件
		QString iniFilePath = QApplication::applicationDirPath() + "/config.ini";
		QSettings *IniWrite = new QSettings(iniFilePath, QSettings::IniFormat);
		IniWrite->setValue("hostIP", m_pEditIP->text());
		IniWrite->setValue("hostPort", m_pEditPort->text().toInt());
		IniWrite->setValue("hostAccount", m_pEditAccount->text());
		IniWrite->setValue("hostPasswd", m_pEditPasswd->text());
		delete IniWrite;

		// 按下录播主机配置按钮的情况下，需要关闭本窗口
		this->accept();
		// 发射保存按钮的点击信号
		emit BtnSaveClicked();
	}
	else
	{
		MyPromptBox *pPromptBox = new MyPromptBox;
		pPromptBox->setLabInfo("绑定录播主机失败", SuccessIcon);
		pPromptBox->exec();
	}
}

// 使用说明槽函数
void BindHost::UseSlot()
{
	MyMessageBox *pMyMessageBox = new MyMessageBox(this);
	pMyMessageBox->setGeometry((WIN_WIDTH - 700) / 2 - 10, (WIN_HEIGHT - 516) / 2 - 40, 700, 516);
	pMyMessageBox->SetTitleText("使用说明");
	pMyMessageBox->ShowControl(false, false);
	pMyMessageBox->SetInfoText("      远程录播控制面板软件需要绑定录播主机后才能对主机进\n\
行控制,请填写录播主机的IP地址、端口等相关信息，并从管\n理员处获取登录账号及密码。\n\
      此外，此远程控制软件需与录播主机在同一网络环境下方\n可进行绑定。");
	pMyMessageBox->exec();
}

// 设置录播主机IP
void BindHost::SetHostIP(QString hostIP)
{
	m_pEditIP->setText(hostIP);
}

// 设置录播主机端口号
void BindHost::SetHostPort(int hostPort)
{
	m_pEditPort->setText(QString::number(hostPort));
}

// 设置录播主机账号
void BindHost::SetHostAccount(QString hostAccount)
{
	m_pEditAccount->setText(hostAccount);
}

// 设置录播主机密码
void BindHost::SetHostPasswd(QString hostPasswd)
{
	m_pEditPasswd->setText(hostPasswd);
}

// 获得录播主机IP
QString BindHost::GetHostIP()
{
	return m_pEditIP->text();
}

// 获得录播主机端口号
int BindHost::GetHostPort()
{
	return m_pEditPort->text().toInt();
}

// 获得录播主机账号
QString BindHost::GetHostAccount()
{
	return m_pEditAccount->text();
}

// 获得录播主机密码
QString BindHost::GetHostPasswd()
{
	return m_pEditPasswd->text();
}
