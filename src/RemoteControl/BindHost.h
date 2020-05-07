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
	void IsFirstOpen(bool isFirstFlag = false); // 是否显示关闭按钮
	void SetHostIP(QString hostIP); // 设置录播主机IP
	void SetHostPort(int hostPort); // 设置录播主机端口号
	void SetHostAccount(QString hostAccount); // 设置录播主机账号
	void SetHostPasswd(QString hostPasswd); // 设置录播主机密码
	QString GetHostIP(); // 获得录播主机IP
	int GetHostPort(); // 获得录播主机端口号
	QString GetHostAccount(); // 获得录播主机账号
	QString GetHostPasswd(); // 获得录播主机密码

signals:
	void BtnReturnClicked(); // 返回按钮的点击信号
	void BtnSaveClicked(); // 保存按钮的点击信号

private slots:
	void CloseSlot(); // 关闭槽函数
	void ReturnSlot(); // 返回槽函数
	void SaveSlot(); // 配置保存槽函数
	void UseSlot(); // 使用说明槽函数

	void timeoutSlot(); // 定时器超时槽函数

private:
	void keyPressEvent(QKeyEvent *event); // 键盘按下事件：解决按Esc键窗口退出的问题

	/* 配置页面 */
	QWidget *m_pWidgetCfgPage; // 配置页面

	/* 顶栏 */
	QLabel *m_pLabTitle; // 标题标签
	QPushButton *m_pBtnClose; // 关闭按钮

	/* 中部窗口 */
	QLabel *m_pLabIP; // 录播主机IP标签
	QLineEdit *m_pEditIP; // 录播主机IP文本框
	QLabel *m_pLabPort; // 录播主机端口号标签
	QLineEdit *m_pEditPort; // 录播主机端口号文本框
	QLabel *m_pLabAccount; // 录播主机账号标签
	QLineEdit *m_pEditAccount; // 录播主机账号文本框
	QLabel *m_pLabPasswd; // 录播主机密码标签
	QLineEdit *m_pEditPasswd; // 录播主机密码文本框

	/* 底栏 */
	QPushButton *m_pBtnReturn; // 返回按钮
	QPushButton *m_pBtnCfgSave; // 配置保存按钮
	QPushButton *m_pBtnUse; // 使用说明按钮

	QString strReturn;

	QTimer *m_pHttpTimer; // http定时器
};
