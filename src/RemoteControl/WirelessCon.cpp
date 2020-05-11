#include "WirelessCon.h"

WirelessCon::WirelessCon(QDialog *parent)
	: QDialog(parent)
{
	/* �������Ӵ���-��ʼ�� */
	this->setFixedSize(700, 516);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

	/* �ӽ���-��ʼ�� */
	m_pWidgetChild = new QWidget(this);
	m_pWidgetChild->setGeometry(0, 0, 700, 516);
	m_pWidgetChild->setObjectName("WirelessCon_WidgetChild");

	/* ��Ա����-��ʼ��*/
	m_lastItem = new QListWidgetItem;
	m_conIndex = -1;

	/* wifi�б�-��ʼ��*/
	pListWidgetWifi = new QListWidget;
	pListWidgetWifi->setFixedSize(700, 70*6);
	pListWidgetWifi->setFrameShape(QListWidget::NoFrame);
	// ����ƽ��
	pListWidgetWifi->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	pListWidgetWifi->setVerticalScrollMode(QListWidget::ScrollPerPixel);
	pListWidgetWifi->setFocusPolicy(Qt::NoFocus); // ����Ϊ�޽��㣬��currentRow��ʼ��Ĭ��Ϊ0
	connect(pListWidgetWifi, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(clickedWifiItem(QListWidgetItem*)));
	// ����������
	//pListWidgetWifi->setStyleSheet("QScrollBar{width:40px;}");
	QFile qssFile(QApplication::applicationDirPath() + "/image/myStyleSheet.qss");
	qssFile.open(QFile::ReadOnly);
	pListWidgetWifi->setStyleSheet(qssFile.readAll());

	// 1. ���ҳ�������wifi������
	QString strCmdCon = Common::Get()->ExecuteCmd("netsh wlan show interface");
	QStringList strListCon = strCmdCon.split("\r\n");
	QString strConWifiName = "null"; // �����б���������Ϊ""��wifi
	if (strListCon.size() > 15) // ������wifi�Ļ��������������24�У�����ֻ��14��
	{
		QStringList strListWifiName = strListCon[19].split(": ");
		strConWifiName = strListWifiName[1].remove(" ");
	}

	// 2. ��ȡ������wifi�����ƣ�����������wifiһ��"��"
	int index = 0;
	QString strCmdOut = Common::Get()->ExecuteCmd("netsh wlan show networks");
	QStringList strListOut = strCmdOut.split("\r\n");
	for (int i = 0; i < strListOut.size(); i++)
	{
		if (strListOut[i].contains("SSID"))
		{
			QStringList strListWifi = strListOut[i].split(" : ");

			// ȥ������Ϊ""��wifi
			if (strListWifi[1] == "")
				continue;
			// ȥ���������루ʵ�������ģ���wifi
			if (strListWifi[1].contains(QRegExp("[\\x4e00-\\x9fa5]+")))
				continue;
			// ȥ�����ȹ�����wifi
			if (strListWifi[1].length() > 24)
				continue;

			// QListWidget�����Զ����б���WifiOptionWidget
			WifiItemWidget *pWifiOptionWidget = new WifiItemWidget;
			pWifiOptionWidget->SetWifiName(strListWifi[1]);
			if (strListWifi[1] == strConWifiName)
			{
				pWifiOptionWidget->SetConStatus(true);
				// ���������wifi������
				m_conIndex = index;
			}
			QListWidgetItem *item = new QListWidgetItem(pListWidgetWifi);
			pListWidgetWifi->setItemWidget(item, pWifiOptionWidget);
			item->setSizeHint(QSize(0, 70));
			pListWidgetWifi->addItem(item);

			// ��wifi������ӵ�m_strListWifi
			m_strListWifi.append(strListWifi[1]);

			index++;
		}
	}

	/* ���ڲ���-��ʼ�� */
	m_pLabTitle = new QLabel;
	m_pBtnClose = new QPushButton;
	m_pBtnWired = new QPushButton;
	m_pLabTitle->setObjectName("WirelessCon_LabTitle");
	m_pBtnClose->setObjectName("WirelessCon_BtnClose");
	m_pBtnWired->setObjectName("WirelessCon_BtnWired");
	m_pLabTitle->setText("��������");
	m_pBtnWired->setText("��������");
	m_pBtnClose->setFixedSize(42, 42);

	/* ������-ˮƽ���� */
	QHBoxLayout *pHLayoutTitle = new QHBoxLayout;
	pHLayoutTitle->addSpacing(10);
	pHLayoutTitle->addWidget(m_pLabTitle);
	pHLayoutTitle->addStretch(1);
	pHLayoutTitle->addWidget(m_pBtnClose);
	pHLayoutTitle->addSpacing(10);

	/* �������Ӱ�ť-ˮƽ���� */
	QHBoxLayout *pHLayoutWired = new QHBoxLayout;
	pHLayoutWired->addSpacing(70);
	pHLayoutWired->addWidget(m_pBtnWired);
	pHLayoutWired->addStretch(1);

	/* ������-��ֱ���� */
	QVBoxLayout *pVLayoutMain = new QVBoxLayout(m_pWidgetChild);
	pVLayoutMain->addSpacing(10);
	pVLayoutMain->addLayout(pHLayoutTitle);
	pVLayoutMain->addSpacing(10);
	pVLayoutMain->addWidget(pListWidgetWifi);
	pVLayoutMain->addStretch(1);
	pVLayoutMain->addLayout(pHLayoutWired);
	pVLayoutMain->addSpacing(10);
	pVLayoutMain->setContentsMargins(0, 0, 0, 0);

	// �رհ�ť-����ۺ���
	QObject::connect(m_pBtnClose, &QPushButton::clicked, [=]() {
		emit StackedWidgetClose();
	});

	// �������Ӱ�ť-����ۺ���
	QObject::connect(m_pBtnWired, &QPushButton::clicked, [=]() {
		// ��������Ƿ����
		if(IsCableAccess() == true)
		{
			// �رոý��棬�����������ý���-��������
			//this->reject();
			emit BtnNextWired();
		}
	});
}

