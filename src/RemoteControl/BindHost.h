#pragma once
#include <QRegExpValidator>
#include "common.h"
#include "HttpClient.h"
#include "MyMessageBox.h"
#include "MyPromptBox.h"

class BindHost : public QDialog
{
	Q_OBJECT

public:
	BindHost(QDialog *parent = Q_NULLPTR);
	~BindHost();
	void IsFirstOpen(bool isFirstFlag = false); // �Ƿ���ʾ�رհ�ť
	void SetHostIP(QString hostIP); // ����¼������IP
	void SetHostPort(int hostPort); // ����¼�������˿ں�
	void SetHostAccount(QString hostAccount); // ����¼�������˺�
	void SetHostPasswd(QString hostPasswd); // ����¼����������
	QString GetHostIP(); // ���¼������IP
	int GetHostPort(); // ���¼�������˿ں�
	QString GetHostAccount(); // ���¼�������˺�
	QString GetHostPasswd(); // ���¼����������

signals:
	void BtnReturnClicked(); // ���ذ�ť�ĵ���ź�
	void BtnSaveClicked(); // ���水ť�ĵ���ź�

private slots:
	void CloseSlot(); // �رղۺ���
	void ReturnSlot(); // ���زۺ���
	void SaveSlot(); // ���ñ���ۺ���
	void UseSlot(); // ʹ��˵���ۺ���

	void timeoutSlot(); // ��ʱ����ʱ�ۺ���

private:
	void keyPressEvent(QKeyEvent *event); // ���̰����¼��������Esc�������˳�������

	/* ����ҳ�� */
	QWidget *m_pWidgetCfgPage; // ����ҳ��

	/* ���� */
	QLabel *m_pLabTitle; // �����ǩ
	QPushButton *m_pBtnClose; // �رհ�ť

	/* �в����� */
	QLabel *m_pLabIP; // ¼������IP��ǩ
	QLineEdit *m_pEditIP; // ¼������IP�ı���
	QLabel *m_pLabPort; // ¼�������˿ںű�ǩ
	QLineEdit *m_pEditPort; // ¼�������˿ں��ı���
	QLabel *m_pLabAccount; // ¼�������˺ű�ǩ
	QLineEdit *m_pEditAccount; // ¼�������˺��ı���
	QLabel *m_pLabPasswd; // ¼�����������ǩ
	QLineEdit *m_pEditPasswd; // ¼�����������ı���

	/* ���� */
	QPushButton *m_pBtnReturn; // ���ذ�ť
	QPushButton *m_pBtnCfgSave; // ���ñ��水ť
	QPushButton *m_pBtnUse; // ʹ��˵����ť

	QString strReturn;

	QTimer *m_pHttpTimer; // http��ʱ��
};
