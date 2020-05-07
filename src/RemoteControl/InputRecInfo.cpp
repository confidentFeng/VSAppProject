#include "InputRecInfo.h"

InputRecInfo::InputRecInfo(QDialog *parent)
	: QDialog(parent)
{
	/* 填写录制信息界面-初始化 */
	this->setFixedSize(480, 436);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->setAttribute(Qt::WA_DeleteOnClose);

	/* 子界面-初始化 */
	m_pWidgetChild = new QWidget(this);
	m_pWidgetChild->setGeometry(0, 0, 480, 436);
	m_pWidgetChild->setObjectName("InputRecInfo_WidgetChild");

	/* 输入相关标签与文本框-初始化 */
	m_pLabTitle = new QLabel;
	m_pBtnClose = new QPushButton;
	m_pLabPresenter = new QLabel;
	m_pEditPresenter = new QLineEdit;
	m_pLabSubject = new QLabel;
	m_pEditSubject = new QLineEdit;
	m_pLabTitle->setObjectName("InputRecInfo_LabTitle");
	m_pBtnClose->setObjectName("InputRecInfo_BtnClose");
	m_pLabPresenter->setObjectName("InputRecInfo_LabPresenter");
	m_pEditPresenter->setObjectName("InputRecInfo_EditPresenter");
	m_pLabSubject->setObjectName("InputRecInfo_LabSubject");
	m_pEditSubject->setObjectName("InputRecInfo_EditSubject");
	m_pLabTitle->setText("填写录制信息");
	m_pLabPresenter->setText("主讲人");
	m_pLabSubject->setText("课题名称");
	m_pBtnClose->setFixedSize(42, 42);
	m_pEditPresenter->setFixedSize(400, 48);
	m_pEditSubject->setFixedSize(400, 48);

	/* 保存按钮与倒计时标签-初始化 */
	m_pBtnSave = new QPushButton;
	m_pBtnCancel = new QPushButton;
	m_pLabCountdown = new QLabel;
	m_pBtnSave->setObjectName("InputRecInfo_BtnSave");
	m_pBtnCancel->setObjectName("InputRecInfo_BtnCancel");
	m_pLabCountdown->setObjectName("InputRecInfo_LabCountdown");
	m_pBtnSave->setText("保存");
	m_pBtnCancel->setText("取消");
	m_pLabCountdown->setText("             ");
	//m_pLabCountdown->setText("3秒后开始录制");
	m_pBtnSave->setFixedSize(136, 48);
	m_pBtnCancel->setFixedSize(136, 48);
	m_pLabCountdown->setFixedSize(104, 16);

	/* 标题栏相关-水平布局 */
	QHBoxLayout *pHLayoutTitle = new QHBoxLayout;
	pHLayoutTitle->addWidget(m_pLabTitle);
	pHLayoutTitle->addStretch();
	pHLayoutTitle->addWidget(m_pBtnClose);

	/* 文本框相关-垂直布局 */
	QVBoxLayout *pVLayoutEdit = new QVBoxLayout;
	pVLayoutEdit->addWidget(m_pLabPresenter);
	pVLayoutEdit->addWidget(m_pEditPresenter);
	pVLayoutEdit->addSpacing(20);
	pVLayoutEdit->addWidget(m_pLabSubject);
	pVLayoutEdit->addWidget(m_pEditSubject);

	/* 子布局-为了在左侧空出一些位置 */
	QHBoxLayout *pHLayoutChild = new QHBoxLayout;
	pHLayoutChild->addLayout(pVLayoutEdit);

	/* 保存按钮相关-网格布局 */
	QGridLayout *pGLayoutSave = new QGridLayout;
	pGLayoutSave->addWidget(m_pBtnCancel, 0, 0);
	pGLayoutSave->addWidget(m_pBtnSave, 0, 1);
	pGLayoutSave->addWidget(m_pLabCountdown, 1, 1, Qt::AlignCenter);

	/* 主布局 */
	QVBoxLayout *pVLayoutMain = new QVBoxLayout(m_pWidgetChild);
	pVLayoutMain->addLayout(pHLayoutTitle);
	pVLayoutMain->addSpacing(54);
	pVLayoutMain->addLayout(pHLayoutChild);
	pVLayoutMain->addSpacing(40);
	pVLayoutMain->addLayout(pGLayoutSave);

	/* 给LineEdit控件添加事件过滤器 */
	m_pEditPresenter->installEventFilter(this);
	m_pEditSubject->installEventFilter(this);

	/* 初始化定时器 */
	m_pTimer = new QTimer();
	m_pTimer->setInterval(1000);
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));

	// 解决按回车键窗口退出的问题，因为按钮默认设置成了StrongFocus
	m_pBtnClose->setFocusPolicy(Qt::NoFocus);
	m_pBtnCancel->setFocusPolicy(Qt::NoFocus);

	// 连接槽函数
	connect(m_pBtnClose, SIGNAL(clicked()), this, SLOT(CloseSlot()));
	connect(m_pBtnCancel, SIGNAL(clicked()), this, SLOT(CloseSlot()));
	connect(m_pBtnSave, SIGNAL(clicked()), this, SLOT(SaveSlot()));
}

