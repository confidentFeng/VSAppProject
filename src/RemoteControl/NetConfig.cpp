#include "NetConfig.h"

NetConfig::NetConfig(QDialog *parent, const bool& bIsWifi)
	: QDialog(parent)
{
	/* �������ý���-��ʼ�� */
	this->setFixedSize(700, 516);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

	/* �ӽ���-��ʼ�� */
	m_pWidgetChild = new QWidget(this);
	m_pWidgetChild->setGeometry(0, 0, 700, 516);
	m_pWidgetChild->setObjectName("NetConfig_WidgetChild");

	/* ���ڲ���-��ʼ�� */
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
		m_pLabTitle->setText("IP����-����");
	else
		m_pLabTitle->setText("IP����-����");
	m_pLabAuto->setText("�Զ���ȡIP��ַ");
	m_pLabManual->setText("ʹ�������IP��ַ");
	m_pLabIP->setText("IP��ַ");
	m_pLabMask->setText("��������");
	m_pLabGway->setText("Ĭ������");
	m_pBtnReturn->setText("����");
	m_pBtnNext->setText("ȷ��");
	m_pEditIP->setFixedSize(400, 48);
	m_pBtnClose->setFixedSize(42, 42);
	m_pEditMask->setFixedSize(400, 48);
	m_pEditGway->setFixedSize(400, 48);
	m_pBtnReturn->setFixedSize(160, 56);
	m_pBtnNext->setFixedSize(160, 56);
	m_pEditIP->setValidator(new QRegExpValidator(QRegExp(REGEXP_IP)));
	m_pEditMask->setValidator(new QRegExpValidator(QRegExp(REGEXP_IP)));
	m_pEditGway->setValidator(new QRegExpValidator(QRegExp(REGEXP_IP)));

	/* ������-ˮƽ���� */
	QHBoxLayout *pHLayoutTitle = new QHBoxLayout;
	pHLayoutTitle->addSpacing(10);
	pHLayoutTitle->addWidget(m_pLabTitle);
	pHLayoutTitle->addStretch(1);
	pHLayoutTitle->addWidget(m_pBtnClose);
	pHLayoutTitle->addSpacing(10);

	/* ��ѡ�����-ˮƽ���� */
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

	/* �ı������-���񲼾� */
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

	/* ��ť���-ˮƽ���� */
	QHBoxLayout *pHLayoutBtn = new QHBoxLayout;
	pHLayoutBtn->addStretch(1);
	pHLayoutBtn->addWidget(m_pBtnReturn);
	pHLayoutBtn->addSpacing(40);
	pHLayoutBtn->addWidget(m_pBtnNext);
	pHLayoutBtn->addStretch(1);

	/* ������-��ֱ���� */
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

	// �رհ�ť-����ۺ���
	QObject::connect(m_pBtnClose, &QPushButton::clicked, [=]() {
		this->reject();
		emit StackedWidgetClose();
	});

	// �Զ���ȡIP��ѡ��ť-����ۺ���
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
	// Ĭ��Ϊ�Զ����ӣ������ı������
	m_pRadioAuto->setChecked(true);
	emit m_pRadioAuto->clicked();

	// �ֶ���ȡIP��ѡ��ť-����ۺ���
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

	// ���ذ�ť-����ۺ���
	QObject::connect(m_pBtnReturn, &QPushButton::clicked, [=]() {
		this->close();
		emit BtnReturnClicked();
	});

	// ���Ӳۺ���
	connect(m_pBtnNext, SIGNAL(clicked()), this, SLOT(NextSlot()));
}

NetConfig::~NetConfig()
{

}

