#include "MyPromptBox.h"

MyPromptBox::MyPromptBox(QDialog *parent)
	: QDialog(parent)
{
	/* ��ʾ�����-��ʼ�� */
	this->setFixedSize(360, 270);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);		
	this->setObjectName("MyPromptBox_Widget");
	this->setAttribute(Qt::WA_DeleteOnClose);

	/* ���ڲ���-��ʼ�� */
	m_pLabIcon = new QLabel;
	m_pLabInfo = new QLabel;
	m_pLabIcon->setObjectName("MyPromptBox_LabIcon");
	m_pLabInfo->setObjectName("MyPromptBox_LabInfo");
	m_pLabIcon->setFixedSize(124, 124);

	/* ������-��ֱ���� */
	QVBoxLayout *pVLayoutMain = new QVBoxLayout(this);
	pVLayoutMain->addStretch(1);
	pVLayoutMain->addWidget(m_pLabIcon, 0, Qt::AlignCenter);
	pVLayoutMain->addStretch(1);
	pVLayoutMain->addWidget(m_pLabInfo, 0, Qt::AlignCenter);
	pVLayoutMain->addStretch(1);

	// ��ʼ1���Ӽ�ʱ
	startTimer(1000);
}

MyPromptBox::~MyPromptBox()
{

}

// ��ʱ���¼�������1���رմ���
void MyPromptBox::timerEvent(QTimerEvent *event)
{
	this->close();
}

// ������Ϣ��ǩ���ı�
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
