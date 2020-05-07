#include "LockScreen.h"

LockScreen::LockScreen(QWidget *parent)
	: QWidget(parent)
{
	/* 锁屏界面-初始化 */
	this->setFixedSize(WIN_WIDTH, WIN_HEIGHT);
	// 必须设置Qt::Dialog，才能在平板模式弹出小键盘
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->setAttribute(Qt::WA_DeleteOnClose);

	/* 子界面-初始化 */
	m_pWidgetChild = new QWidget(this);
	m_pWidgetChild->setGeometry(0, 0, WIN_WIDTH, WIN_HEIGHT);
	m_pWidgetChild->setObjectName("LockScreen_WidgetChild");

	/* 窗口部件-初始化 */
	m_pLabHead = new QLabel;
	m_pLabAccount = new QLabel;
	m_pEditPasswd = new QLineEdit;
	m_pLabHead->setObjectName("LockScreen_LabHead");
	m_pLabAccount->setObjectName("LockScreen_LabAccount");
	m_pEditPasswd->setObjectName("LockScreen_EditPasswd");
	m_pLabHead->setFixedSize(250, 250);
	m_pEditPasswd->setFixedSize(600, 68);
	m_pEditPasswd->setPlaceholderText("请输入录播主机密码");
	m_pEditPasswd->setEchoMode(QLineEdit::Password);
	m_pEditPasswd->setValidator(new QRegExpValidator(QRegExp(REGEXP_PASSWD)));

	/* 主布局 */
	QVBoxLayout *pVLayoutMain = new QVBoxLayout(m_pWidgetChild);
	pVLayoutMain->addStretch(6);
	pVLayoutMain->addWidget(m_pLabHead, 0, Qt::AlignCenter);
	pVLayoutMain->addStretch(1);
	pVLayoutMain->addWidget(m_pLabAccount, 0, Qt::AlignCenter);
	pVLayoutMain->addStretch(3);
	pVLayoutMain->addWidget(m_pEditPasswd, 0, Qt::AlignCenter);
	pVLayoutMain->addStretch(24);

	/* 读取配置文件中的信息 */
	QString iniFilePath = QApplication::applicationDirPath() + "/config.ini";
	QSettings *iniRead = new QSettings(iniFilePath, QSettings::IniFormat);
	QString hostAccount = iniRead->value("hostAccount").toString();
	qDebug() << "hostAccount: " << hostAccount;
	delete iniRead;
	// 设置账号名
	m_pLabAccount->setText(hostAccount);

	/* 连接信号槽 */
	connect(m_pEditPasswd, SIGNAL(returnPressed()), this, SLOT(EnterSlot()));
}

LockScreen::~LockScreen()
{

}

// 文本框回车键响应的槽函数
void LockScreen::EnterSlot()
{
	/* 读取配置文件中的信息 */
	QString iniFilePath = QApplication::applicationDirPath() + "/config.ini";
	QSettings *iniRead = new QSettings(iniFilePath, QSettings::IniFormat);
	QString hostPasswd = iniRead->value("hostPasswd").toString();
	qDebug() << "hostPasswd: " << hostPasswd;
	delete iniRead;

	if (m_pEditPasswd->text() == hostPasswd)
	{
		MyPromptBox *pPromptBox = new MyPromptBox;
		pPromptBox->setLabInfo("解除屏幕锁定成功", SuccessIcon);
		pPromptBox->exec();

		this->close();
	}
	else if (m_pEditPasswd->text().isEmpty())
	{
		MyPromptBox *pPromptBox = new MyPromptBox;
		pPromptBox->setLabInfo("输入栏不能为空", PromptIcon);
		pPromptBox->exec();
	}
	else
	{
		MyPromptBox *pPromptBox = new MyPromptBox;
		pPromptBox->setLabInfo("密码错误", FailIcon);
		pPromptBox->exec();
	}
}