void NetConfig::showEvent(QShowEvent * event)
{
	// 1. ��ȡ��̫��������wifi������MAC��ַ
	QString Mac;
	QList<QNetworkInterface> iface = QNetworkInterface::allInterfaces();
	for (int i = 0; i < iface.size(); i++)
	{		
		QNetworkInterface var = iface.at(i);
		//qDebug() << "var.humanReadableName(): " << var.humanReadableName();

		if (!m_bIsWifi)
		{
			if (var.humanReadableName() == "��̫��")
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

	// 2. �ж��Ǿ�̬IP ���Ƕ�̬IP
	if (isDhcpEnabled(Mac))
	{
		// 2.2 ��̬IP
		m_pRadioAuto->setChecked(true);
		m_pRadioManual->setChecked(false);
		qDebug() << "��̬IP";
	}
	else
	{
		// 2.1 ��̬IP
		m_pRadioAuto->setChecked(false);
		m_pRadioManual->setChecked(true);
		emit m_pRadioManual->clicked();
		qDebug() << "��̬IP";
	}
}

// ��һ���ۺ���
void NetConfig::NextSlot()
{
	// 1.�ж� �Զ���ȡIP��ť ״̬
	if (!m_isManualFlag)
	{
		// 1.1 ��ѡ ��������ΪDHCP
		QProcess cmd;
		cmd.start(QString("netsh interface ip set address \"%1\" dhcp").arg(humanReadableName));
		cmd.waitForStarted();
		cmd.waitForFinished();
		QString strCmdOut = QString::fromLocal8Bit(cmd.readAllStandardOutput());
		qDebug() << "m_bIsWifi: " << m_bIsWifi <<" netCard: " << humanReadableName;
		qDebug() << "strCmdOut: " << strCmdOut;
		// ��ʱ��ִ�������ȴ�ʱ��̫�̣�������wifi��û���ü���������ʹ�ã���᷵��"\r\n"
		// ��ʵ���Ѿ��ɹ�����DHCP��������������wifi��������������DHCP��
		if (strCmdOut.contains("���ڴ˽ӿ������� DHCP��") || strCmdOut == "\r\n")
		{
			MyPromptBox *pPromptBox = new MyPromptBox;
			pPromptBox->setLabInfo("�Զ���ȡIP�ɹ�", SuccessIcon);
			pPromptBox->exec();

			this->accept();
			emit NetConfigSuc(); // �����������óɹ����ź�
		}
		else
		{
			MyPromptBox *pPromptBox = new MyPromptBox;
			pPromptBox->setLabInfo("�Զ���ȡIPʧ��", FailIcon);
			pPromptBox->exec();

			this->reject();
			emit NetConfigSuc(); // �����������óɹ����ź�(��Ȼ�Զ���ȡʧ����)
		}
	}
	else
	{
		// Ҫ����ı���Ҫ������
		if (m_pEditIP->text() == "" || m_pEditMask->text() == "" || m_pEditGway->text() == "")
		{
			MyPromptBox *pPromptBox = new MyPromptBox;
			pPromptBox->setLabInfo("����������Ҫ������", PromptIcon);
			pPromptBox->exec();
		}

		// 1.2 �ǹ�ѡ ����Ϊ��̬IP
		QString strCommand("netsh interface ip set address ");

		// 1.3 ִ��CMD����
		strCommand += QString("\"%1\" ").arg(humanReadableName);
		strCommand += QString("static %1 ").arg(m_pEditIP->text());
		strCommand += QString("%1 ").arg(m_pEditMask->text());
		strCommand += QString("%1").arg(m_pEditGway->text());
		QProcess cmd;
		cmd.start(strCommand);
		cmd.waitForStarted();
		cmd.waitForFinished();
		// cmd.readAllStandardError()��Щ��Ϣֻ�����һ�Σ�����Ҫ��ֵ����ʱQString
		// �������Ӻ�wifi������IP��������Ϊһ���ģ��������ʾ��"�����Ѵ���"
		QString strCmdOut = QString::fromLocal8Bit(cmd.readAllStandardOutput());
		QString strError = QString::fromLocal8Bit(cmd.readAllStandardError());
		qDebug() << "����Ϊ��̬IP_strCmdOut: " << strCmdOut;
		qDebug() << "����Ϊ��̬IP_error: " << strError;
		// �ж�cmd�Ƿ�ִ�гɹ�
		if (strCmdOut.contains("address"))
		{
			MyPromptBox *pPromptBox = new MyPromptBox;
			pPromptBox->setLabInfo("��ЧIP����", PromptIcon);
			pPromptBox->exec();
		}
		else if (strCmdOut.contains("mask"))
		{
			MyPromptBox *pPromptBox = new MyPromptBox;
			pPromptBox->setLabInfo("��Чmask����", PromptIcon);
			pPromptBox->exec();
		}
		else if (strCmdOut.contains("gateway"))
		{
			MyPromptBox *pPromptBox = new MyPromptBox;
			pPromptBox->setLabInfo("��Чgateway����", PromptIcon);
			pPromptBox->exec();
		}
		else if (strCmdOut == "\r\n" && strError == "")
		{
			MyPromptBox *pPromptBox = new MyPromptBox;
			pPromptBox->setLabInfo("�ֶ����óɹ�", SuccessIcon);
			pPromptBox->exec();

			this->accept();
			emit NetConfigSuc(); // �����������óɹ����ź�
		}
		else if (strCmdOut.contains("�����Ѵ��ڡ�"))
		{
			MyPromptBox *pPromptBox = new MyPromptBox;
			pPromptBox->setLabInfo("��������δ�Ķ�", SuccessIcon);
			pPromptBox->exec();

			this->accept();
			emit NetConfigSuc(); // �����������óɹ����ź�
		}
		else
		{
			MyPromptBox *pPromptBox = new MyPromptBox;
			pPromptBox->setLabInfo("�ֶ�����ʧ��", FailIcon);
			pPromptBox->exec();
		}
	}
}

// ���÷��ذ�ť���ı�
void NetConfig::SetBtnReturnText(const QString& strText)
{
	m_pBtnReturn->setText(strText);
}

// ���DHCP�����Ƿ���
bool NetConfig::isDhcpEnabled(QString mac)
{
	mac.remove(":");
	// PIP_ADAPTER_INFO�ṹ��ָ��洢����������Ϣ
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
	// �õ��ṹ���С,����GetAdaptersInfo����
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);
	// ����GetAdaptersInfo����,���pIpAdapterInfoָ�����;����stSize��������һ��������Ҳ��һ�������
	int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);

	// ��¼ÿ�������ϵ�IP��ַ����
	int IPnumPerNetCard = 0;
	if (ERROR_BUFFER_OVERFLOW == nRel)
	{
		// ����������ص���ERROR_BUFFER_OVERFLOW
		// ��˵��GetAdaptersInfo�������ݵ��ڴ�ռ䲻��,ͬʱ�䴫��stSize,��ʾ��Ҫ�Ŀռ��С
		// ��Ҳ��˵��ΪʲôstSize����һ��������Ҳ��һ�������
		// �ͷ�ԭ�����ڴ�ռ�
		delete pIpAdapterInfo;
		// ���������ڴ�ռ������洢����������Ϣ
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		// �ٴε���GetAdaptersInfo����,���pIpAdapterInfoָ�����
		nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	}
	if (ERROR_SUCCESS == nRel)
	{
		QString macaddress;
		// ѭ���ж����� ȡ��MAC��ַ�Ա��Ƿ�������Ҫ�ҵ�������ַ
		while (pIpAdapterInfo)
		{
			char tmpStr[MAX_ADAPTER_ADDRESS_LENGTH] = { 0 };
			QByteArray ba((char*)pIpAdapterInfo->Address, pIpAdapterInfo->AddressLength);
			macaddress = ba.toHex();
			mac.toUpper();
			macaddress.toUpper();
			if (macaddress.toUpper() == mac.toUpper())
			{
				// ���������ǵ����� ���DHCP�Ƿ��п���
				if (pIpAdapterInfo->DhcpEnabled)
					return true;
				else
					return false;
			}

			pIpAdapterInfo = pIpAdapterInfo->Next;
		}
	}
	// �ͷ��ڴ�ռ�
	if (pIpAdapterInfo)
	{
		delete pIpAdapterInfo;
	}

	return false;
}
