#include "MyPromptBox.h"

MyPromptBox::MyPromptBox(QDialog *parent)
	: QDialog(parent)
{
	/* 提示框界面-初始化 */
	this->setFixedSize(360, 270);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);		
	this->setObjectName("MyPromptBox_Widget");
	this->setAttribute(Qt::WA_DeleteOnClose);

	/* 窗口部件-初始化 */
	m_pLabIcon = new QLabel;
	m_pLabInfo = new QLabel;
	m_pLabIcon->setObjectName("MyPromptBox_LabIcon");
	m_pLabInfo->setObjectName("MyPromptBox_LabInfo");
	m_pLabIcon->setFixedSize(124, 124);

	/* 主窗口-垂直布局 */
	QVBoxLayout *pVLayoutMain = new QVBoxLayout(this);
	pVLayoutMain->addStretch(1);
	pVLayoutMain->addWidget(m_pLabIcon, 0, Qt::AlignCenter);
	pVLayoutMain->addStretch(1);
	pVLayoutMain->addWidget(m_pLabInfo, 0, Qt::AlignCenter);
	pVLayoutMain->addStretch(1);

	// 开始1秒钟计时
	startTimer(1000);
}

MyPromptBox::~MyPromptBox()
{

}

// 定时器事件：用于1秒后关闭窗口
void MyPromptBox::timerEvent(QTimerEvent *event)
{
	this->close();
}

// 设置消息标签的文本
void MyPromptBox::setLabInfo(const QString& strText, const EnumIcon enumIcon)
{
	if(enumIcon == SuccessIcon)
		m_pLabIcon->setPixmap(QPixmap(":/Popup/image/Popup/MyPromptBox_LabIcon_success.png"));
	else if (enumIcon == FailIcon)
		m_pLabIcon->setPixmap(QPixmap(":/Popup/image/Popup/MyPromptBox_LabIcon_fail.png"));
	else if (enumIcon == PromptIcon)
		m_pLabIcon->setPixmap(QPixmap(":/Popup/image/Popup/MyPromptBox_LabIcon_prompt.png"));

	m_pLabInfo->setText(strText);
}
