#include "BindHost.h"

BindHost::BindHost(QDialog *parent)
	: QDialog(parent)
{
	/* ��¼����������-��ʼ�� */
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

	/* ����ҳ��-��ʼ�� */
	m_pWidgetCfgPage = new QWidget(this);
	m_pWidgetCfgPage->setObjectName("ConfigPage_WidgetCfgPage");

	/* ����-��ʼ�� */
	m_pLabTitle = new QLabel;
	m_pBtnClose = new QPushButton;
	m_pLabTitle->setObjectName("ConfigPage_LabTitle");
	m_pBtnClose->setObjectName("ConfigPage_BtnClose");
	m_pLabTitle->setText("��¼������");
	m_pBtnClose->setFixedSize(42, 42);

	/* �в�����-��ʼ�� */
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
	m_pLabIP->setText("¼������IP");
	m_pLabPort->setText("¼�������˿ں�");
	m_pLabAccount->setText("¼�������˺�");
	m_pLabPasswd->setText("¼����������");
	m_pEditIP->setFixedSize(400, 48);
	m_pEditPort->setFixedSize(400, 48);
	m_pEditAccount->setFixedSize(400, 48);
	m_pEditPasswd->setFixedSize(400, 48);
	m_pEditIP->setValidator(new QRegExpValidator(QRegExp(REGEXP_IP)));
	m_pEditPort->setValidator(new QRegExpValidator(QRegExp(REGEXP_PORT)));
	m_pEditAccount->setValidator(new QRegExpValidator(QRegExp(REGEXP_ACCOUNT)));
	m_pEditPasswd->setValidator(new QRegExpValidator(QRegExp(REGEXP_PASSWD)));
	m_pEditPasswd->setEchoMode(QLineEdit::Password);

	/* ����-��ʼ�� */
	m_pBtnReturn = new QPushButton;
	m_pBtnCfgSave = new QPushButton;
	m_pBtnUse = new QPushButton;
	m_pBtnReturn->setObjectName("ConfigPage_BtnReturn");
	m_pBtnCfgSave->setObjectName("ConfigPage_BtnCfgSave");
	m_pBtnUse->setObjectName("ConfigPage_BtnUse");
	m_pBtnCfgSave->setText("����");
	m_pBtnUse->setText("ʹ��˵��");
	m_pBtnReturn->setFixedSize(136, 48);
	m_pBtnCfgSave->setFixedSize(136, 48);

	/* ����-ˮƽ���� */
	QHBoxLayout *pHLayoutTop = new QHBoxLayout;
	pHLayoutTop->addWidget(m_pLabTitle);
	pHLayoutTop->addStretch();
	pHLayoutTop->addWidget(m_pBtnClose);

	/* �в�����-���񲼾� */
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

	/* ����-ˮƽ���� */
	QHBoxLayout *pHLayoutBottom = new QHBoxLayout;
	pHLayoutBottom->addStretch(3);
	pHLayoutBottom->addWidget(m_pBtnReturn);
	pHLayoutBottom->addSpacing(30);
	pHLayoutBottom->addWidget(m_pBtnCfgSave);
	pHLayoutBottom->addSpacing(30);
	pHLayoutBottom->addWidget(m_pBtnUse, 0, Qt::AlignBottom);
	pHLayoutBottom->addStretch(1);

	/* ������ */
	QVBoxLayout *pVLayoutMain = new QVBoxLayout(m_pWidgetCfgPage);
	pVLayoutMain->addSpacing(5);
	pVLayoutMain->addLayout(pHLayoutTop);
	pVLayoutMain->addStretch();
	pVLayoutMain->addLayout(pGLayoutCenter);
	pVLayoutMain->addStretch();
	pVLayoutMain->addLayout(pHLayoutBottom);
	pVLayoutMain->addSpacing(30);

	// ������س��������˳������⣬��Ϊ��ťĬ�����ó���StrongFocus
	m_pBtnClose->setFocusPolicy(Qt::NoFocus);
	m_pBtnReturn->setFocusPolicy(Qt::NoFocus);

	// ��ʼ��http��ʱ��
	m_pHttpTimer = new QTimer;
	m_pHttpTimer->setInterval(BINDHOST_OUTTIME); // ʱ��̫�̣��п������������յ�http������Ϣ
	connect(m_pHttpTimer, SIGNAL(timeout()), this, SLOT(timeoutSlot()));

	// ���Ӳۺ���
	connect(m_pBtnClose, SIGNAL(clicked()), this, SLOT(CloseSlot()));
	connect(m_pBtnReturn, SIGNAL(clicked()), this, SLOT(ReturnSlot()));
	connect(m_pBtnCfgSave, SIGNAL(clicked()), this, SLOT(SaveSlot()));
	connect(m_pBtnUse, SIGNAL(clicked()), this, SLOT(UseSlot()));
}

BindHost::~BindHost()
{

}

// ���̰����¼��������Esc�������˳�������
void BindHost::keyPressEvent(QKeyEvent *event)
{
	// ʲô��������
}

