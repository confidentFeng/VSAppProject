#pragma once
#include "common.h"

// 图标枚举
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
	void setLabInfo(const QString& strText, const EnumIcon enumIcon); // 设置消息标签的文本

private:
	void timerEvent(QTimerEvent *event); // 定时器事件：用于1秒后关闭窗口

	QLabel *m_pLabIcon; // 图标标签
	QLabel *m_pLabInfo; // 消息标签]
};
