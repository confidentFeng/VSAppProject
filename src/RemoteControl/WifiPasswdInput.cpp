#include "WifiPasswdInput.h"

WifiPasswdInput::WifiPasswdInput(QDialog *parent, const QString& strWifiName)
	: QDialog(parent)
{
	/* 主界面-初始化 */
	this->setFixedSize(700, 516);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->move((WIN_WIDTH -700)/2-10, (WIN_HEIGHT-516)/2); // 因为主窗口向左偏移了10像素

	/* 子界面-初始化 */
	m_pWidgetChild = new QWidget(this);
	m_pWidgetChild->setGeometry(0, 0, 700, 516);
	m_pWidgetChild->setObjectName("WifiPasswdInput_WidgetChild");

	/* 窗口部件-初始化 */
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
	m_pBtnOK->setText("确定");
	m_pBtnCancel->setText("取消");
	m_pBtnClose->setFixedSize(42, 42);
	m_pEditPasswd->setFixedSize(400, 48);
	m_pBtnOK->setFixedSize(136, 48);
	m_pBtnCancel->setFixedSize(136, 48);
	m_pEditPasswd->setPlaceholderText("请输入WIFI密码");
	m_pEditPasswd->setEchoMode(QLineEdit::Password);
	m_pEditPasswd->setMaxLength(16);

	/* 按钮布局 */
	QHBoxLayout *pHLayoutButton = new QHBoxLayout;
	pHLayoutButton->addStretch(1);
	pHLayoutButton->addWidget(m_pBtnCancel);
	pHLayoutButton->addSpacing(30);
	pHLayoutButton->addWidget(m_pBtnOK);
	pHLayoutButton->addStretch(1);

	/* 主窗口-垂直布局 */
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

	// 关闭按钮-点击槽函数
	QObject::connect(m_pBtnClose, &QPushButton::clicked, [=]() {
		this->close();
	});

	// 确定按钮-点击槽函数
	QObject::connect(m_pBtnOK, &QPushButton::clicked, [=]() {
		// 检测密码输入栏是否为空
		if (m_pEditPasswd->text().isEmpty())
		{
			MyPromptBox *pPromptBox = new MyPromptBox;
			pPromptBox->setLabInfo("密码不能为空", FailIcon);
			pPromptBox->exec();
			return;
		}

		// 1. 创建wifi配置文件
		XmlHelper::Get()->WriteXml(strWifiName, m_pEditPasswd->text());
		// 2. 添加wifi配置文件
		QString strReturn = Common::Get()->ExecuteCmd(QString("netsh wlan add profile filename=%1/%2.xml")\
			.arg(QApplication::applicationDirPath()).arg(strWifiName));
		if (strReturn.contains("已将配置文件"))
		{
			// 3. 连接wifi
			Common::Get()->ExecuteCmd(QString("netsh wlan connect name=%1").arg(strWifiName));

			this->accept();
			this->close();
		}
		else if (strReturn.contains("配置文件格式错误"))
		{
			MyPromptBox *pPromptBox = new MyPromptBox;
			pPromptBox->setLabInfo("wifi密码错误", FailIcon);
			pPromptBox->exec();

			// 同时将密码输入栏清空
			m_pEditPasswd->clear();
		}

		// 不管添加wifi配置文件是否成功，都删除相应配置文件
		QString fileName = QApplication::applicationDirPath() + "/" + strWifiName + ".xml";
		QFile fileTemp(fileName);
		fileTemp.remove();
	});

	// 取消按钮-点击槽函数
	QObject::connect(m_pBtnCancel, &QPushButton::clicked, [=]() {
		this->close();
	});
}

WifiPasswdInput::~WifiPasswdInput()
{

}
