#include "MyMessageBox.h"

MyMessageBox::MyMessageBox(QDialog *parent)
	: QDialog(parent)
{
	// ��ʼ������
	Init();
}

MyMessageBox::~MyMessageBox()
{

}

// ��ʼ������
void MyMessageBox::Init()
{
	/* ��Ϣ�����-��ʼ�� */
	this->setFixedSize(700, 416);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->setAttribute(Qt::WA_DeleteOnClose);

	/* �ӽ���-��ʼ�� */
	m_pWidgetChild = new QWidget(this);
	m_pWidgetChild->setGeometry(0, 0, 700, 416);
	m_pWidgetChild->setObjectName("MyMessageBox_WidgetChild");

	/* ���ڲ���-��ʼ�� */
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
	m_pBtnOK->setText("ȷ��");
	m_pBtnCancel->setText("ȡ��");
	m_pBtnClose->setFixedSize(42, 42);
	m_pBtnOK->setFixedSize(136, 48);
	m_pBtnCancel->setFixedSize(136, 48);

	/* ������-ˮƽ���� */
	QHBoxLayout *pHLayoutTitle = new QHBoxLayout();
	pHLayoutTitle->addWidget(m_pLabTitle);
	pHLayoutTitle->addStretch(1);
	pHLayoutTitle->addWidget(m_pBtnClose);

	/* ��ť���� */
	QHBoxLayout *pHLayoutButton = new QHBoxLayout;
	pHLayoutButton->addWidget(m_pBtnCancel);
	pHLayoutButton->addWidget(m_pBtnOK);

	/* ������ */
	QVBoxLayout *pVLayoutMain = new QVBoxLayout(m_pWidgetChild);
	
	pVLayoutMain->addLayout(pHLayoutTitle);
	pVLayoutMain->addSpacing(40);
	pVLayoutMain->addWidget(m_pLabInco, 0, Qt::AlignCenter);
	pVLayoutMain->addWidget(m_pLabInfo, 0, Qt::AlignCenter);
	pVLayoutMain->addSpacing(50);
	pVLayoutMain->addLayout(pHLayoutButton);
	pVLayoutMain->addSpacing(30);

	// ���Ӳۺ���
	connect(m_pBtnClose, SIGNAL(clicked()), this, SLOT(CloseSlot()));
	connect(m_pBtnCancel, SIGNAL(clicked()), this, SLOT(CloseSlot()));
	connect(m_pBtnOK, SIGNAL(clicked()), this, SLOT(OKSlot()));
}

// ���ñ����ǩ���ı�
void MyMessageBox::SetTitleText(const QString &strTitle)
{
	m_pLabTitle->setText(strTitle);

	if (m_pLabTitle->text() == "ʹ��˵��")
	{
		this->setFixedSize(700, 516);
		m_pWidgetChild->setGeometry(0, 0, 700, 516);
	}
}

// ������Ϣ��ǩ���ı�
void MyMessageBox::SetInfoText(const QString &strText)
{
	m_pLabInfo->setText(strText);
}

// ��ʾ���ƺ���
void MyMessageBox::ShowControl(bool isShowIconFlag, bool isShowOKFlag, const QString& strText)
{
	// ѡ����ʾ��̾��ͼ���ǩ�������ı�
	if (isShowIconFlag)
	{
		m_pLabInco->setFixedSize(60, 60);
		m_pLabInco->setStyleSheet("border-image: url(:/Popup/image/Popup/MainWidget_LabInco.png)");
	}
	else
	{
		m_pLabInco->setText(strText);
	}

	if (strText == "�������������")
	{
		this->setFixedSize(700, 516);
		m_pWidgetChild->setGeometry(0, 0, 700, 516);
	}

	// �Ƿ���ʾȷ����ť
	if (!isShowOKFlag)
	{
		m_pBtnOK->hide();
	}
}

// �رհ�ť�ۺ���
void MyMessageBox::CloseSlot()
{
	this->close();
	delete this;
}

// ȷ����ť�ۺ���
void MyMessageBox::OKSlot()
{
	this->accept();
}