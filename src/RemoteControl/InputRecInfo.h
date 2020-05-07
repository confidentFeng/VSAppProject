#pragma once
#include <windows.h>
#include <QRegExpValidator>
#include "common.h"
#include "HttpClient.h"
#include "MyPromptBox.h"

class InputRecInfo : public QDialog
{
	Q_OBJECT

public:
	InputRecInfo(QDialog *parent = Q_NULLPTR);
	~InputRecInfo();

private slots:
	void CloseSlot(); // �رղۺ���
	void SaveSlot(); // ����ۺ���
	void onTimeOut(); // ��ʱ�ۺ���

private:
	void keyPressEvent(QKeyEvent *event); // ���̰����¼��������Esc�������˳�������
	void CallKeyBoard(); // ����С����
	bool eventFilter(QObject *watched, QEvent *event); // �¼�������������д

	QWidget *m_pWidgetChild; // �ӽ���
	QLabel *m_pLabTitle; // �����ǩ
	QPushButton *m_pBtnClose; // �رհ�ť
	QLabel *m_pLabPresenter; // �����˱�ǩ
	QLineEdit *m_pEditPresenter; // �������ı���
	QLabel *m_pLabSubject; // �����ǩ
	QLineEdit *m_pEditSubject; // �����ı���
	QPushButton *m_pBtnSave; // ���水ť
	QPushButton *m_pBtnCancel; // ȡ����ť
	QLabel *m_pLabCountdown; // ����ʱ��ǩ

	QTimer *m_pTimer; // ��ʱ��
	int CountdownNum = 3; // ����ʱ����
};
