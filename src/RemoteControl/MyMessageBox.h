#pragma once
#include "common.h"

// ���ַ����ı����޸�Ϊ"utf-8"��������ʾ�����Լ�����http��Get��ʽ��������
#pragma execution_character_set("utf-8")

class MyMessageBox : public QDialog
{
	Q_OBJECT

public:
	MyMessageBox(QDialog *parent = Q_NULLPTR);
	~MyMessageBox();

	void SetTitleText(const QString &strTitle); // ���ñ����ǩ���ı�
	void SetInfoText(const QString &strText); // ������Ϣ��ǩ���ı�
	void ShowControl(bool isShowIconFlag, bool isShowOKFlag = true, const QString& strText = ""); // ��ʾ���ƺ���

private slots:
	void CloseSlot(); // �رհ�ť�ۺ���
	void OKSlot(); // ȷ����ť�ۺ���

private:
	void Init(); // ��ʼ������

	QWidget *m_pWidgetChild; // �ӽ���
	QLabel *m_pLabTitle; // �����ǩ
	QPushButton *m_pBtnClose; // �رհ�ť
	QLabel *m_pLabInco; // ͼ���ǩ
	QLabel *m_pLabInfo; // ��Ϣ��ǩ
	QPushButton *m_pBtnOK; // ȷ����ť
	QPushButton *m_pBtnCancel; // ȡ����ť
};
