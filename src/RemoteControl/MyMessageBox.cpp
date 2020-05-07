#include "MyMessageBox.h"

MyMessageBox::MyMessageBox(QDialog *parent)
	: QDialog(parent)
{
	// 初始化函数
	Init();
}

MyMessageBox::~MyMessageBox()
{

}

// 初始化函数
void MyMessageBox::Init()
{
	/* 消息框界面-初始化 */
	this->setFixedSize(700, 416);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->setAttribute(Qt::WA_DeleteOnClose);

	/* 子界面-初始化 */
	m_pWidgetChild = new QWidget(this);
	m_pWidgetChild->setGeometry(0, 0, 700, 416);
	m_pWidgetChild->setObjectName("MyMessageBox_WidgetChild");

	/* 窗口部件-初始化 */
	m_pLabTitle = new QLabel;
	m_pBtnClose = new QPushButton;
	m_pLabInco = new QLabel;
	m_pLabInfo = new QLabel;
	m_pBtnOK = new QPushButton;
	m_pBtnCancel = new QPushButton;
	m_pLabTitle->setObjectName("MyMessageBox_LabTitle");
	m_pBtnClose->setObjectName("MyMessageBox_BtnClose");
	m_pLabInco->setObjectName("MyMessageBox_LabInco");
	m_pLabInfo->setObjectName("MyMessageBox_LabInfo");
	m_pBtnOK->setObjectName("MyMessageBox_BtnOK");
	m_pBtnCancel->setObjectName("MyMessageBox_BtnCancel");
	m_pBtnOK->setText("确定");
	m_pBtnCancel->setText("取消");
	m_pBtnClose->setFixedSize(42, 42);
	m_pBtnOK->setFixedSize(136, 48);
	m_pBtnCancel->setFixedSize(136, 48);

	/* 标题栏-水平布局 */
	QHBoxLayout *pHLayoutTitle = new QHBoxLayout();
	pHLayoutTitle->addWidget(m_pLabTitle);
	pHLayoutTitle->addStretch(1);
	pHLayoutTitle->addWidget(m_pBtnClose);

	/* 按钮布局 */
	QHBoxLayout *pHLayoutButton = new QHBoxLayout;
	pHLayoutButton->addWidget(m_pBtnCancel);
	pHLayoutButton->addWidget(m_pBtnOK);

	/* 主布局 */
	QVBoxLayout *pVLayoutMain = new QVBoxLayout(m_pWidgetChild);
	
	pVLayoutMain->addLayout(pHLayoutTitle);
	pVLayoutMain->addSpacing(40);
	pVLayoutMain->addWidget(m_pLabInco, 0, Qt::AlignCenter);
	pVLayoutMain->addWidget(m_pLabInfo, 0, Qt::AlignCenter);
	pVLayoutMain->addSpacing(50);
	pVLayoutMain->addLayout(pHLayoutButton);
	pVLayoutMain->addSpacing(30);

	// 连接槽函数
	connect(m_pBtnClose, SIGNAL(clicked()), this, SLOT(CloseSlot()));
	connect(m_pBtnCancel, SIGNAL(clicked()), this, SLOT(CloseSlot()));
	connect(m_pBtnOK, SIGNAL(clicked()), this, SLOT(OKSlot()));
}

// 设置标题标签的文本
void MyMessageBox::SetTitleText(const QString &strTitle)
{
	m_pLabTitle->setText(strTitle);

	if (m_pLabTitle->text() == "使用说明")
	{
		this->setFixedSize(700, 516);
		m_pWidgetChild->setGeometry(0, 0, 700, 516);
	}
}

// 设置消息标签的文本
void MyMessageBox::SetInfoText(const QString &strText)
{
	m_pLabInfo->setText(strText);
}

// 显示控制函数
void MyMessageBox::ShowControl(bool isShowIconFlag, bool isShowOKFlag, const QString& strText)
{
	// 选择显示感叹号图标标签，还是文本
	if (isShowIconFlag)
	{
		m_pLabInco->setFixedSize(60, 60);
		m_pLabInco->setStyleSheet("border-image: url(:/Popup/image/Popup/MainWidget_LabInco.png)");
	}
	else
	{
		m_pLabInco->setText(strText);
	}

	if (strText == "请插入网络连接")
	{
		this->setFixedSize(700, 516);
		m_pWidgetChild->setGeometry(0, 0, 700, 516);
	}

	// 是否显示确定按钮
	if (!isShowOKFlag)
	{
		m_pBtnOK->hide();
	}
}

// 关闭按钮槽函数
void MyMessageBox::CloseSlot()
{
	this->close();
	delete this;
}

// 确定按钮槽函数
void MyMessageBox::OKSlot()
{
	this->accept();
}