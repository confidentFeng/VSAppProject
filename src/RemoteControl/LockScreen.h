#pragma once
#include <QRegExpValidator>
#include "common.h"
#include "MyPromptBox.h"

class LockScreen : public QWidget
{
	Q_OBJECT

public:
	LockScreen(QWidget *parent = Q_NULLPTR);
	~LockScreen();

private slots:
	void EnterSlot(); // �ı���س�����Ӧ�Ĳۺ���

private:
	QWidget *m_pWidgetChild; // �ӽ���
	QLabel *m_pLabHead; // ͷ���ǩ
	QLabel *m_pLabAccount; // ¼�������˺ű�ǩ
	QLineEdit *m_pEditPasswd; // ¼�����������ı���
};