WirelessCon::~WirelessCon()
{
	
}

// ��������Ƿ����
bool WirelessCon::IsCableAccess()
{
	QString strCmdOut = Common::Get()->ExecuteCmd("netsh interface ipv4 show ipaddress interface=��̫��");
	// ע�⣬���str�ǿ��ַ�����list1������һ�����ַ������б����size=1
	QStringList strCmdOutList = strCmdOut.split("\r\n"); 
	for (int i = 0; i<strCmdOutList.size(); i++)
	{
		if (strCmdOutList[i] == "DAD ״̬           : ��ѡ��")
			return true;
	}

	return false;
}

// WifiItemWidget����¼�-��Ӧ����
void WirelessCon::clickedWifiItem(QListWidgetItem* curItem)
{
	// ��õ�ǰitem������
	int index = pListWidgetWifi->currentRow();

	// ��ǰ��wifi��δ����
	if (index != m_conIndex)
	{
		WifiPasswdInput* pWifiPasswdInput = new WifiPasswdInput(this, m_strListWifi[index]);
		pWifiPasswdInput->setGeometry((WIN_WIDTH - 700) / 2 - 10, (WIN_HEIGHT - 516) / 2 - 40, 700, 516);
		int res = pWifiPasswdInput->exec();
		if (res == QDialog::Accepted)
		{
			// ���ǵ�һ�����ӵ�wifi��Ҫ����ǰһ������wifi���"�Թ�"ͼ��
			WifiItemWidget *pWifiItemLast = new WifiItemWidget;
			pListWidgetWifi->setItemWidget(m_lastItem, pWifiItemLast);
			pWifiItemLast->SetWifiName(m_strLastWifiName);
			pWifiItemLast->SetConStatus(false);

			// �ڵ�ǰindex����������QListWidget�������ѡ��
			WifiItemWidget *pWifiOptionWidget = new WifiItemWidget;
			pListWidgetWifi->setItemWidget(curItem, pWifiOptionWidget);
			pWifiOptionWidget->SetWifiName(m_strListWifi[index]);
			pWifiOptionWidget->SetConStatus(true);
			m_conIndex = index;

			// �����һ������wifi��
			m_lastItem = curItem;
			m_strLastWifiName = m_strListWifi[index];

			// �رոý��棬�����������ý���-����
			//this->accept();
			emit BtnNextWifi();
		}
	}
	else
	{
		// ��ǰ��wifi�Ѿ�����
		ForgetPasswd* pForgetPasswd = new ForgetPasswd(this, m_strListWifi[index]);
		pForgetPasswd->setGeometry((WIN_WIDTH - 700) / 2 - 10, (WIN_HEIGHT - 516) / 2 - 40, 700, 516);
		int res = pForgetPasswd->exec();
		if (res == QDialog::Accepted)
		{
			// �ڵ�ǰindex����������QListWidget������ò�ѡ��
			WifiItemWidget *pWifiOptionWidget = new WifiItemWidget(this);
			pListWidgetWifi->setItemWidget(curItem, pWifiOptionWidget);
			pWifiOptionWidget->SetWifiName(m_strListWifi[index]);
			pWifiOptionWidget->SetConStatus(false);

			// ����"���ӳɹ�wifi�������"Ϊ-1������"��������"���ٵ�������ظ�����
			m_conIndex = -1;
		}
	}
}
