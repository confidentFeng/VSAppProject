#include "ForgetPasswd.h"

ForgetPasswd::ForgetPasswd(QDialog *parent, const QString& strWifiName)
	: QDialog(parent)
{
	/* ������-��ʼ�� */
	this->setFixedSize(700, 516);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->move((WIN_WIDTH - 700) / 2 - 10, (WIN_HEIGHT - 516) / 2); // ��Ϊ����������ƫ����10����

	/* �ӽ���-��ʼ�� */
	m_pWidgetChild = new QWidget(this);
	m_pWidgetChild->setGeometry(0, 0, 700, 516);
	m_pWidgetChild->setObjectName("ForgetPasswd_WidgetChild");

	/* ���ڲ���-��ʼ�� */
	m_pBtnClose = new QPushButton;
	m_pLabIcon = new QLabel;
	m_pLabWifi = new QLabel;
	m_pBtnForget = new QPushButton;
	m_pBtnCancel = new QPushButton;
	m_pBtnClose->setObjectName("ForgetPasswd_BtnClose");
	m_pLabIcon->setObjectName("ForgetPasswd_LabIcon");
	m_pLabWifi->setObjectName("ForgetPasswd_LabWifi");
	m_pBtnForget->setObjectName("ForgetPasswd_BtnForget");
	m_pBtnCancel->setObjectName("ForgetPasswd_BtnCancel");
	m_pLabWifi->setText(strWifiName);
	m_pBtnForget->setText("��������");
	m_pBtnCancel->setText("ȡ��");
	m_pBtnClose->setFixedSize(42, 42);
	m_pLabIcon->setFixedSize(300, 84);
	m_pBtnForget->setFixedSize(136, 48);
	m_pBtnCancel->setFixedSize(136, 48);

	/* ��ť���� */
	QHBoxLayout *pHLayoutButton = new QHBoxLayout;
	pHLayoutButton->addStretch(1);
	pHLayoutButton->addWidget(m_pBtnCancel);
	pHLayoutButton->addSpacing(30);
	pHLayoutButton->addWidget(m_pBtnForget);
	pHLayoutButton->addStretch(1);

	/* ������-��ֱ���� */
	QVBoxLayout *pVLayoutMain = new QVBoxLayout(m_pWidgetChild);
	pVLayoutMain->addSpacing(6);
	pVLayoutMain->addWidget(m_pBtnClose, 0, Qt::AlignRight);
	pVLayoutMain->addStretch(3);
	pVLayoutMain->addWidget(m_pLabIcon, 0, Qt::AlignCenter);	
	pVLayoutMain->addStretch(1);
	pVLayoutMain->addWidget(m_pLabWifi, 0, Qt::AlignCenter);
	pVLayoutMain->addStretch(2);
	pVLayoutMain->addLayout(pHLayoutButton);
	pVLayoutMain->addSpacing(30);

	// �رհ�ť-����ۺ���
	QObject::connect(m_pBtnClose, &QPushButton::clicked, [=]() {
		this->close();
	});

	// �������밴ť-����ۺ���
	QObject::connect(m_pBtnForget, &QPushButton::clicked, [=]() {
		Common::Get()->ExecuteCmd(QString("netsh wlan delete profile name=%1").arg(strWifiName));
		this->accept();
	});

	// ȡ����ť-����ۺ���
	QObject::connect(m_pBtnCancel, &QPushButton::clicked, [=]() {
		this->close();
	});
}

ForgetPasswd::~ForgetPasswd()
{

}
