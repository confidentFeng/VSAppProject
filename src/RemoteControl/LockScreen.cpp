#include "LockScreen.h"

LockScreen::LockScreen(QWidget *parent)
	: QWidget(parent)
{
	/* ��������-��ʼ�� */
	this->setFixedSize(WIN_WIDTH, WIN_HEIGHT);
	// ��������Qt::Dialog��������ƽ��ģʽ����С����
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->setAttribute(Qt::WA_DeleteOnClose);

	/* �ӽ���-��ʼ�� */
	m_pWidgetChild = new QWidget(this);
	m_pWidgetChild->setGeometry(0, 0, WIN_WIDTH, WIN_HEIGHT);
	m_pWidgetChild->setObjectName("LockScreen_WidgetChild");

	/* ���ڲ���-��ʼ�� */
	m_pLabHead = new QLabel;
	m_pLabAccount = new QLabel;
	m_pEditPasswd = new QLineEdit;
	m_pLabHead->setObjectName("LockScreen_LabHead");
	m_pLabAccount->setObjectName("LockScreen_LabAccount");
	m_pEditPasswd->setObjectName("LockScreen_EditPasswd");
	m_pLabHead->setFixedSize(250, 250);
	m_pEditPasswd->setFixedSize(600, 68);
	m_pEditPasswd->setPlaceholderText("������¼����������");
	m_pEditPasswd->setEchoMode(QLineEdit::Password);
	m_pEditPasswd->setValidator(new QRegExpValidator(QRegExp(REGEXP_PASSWD)));

	/* ������ */
	QVBoxLayout *pVLayoutMain = new QVBoxLayout(m_pWidgetChild);
	pVLayoutMain->addStretch(6);
	pVLayoutMain->addWidget(m_pLabHead, 0, Qt::AlignCenter);
	pVLayoutMain->addStretch(1);
	pVLayoutMain->addWidget(m_pLabAccount, 0, Qt::AlignCenter);
	pVLayoutMain->addStretch(3);
	pVLayoutMain->addWidget(m_pEditPasswd, 0, Qt::AlignCenter);
	pVLayoutMain->addStretch(24);

	/* ��ȡ�����ļ��е���Ϣ */
	QString iniFilePath = QApplication::applicationDirPath() + "/config.ini";
	QSettings *iniRead = new QSettings(iniFilePath, QSettings::IniFormat);
	QString hostAccount = iniRead->value("hostAccount").toString();
	qDebug() << "hostAccount: " << hostAccount;
	delete iniRead;
	// �����˺���
	m_pLabAccount->setText(hostAccount);

	/* �����źŲ� */
	connect(m_pEditPasswd, SIGNAL(returnPressed()), this, SLOT(EnterSlot()));
}

LockScreen::~LockScreen()
{

}

// �ı���س�����Ӧ�Ĳۺ���
void LockScreen::EnterSlot()
{
	/* ��ȡ�����ļ��е���Ϣ */
	QString iniFilePath = QApplication::applicationDirPath() + "/config.ini";
	QSettings *iniRead = new QSettings(iniFilePath, QSettings::IniFormat);
	QString hostPasswd = iniRead->value("hostPasswd").toString();
	qDebug() << "hostPasswd: " << hostPasswd;
	delete iniRead;

	if (m_pEditPasswd->text() == hostPasswd)
	{
		MyPromptBox *pPromptBox = new MyPromptBox;
		pPromptBox->setLabInfo("�����Ļ�����ɹ�", SuccessIcon);
		pPromptBox->exec();

		this->close();
	}
	else if (m_pEditPasswd->text().isEmpty())
	{
		MyPromptBox *pPromptBox = new MyPromptBox;
		pPromptBox->setLabInfo("����������Ϊ��", PromptIcon);
		pPromptBox->exec();
	}
	else
	{
		MyPromptBox *pPromptBox = new MyPromptBox;
		pPromptBox->setLabInfo("�������", FailIcon);
		pPromptBox->exec();
	}
}
