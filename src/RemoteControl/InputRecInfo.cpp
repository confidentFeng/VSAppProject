#include "InputRecInfo.h"

InputRecInfo::InputRecInfo(QDialog *parent)
	: QDialog(parent)
{
	/* ��д¼����Ϣ����-��ʼ�� */
	this->setFixedSize(480, 436);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->setAttribute(Qt::WA_DeleteOnClose);

	/* �ӽ���-��ʼ�� */
	m_pWidgetChild = new QWidget(this);
	m_pWidgetChild->setGeometry(0, 0, 480, 436);
	m_pWidgetChild->setObjectName("InputRecInfo_WidgetChild");

	/* ������ر�ǩ���ı���-��ʼ�� */
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
	m_pLabTitle->setText("��д¼����Ϣ");
	m_pLabPresenter->setText("������");
	m_pLabSubject->setText("��������");
	m_pBtnClose->setFixedSize(42, 42);
	m_pEditPresenter->setFixedSize(400, 48);
	m_pEditSubject->setFixedSize(400, 48);

	/* ���水ť�뵹��ʱ��ǩ-��ʼ�� */
	m_pBtnSave = new QPushButton;
	m_pBtnCancel = new QPushButton;
	m_pLabCountdown = new QLabel;
	m_pBtnSave->setObjectName("InputRecInfo_BtnSave");
	m_pBtnCancel->setObjectName("InputRecInfo_BtnCancel");
	m_pLabCountdown->setObjectName("InputRecInfo_LabCountdown");
	m_pBtnSave->setText("����");
	m_pBtnCancel->setText("ȡ��");
	m_pLabCountdown->setText("             ");
	//m_pLabCountdown->setText("3���ʼ¼��");
	m_pBtnSave->setFixedSize(136, 48);
	m_pBtnCancel->setFixedSize(136, 48);
	m_pLabCountdown->setFixedSize(104, 16);

	/* ���������-ˮƽ���� */
	QHBoxLayout *pHLayoutTitle = new QHBoxLayout;
	pHLayoutTitle->addWidget(m_pLabTitle);
	pHLayoutTitle->addStretch();
	pHLayoutTitle->addWidget(m_pBtnClose);

	/* �ı������-��ֱ���� */
	QVBoxLayout *pVLayoutEdit = new QVBoxLayout;
	pVLayoutEdit->addWidget(m_pLabPresenter);
	pVLayoutEdit->addWidget(m_pEditPresenter);
	pVLayoutEdit->addSpacing(20);
	pVLayoutEdit->addWidget(m_pLabSubject);
	pVLayoutEdit->addWidget(m_pEditSubject);

	/* �Ӳ���-Ϊ�������ճ�һЩλ�� */
	QHBoxLayout *pHLayoutChild = new QHBoxLayout;
	pHLayoutChild->addLayout(pVLayoutEdit);

	/* ���水ť���-���񲼾� */
	QGridLayout *pGLayoutSave = new QGridLayout;
	pGLayoutSave->addWidget(m_pBtnCancel, 0, 0);
	pGLayoutSave->addWidget(m_pBtnSave, 0, 1);
	pGLayoutSave->addWidget(m_pLabCountdown, 1, 1, Qt::AlignCenter);

	/* ������ */
	QVBoxLayout *pVLayoutMain = new QVBoxLayout(m_pWidgetChild);
	pVLayoutMain->addLayout(pHLayoutTitle);
	pVLayoutMain->addSpacing(54);
	pVLayoutMain->addLayout(pHLayoutChild);
	pVLayoutMain->addSpacing(40);
	pVLayoutMain->addLayout(pGLayoutSave);

	/* ��LineEdit�ؼ�����¼������� */
	m_pEditPresenter->installEventFilter(this);
	m_pEditSubject->installEventFilter(this);

	/* ��ʼ����ʱ�� */
	m_pTimer = new QTimer();
	m_pTimer->setInterval(1000);
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));

	// ������س��������˳������⣬��Ϊ��ťĬ�����ó���StrongFocus
	m_pBtnClose->setFocusPolicy(Qt::NoFocus);
	m_pBtnCancel->setFocusPolicy(Qt::NoFocus);

	// ���Ӳۺ���
	connect(m_pBtnClose, SIGNAL(clicked()), this, SLOT(CloseSlot()));
	connect(m_pBtnCancel, SIGNAL(clicked()), this, SLOT(CloseSlot()));
	connect(m_pBtnSave, SIGNAL(clicked()), this, SLOT(SaveSlot()));
}

InputRecInfo::~InputRecInfo()
{

}

// ���̰����¼��������Esc�������˳�������
void InputRecInfo::keyPressEvent(QKeyEvent *event)
{
	// ʲô��������
}

// ����С����
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

// �¼�������������д
bool InputRecInfo::eventFilter(QObject *watched, QEvent *event)
{
	if ((watched == m_pEditPresenter || watched == m_pEditSubject) && (event->type() == QEvent::MouseButtonPress))
	{
		// ����С����
		//CallKeyBoard();
	}

	return QWidget::eventFilter(watched, event);
}

// �رղۺ���
void InputRecInfo::CloseSlot()
{
	this->close();
	delete this;
}

// ����ۺ���
void InputRecInfo::SaveSlot()
{
	// �жϸ��������Ƿ�������
	if (m_pEditPresenter->text().isEmpty() || m_pEditSubject->text().isEmpty())
	{
		MyPromptBox *pPromptBox = new MyPromptBox;
		pPromptBox->setLabInfo("����������Ҫ������", PromptIcon);
		pPromptBox->exec();
		return;
	}

	CountdownNum = 3;
	// ������ʱ��
	m_pTimer->start();
	// ��ʾ����ʱ��ǩ
	m_pLabCountdown->setText("3���ʼ¼��");

	// ��ȡ�����ļ��е���Ϣ
	QString iniFilePath = QApplication::applicationDirPath() + "/config.ini";
	QSettings *iniRead = new QSettings(iniFilePath, QSettings::IniFormat);
	QString hostIP = iniRead->value("hostIP").toString();
	delete iniRead;

#if HTTP_TEST
	// http��������"���ÿ�����Ϣ"
	QString strRecInfo = QString("http://%1/ROCPOW.cgi?type=18&token=xx&speaker=%2&title=%3")\
						.arg(hostIP).arg(m_pEditPresenter->text()).arg(m_pEditSubject->text());
	HttpClient(strRecInfo).success([](const QString &response) {
		qDebug().noquote() << "���ÿ�����Ϣ: " << response << endl;
	}).fail([](const QString &error, int errorCode) {
		qDebug().noquote() << "error: " << error << errorCode << endl;
	}).get();
#endif
}

// ��ʱ�ۺ���
void InputRecInfo::onTimeOut()
{
	qDebug() << "����";

	CountdownNum--;
	m_pLabCountdown->setText(QString("%1���ʼ¼��").arg(CountdownNum));
	if (CountdownNum == 0)
	{
		// ��ֹ��ʱ��
		m_pTimer->stop();


		// ����ֵQDialog::Accepted�����رոô���
		this->accept();
		this->close();
	}
}