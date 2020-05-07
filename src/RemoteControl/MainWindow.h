#pragma once
#include <QTime>
#include <QStackedWidget>
#include "common.h"
#include "mpvplayer.h"
#include "UdpClient.h"
#include "HttpClient.h"
#include "InputRecInfo.h"
#include "BindHost.h"
#include "LockScreen.h"
#include "MyMessageBox.h"
#include "WirelessCon.h"
#include "LoadWin.h"
#include "BatteryItem.h"
#include "StackedWidget.h"

// ���ַ����ı����޸�Ϊ"utf-8"��������ʾ�����Լ�����http��Get��ʽ��������
#pragma execution_character_set("utf-8")

class MainWindow : public QDialog
{
	Q_OBJECT

public:
	MainWindow(QDialog *parent = Q_NULLPTR);
	~MainWindow();

protected:
	void showEvent(QShowEvent *event); // ���������Qt::FramelessWindowHint�����治������ˢ�µ�����
	void keyPressEvent(QKeyEvent *event); // ���̰����¼�:���ڰ�Alt+M���رճ���
	void timerEvent(QTimerEvent* event); // ��ʱ���¼�

private slots:
	/* ������ť-�ۺ��� */
	void NetSetSlot(); // �������õĲۺ���
	void SysSetSlot(); // ϵͳ���õĲۺ���
	void ShutdownSlot(); // �ػ��Ĳۺ���

	/* ������ť-�ۺ��� */
	void RecordSlot(); // ¼����Ƶ
	void PauseSlot(); // ��ͣ/�ָ�¼��
	void LockVGASlot(); // ����VGA�Ĳۺ���
	void LiveSlot(); // ֱ������/�رյĲۺ���
	void SwitchSlot(); // �Զ��л�����/�رյĲۺ���
	void TrackSlot(); // �Զ����ٿ���/�رյĲۺ���
	void LockScrSlot(); // �����Ĳۺ���
	void RecordTimeOutSlot(); // ¼�ƶ�ʱ����ʱ����

	void RecvUdpData(); // �������ݵĲۺ���
	void timeoutSlot(); // ��ʱ����ʱ�ۺ���������ʵʱ��ȡʱ���Ӳ������
	void WiredNetSlot(const QString &strCmdOut); // ��̫�����ۺ���
	void WifiNetSlot(const QString &strCmdOut); // wifi���ۺ���

signals:
	void PauseSignal(); // ��ͣ¼���ź�

private:
	void InitPowerMonitoring(); // ��ʼ�������ؼ�
	void InitNetwork(); // ��ʼ���������
	void updataWin(); // ���´���
	void CheckNet(); // ��ʱ�����̫����wifi����ȷ������ͼ��							

	/* �ӽ��� */
	QWidget *m_pWidgetTop; // �����ӽ���
	QWidget *m_pWidgetCenter; // �в��ӽ���
	QWidget *m_pWidgetBottom; // �в��ӽ���
	QWidget *m_pWidgetRecord; // Ϊ�˱���"¼�ư�ť"��"¼��ʱ��"����

	/* ��Ƶ����Frame���� */
	MpvPlayer *mpvPlayer; // mpv����������
	QFrame *m_pVedioFrame; // ��Ƶ����Frame����
	QWidget *m_pVideoWidget; // ��Ƶ����Widget����

	/* ���� */
	QLabel *m_pLabTime; // ʱ���ǩ
	QLabel *m_pLabIPText; // IP�ı���ǩ
	QLabel *m_pLabIP; // IP��ǩ
	QLabel *m_pLabHardDiskText; // Ӳ���ı���ǩ
	QLabel *m_pLabHardDisk; // Ӳ�̱�ǩ
	BatteryItem *m_pBatteryItem;  // ��ر�ǩ
	QPushButton *m_pBtnNetwork; // ���簴ť
	QPushButton *m_pBtnSysSet; // ϵͳ���ð�ť
	QPushButton *m_pBtnShutdown; // �ػ���ť

	/* ����� */
	QPushButton *m_pBtnReview; // �γ̻ع˰�ť
	QPushButton *m_pBtnSplitSet; // �������ð�ť
	QPushButton *m_pBtnOSD; // OSD��ť

	/* ���� */
	QPushButton *m_pBtnRecord; // ¼�ư�ť
	QLabel *m_pLabRecord; // ¼�Ƽ�ʱ��ǩ
	QPushButton *m_pBtnPause; // ��ͣ¼�ư�ť
	QPushButton *m_pBtnLockVGA; // ����VGA��ť
	QPushButton *m_pBtnLive; // ֱ����ť
	QPushButton *m_pBtnSwitch; // �л���ť
	QPushButton *m_pBtnTrack; // ���ٰ�ť
	QPushButton *m_pBtnLockScr; // ������ť

	/* ��־λ */
	bool m_isLive; // �Ƿ���ֱ���ı�־λ
	bool m_isRecord; // �Ƿ���¼�Ƶı�־λ
	bool m_isPause; // �Ƿ�����ͣ�ı�־λ
	bool m_isLockVGA; // �Ƿ�������VGA�ı�־λ
	bool m_isSwitch; // �Ƿ����Զ��л��ı�־λ
	bool m_isTrack; // �Ƿ����Զ����ٵı�־λ
	bool bHaveWired = false; // ��������wifi�ı�־λ
	bool m_bHaveWifi = false; // �����߲���ı�־λ

	/* ʱ�������ر��� */
	int m_recordTime = 0; // ¼��ʱ��
	QTime m_pTimeRecord; // ¼��ʱ�������
	QTimer *m_pTimerRecord; // ¼�ƶ�ʱ��
	QTimer *m_pSysTimer; // ϵͳʱ�䶨ʱ��
	int timeIDPower = -1; // ������ʱ��ID
	int timeIDNetCheck = -2; // �����ⶨʱ��ID
	int timeIDRecord = -3; // ¼��״̬��ⶨʱ��ID

	/* ������ر��� */
	QString m_hostIP; // ¼������IP
	QString m_httpAds; // http��ַ
	QString m_strFreeCap; // ����Ӳ������
	QString m_strTotalCap; // ��Ӳ������

	QUdpSocket *m_UdpSocket; // UDP�׽��ֶ���
};
