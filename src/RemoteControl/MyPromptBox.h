#pragma once
#include "common.h"

// ͼ��ö��
enum EnumIcon
{
	SuccessIcon,
	FailIcon,
	PromptIcon
};

class MyPromptBox : public QDialog
{
	Q_OBJECT

public:
	MyPromptBox(QDialog *parent = Q_NULLPTR);
	~MyPromptBox();
	void setLabInfo(const QString& strText, const EnumIcon enumIcon); // ������Ϣ��ǩ���ı�

private:
	void timerEvent(QTimerEvent *event); // ��ʱ���¼�������1���رմ���

	QLabel *m_pLabIcon; // ͼ���ǩ
	QLabel *m_pLabInfo; // ��Ϣ��ǩ]
};
