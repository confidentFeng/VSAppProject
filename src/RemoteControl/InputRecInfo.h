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
	void CloseSlot(); // 关闭槽函数
	void SaveSlot(); // 保存槽函数
	void onTimeOut(); // 超时槽函数

private:
	void keyPressEvent(QKeyEvent *event); // 键盘按下事件：解决按Esc键窗口退出的问题
	void CallKeyBoard(); // 调用小键盘
	bool eventFilter(QObject *watched, QEvent *event); // 事件过滤器函数重写

	QWidget *m_pWidgetChild; // 子界面
	QLabel *m_pLabTitle; // 标题标签
	QPushButton *m_pBtnClose; // 关闭按钮
	QLabel *m_pLabPresenter; // 主讲人标签
	QLineEdit *m_pEditPresenter; // 主讲人文本框
	QLabel *m_pLabSubject; // 课题标签
	QLineEdit *m_pEditSubject; // 课题文本框
	QPushButton *m_pBtnSave; // 保存按钮
	QPushButton *m_pBtnCancel; // 取消按钮
	QLabel *m_pLabCountdown; // 倒计时标签

	QTimer *m_pTimer; // 定时器
	int CountdownNum = 3; // 倒计时秒数
};