InputRecInfo::~InputRecInfo()
{

}

// 键盘按下事件：解决按Esc键窗口退出的问题
void InputRecInfo::keyPressEvent(QKeyEvent *event)
{
	// 什么都不用做
}

// 调用小键盘
void InputRecInfo::CallKeyBoard()
{
	PVOID OldValue = nullptr;
	BOOL bRet = Wow64DisableWow64FsRedirection(&OldValue);
	QString csProcess = "C:\\Windows\\System32\\osk.exe";
	QString params = "";
	ShellExecute(nullptr, L"open", (LPCWSTR)csProcess.utf16(), (LPCWSTR)params.utf16(), nullptr, SW_SHOWNORMAL);
	if (bRet)
	{
		Wow64RevertWow64FsRedirection(OldValue);
	}
}

// 事件过滤器函数重写
bool InputRecInfo::eventFilter(QObject *watched, QEvent *event)
{
	if ((watched == m_pEditPresenter || watched == m_pEditSubject) && (event->type() == QEvent::MouseButtonPress))
	{
		// 调用小键盘
		//CallKeyBoard();
	}

	return QWidget::eventFilter(watched, event);
}

// 关闭槽函数
void InputRecInfo::CloseSlot()
{
	this->close();
	delete this;
}

// 保存槽函数
void InputRecInfo::SaveSlot()
{
	// 判断各输入栏是否有输入
	if (m_pEditPresenter->text().isEmpty() || m_pEditSubject->text().isEmpty())
	{
		MyPromptBox *pPromptBox = new MyPromptBox;
		pPromptBox->setLabInfo("各输入栏都要有输入", PromptIcon);
		pPromptBox->exec();
		return;
	}

	CountdownNum = 3;
	// 开启定时器
	m_pTimer->start();
	// 显示倒计时标签
	m_pLabCountdown->setText("3秒后开始录制");

	// 读取配置文件中的信息
	QString iniFilePath = QApplication::applicationDirPath() + "/config.ini";
	QSettings *iniRead = new QSettings(iniFilePath, QSettings::IniFormat);
	QString hostIP = iniRead->value("hostIP").toString();
	delete iniRead;

#if HTTP_TEST
	// http发送设置"设置课堂信息"
	QString strRecInfo = QString("http://%1/ROCPOW.cgi?type=18&token=xx&speaker=%2&title=%3")\
						.arg(hostIP).arg(m_pEditPresenter->text()).arg(m_pEditSubject->text());
	HttpClient(strRecInfo).success([](const QString &response) {
		qDebug().noquote() << "设置课堂信息: " << response << endl;
	}).fail([](const QString &error, int errorCode) {
		qDebug().noquote() << "error: " << error << errorCode << endl;
	}).get();
#endif
}

// 超时槽函数
void InputRecInfo::onTimeOut()
{
	qDebug() << "锁屏";

	CountdownNum--;
	m_pLabCountdown->setText(QString("%1秒后开始录制").arg(CountdownNum));
	if (CountdownNum == 0)
	{
		// 终止定时器
		m_pTimer->stop();


		// 返回值QDialog::Accepted，并关闭该窗口
		this->accept();
		this->close();
	}
}