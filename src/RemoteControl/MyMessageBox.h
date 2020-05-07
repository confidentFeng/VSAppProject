#pragma once
#include "common.h"

// 将字符串的编码修改为"utf-8"，便于显示中文以及允许http的Get方式传输中文
#pragma execution_character_set("utf-8")

class MyMessageBox : public QDialog
{
	Q_OBJECT

public:
	MyMessageBox(QDialog *parent = Q_NULLPTR);
	~MyMessageBox();

	void SetTitleText(const QString &strTitle); // 设置标题标签的文本
	void SetInfoText(const QString &strText); // 设置消息标签的文本
	void ShowControl(bool isShowIconFlag, bool isShowOKFlag = true, const QString& strText = ""); // 显示控制函数

private slots:
	void CloseSlot(); // 关闭按钮槽函数
	void OKSlot(); // 确定按钮槽函数

private:
	void Init(); // 初始化函数

	QWidget *m_pWidgetChild; // 子界面
	QLabel *m_pLabTitle; // 标题标签
	QPushButton *m_pBtnClose; // 关闭按钮
	QLabel *m_pLabInco; // 图标标签
	QLabel *m_pLabInfo; // 消息标签
	QPushButton *m_pBtnOK; // 确定按钮
	QPushButton *m_pBtnCancel; // 取消按钮
};