// �Ƿ���ʾ�رհ�ť
void BindHost::IsFirstOpen(bool isFirstFlag)
{
	if (isFirstFlag)
	{
		this->setFixedSize(WIN_WIDTH, WIN_HEIGHT);
		m_pWidgetCfgPage->setGeometry((WIN_WIDTH-700)/2, (WIN_HEIGHT-516)/2, 700, 516);

		m_pBtnClose->hide();
		m_pBtnReturn->setText("����");
	}
	else
	{
		this->setFixedSize(700, 516);
		m_pWidgetCfgPage->setGeometry(0, 0, 700, 516);

		m_pBtnReturn->setText("ȡ��");
	}
}

// �رղۺ���
void BindHost::CloseSlot()
{
	this->close();
	delete this;
}

// ���زۺ���
void BindHost::ReturnSlot()
{
	// ����¼���������ð�ť������£���Ҫ�رձ�����
	this->close();

	emit BtnReturnClicked(); // ���ذ�ť�ĵ���ź�
}

// ���ñ���ۺ���
void BindHost::SaveSlot()
{
	// �жϸ��������Ƿ�������
	if (m_pEditIP->text().isEmpty() || m_pEditPort->text().isEmpty() || m_pEditAccount->text().isEmpty() \
		|| m_pEditPasswd->text().isEmpty())
	{
		MyPromptBox *pPromptBox = new MyPromptBox;
		pPromptBox->setLabInfo("����������Ҫ������", PromptIcon);
		pPromptBox->exec();
		return;
	}

#if 1
	// http���͡���¼����(�����߳��첽ִ�У����Ի��ڶ�ʱ����ʱ�����н����ж�)
	HttpClient(QString("http://%1/ROCPOW.cgi?type=1&account=%2&password=%3").arg(m_pEditIP->text())\
		.arg(m_pEditAccount->text()).arg(m_pEditPasswd->text())).success([&](const QString &response) {
		strReturn = response;	
	}).fail([](const QString &error, int errorCode) {
		qDebug().noquote() << "error: " << error << errorCode << endl;
	}).get();

	m_pHttpTimer->start();
#endif
}

// ��ʱ����ʱ�ۺ���
void BindHost::timeoutSlot()
{
	m_pHttpTimer->stop();

	// ���http������ִ�У�������ν����
	if (strReturn.contains("\"result\":0")) //"result":0
	{
		MyPromptBox *pPromptBox = new MyPromptBox;
		pPromptBox->setLabInfo("��¼�������ɹ�", SuccessIcon);
		pPromptBox->exec();

		// ��¼�������ɹ�����дINN�ļ�
		QString iniFilePath = QApplication::applicationDirPath() + "/config.ini";
		QSettings *IniWrite = new QSettings(iniFilePath, QSettings::IniFormat);
		IniWrite->setValue("hostIP", m_pEditIP->text());
		IniWrite->setValue("hostPort", m_pEditPort->text().toInt());
		IniWrite->setValue("hostAccount", m_pEditAccount->text());
		IniWrite->setValue("hostPasswd", m_pEditPasswd->text());
		delete IniWrite;

		// ����¼���������ð�ť������£���Ҫ�رձ�����
		this->accept();
		// ���䱣�水ť�ĵ���ź�
		emit BtnSaveClicked();
	}
	else
	{
		MyPromptBox *pPromptBox = new MyPromptBox;
		pPromptBox->setLabInfo("��¼������ʧ��", SuccessIcon);
		pPromptBox->exec();
	}
}

// ʹ��˵���ۺ���
void BindHost::UseSlot()
{
	MyMessageBox *pMyMessageBox = new MyMessageBox(this);
	pMyMessageBox->setGeometry((WIN_WIDTH - 700) / 2 - 10, (WIN_HEIGHT - 516) / 2 - 40, 700, 516);
	pMyMessageBox->SetTitleText("ʹ��˵��");
	pMyMessageBox->ShowControl(false, false);
	pMyMessageBox->SetInfoText("      Զ��¼��������������Ҫ��¼����������ܶ�������\n\
�п���,����д¼��������IP��ַ���˿ڵ������Ϣ�����ӹ�\n��Ա����ȡ��¼�˺ż����롣\n\
      ���⣬��Զ�̿����������¼��������ͬһ���绷���·�\n�ɽ��а󶨡�");
	pMyMessageBox->exec();
}

// ����¼������IP
void BindHost::SetHostIP(QString hostIP)
{
	m_pEditIP->setText(hostIP);
}

// ����¼�������˿ں�
void BindHost::SetHostPort(int hostPort)
{
	m_pEditPort->setText(QString::number(hostPort));
}

// ����¼�������˺�
void BindHost::SetHostAccount(QString hostAccount)
{
	m_pEditAccount->setText(hostAccount);
}

// ����¼����������
void BindHost::SetHostPasswd(QString hostPasswd)
{
	m_pEditPasswd->setText(hostPasswd);
}

// ���¼������IP
QString BindHost::GetHostIP()
{
	return m_pEditIP->text();
}

// ���¼�������˿ں�
int BindHost::GetHostPort()
{
	return m_pEditPort->text().toInt();
}

// ���¼�������˺�
QString BindHost::GetHostAccount()
{
	return m_pEditAccount->text();
}

// ���¼����������
QString BindHost::GetHostPasswd()
{
	return m_pEditPasswd->text();
}
