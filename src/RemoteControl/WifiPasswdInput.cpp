#include "WifiPasswdInput.h"

WifiPasswdInput::WifiPasswdInput(QDialog *parent, const QString& strWifiName)
	: QDialog(parent)
{
	/* ������-��ʼ�� */
	this->setFixedSize(700, 516);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->move((WIN_WIDTH -700)/2-10, (WIN_HEIGHT-516)/2); // ��Ϊ����������ƫ����10����

	/* �ӽ���-��ʼ�� */
	m_pWidgetChild = new QWidget(this);
	m_pWidgetChild->setGeometry(0, 0, 700, 516);
	m_pWidgetChild->setObjectName("WifiPasswdInput_WidgetChild");

	/* ���ڲ���-��ʼ�� */
	m_pBtnClose = new QPushButton;
	m_pLabPasswd = new QLabel;
	m_pEditPasswd = new QLineEdit;
	m_pBtnOK = new QPushButton;
	m_pBtnCancel = new QPushButton;
	m_pBtnClose->setObjectName("WifiPasswdInput_BtnClose");
	m_pLabPasswd->setObjectName("WifiPasswdInput_LabPasswd");
	m_pEditPasswd->setObjectName("WifiPasswdInput_EditPasswd");
	m_pBtnOK->setObjectName("WifiPasswdInput_BtnOK");
	m_pBtnCancel->setObjectName("WifiPasswdInput_BtnCancel");
	m_pLabPasswd->setText(strWifiName);
	m_pBtnOK->setText("ȷ��");
	m_pBtnCancel->setText("ȡ��");
	m_pBtnClose->setFixedSize(42, 42);
	m_pEditPasswd->setFixedSize(400, 48);
	m_pBtnOK->setFixedSize(136, 48);
	m_pBtnCancel->setFixedSize(136, 48);
	m_pEditPasswd->setPlaceholderText("������WIFI����");
	m_pEditPasswd->setEchoMode(QLineEdit::Password);
	m_pEditPasswd->setMaxLength(16);

	/* ��ť���� */
	QHBoxLayout *pHLayoutButton = new QHBoxLayout;
	pHLayoutButton->addStretch(1);
	pHLayoutButton->addWidget(m_pBtnCancel);
	pHLayoutButton->addSpacing(30);
	pHLayoutButton->addWidget(m_pBtnOK);
	pHLayoutButton->addStretch(1);

	/* ������-��ֱ���� */
	QVBoxLayout *pVLayoutMain = new QVBoxLayout(m_pWidgetChild);
	pVLayoutMain->addSpacing(6);
	pVLayoutMain->addWidget(m_pBtnClose, 0, Qt::AlignRight);
	pVLayoutMain->addSpacing(100);
	pVLayoutMain->addWidget(m_pLabPasswd, 0, Qt::AlignCenter);
	pVLayoutMain->addStretch(1);
	pVLayoutMain->addWidget(m_pEditPasswd, 0, Qt::AlignCenter);
	pVLayoutMain->addStretch(1);
	pVLayoutMain->addLayout(pHLayoutButton);
	pVLayoutMain->addSpacing(50);

	// �رհ�ť-����ۺ���
	QObject::connect(m_pBtnClose, &QPushButton::clicked, [=]() {
		this->close();
	});

	// ȷ����ť-����ۺ���
	QObject::connect(m_pBtnOK, &QPushButton::clicked, [=]() {
		// ��������������Ƿ�Ϊ��
		if (m_pEditPasswd->text().isEmpty())
		{
			MyPromptBox *pPromptBox = new MyPromptBox;
			pPromptBox->setLabInfo("���벻��Ϊ��", FailIcon);
			pPromptBox->exec();
			return;
		}

		// 1. ����wifi�����ļ�
		XmlHelper::Get()->WriteXml(strWifiName, m_pEditPasswd->text());
		// 2. ���wifi�����ļ�
		QString strReturn = Common::Get()->ExecuteCmd(QString("netsh wlan add profile filename=%1/%2.xml")\
			.arg(QApplication::applicationDirPath()).arg(strWifiName));
		if (strReturn.contains("�ѽ������ļ�"))
		{
			// 3. ����wifi
			Common::Get()->ExecuteCmd(QString("netsh wlan connect name=%1").arg(strWifiName));

			this->accept();
			this->close();
		}
		else if (strReturn.contains("�����ļ���ʽ����"))
		{
			MyPromptBox *pPromptBox = new MyPromptBox;
			pPromptBox->setLabInfo("wifi�������", FailIcon);
			pPromptBox->exec();

			// ͬʱ���������������
			m_pEditPasswd->clear();
		}

		// �������wifi�����ļ��Ƿ�ɹ�����ɾ����Ӧ�����ļ�
		QString fileName = QApplication::applicationDirPath() + "/" + strWifiName + ".xml";
		QFile fileTemp(fileName);
		fileTemp.remove();
	});

	// ȡ����ť-����ۺ���
	QObject::connect(m_pBtnCancel, &QPushButton::clicked, [=]() {
		this->close();
	});
}

WifiPasswdInput::~WifiPasswdInput()
{

}
