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

// 将字符串的编码修改为"utf-8"，便于显示中文以及允许http的Get方式传输中文
#pragma execution_character_set("utf-8")

class MainWindow : public QDialog
{
	Q_OBJECT

public:
	MainWindow(QDialog *parent = Q_NULLPTR);
	~MainWindow();

protected:
	void showEvent(QShowEvent *event); // 解决设置了Qt::FramelessWindowHint，界面不能自主刷新的问题
	void keyPressEvent(QKeyEvent *event); // 键盘按下事件:用于按Alt+M键关闭程序
	void timerEvent(QTimerEvent* event); // 定时器事件

private slots:
	/* 顶栏按钮-槽函数 */
	void NetSetSlot(); // 网络设置的槽函数
	void SysSetSlot(); // 系统设置的槽函数
	void ShutdownSlot(); // 关机的槽函数

	/* 底栏按钮-槽函数 */
	void RecordSlot(); // 录制视频
	void PauseSlot(); // 暂停/恢复录制
	void LockVGASlot(); // 锁定VGA的槽函数
	void LiveSlot(); // 直播开启/关闭的槽函数
	void SwitchSlot(); // 自动切换开启/关闭的槽函数
	void TrackSlot(); // 自动跟踪开启/关闭的槽函数
	void LockScrSlot(); // 锁屏的槽函数
	void RecordTimeOutSlot(); // 录制定时器超时函数

	void RecvUdpData(); // 接收数据的槽函数
	void timeoutSlot(); // 定时器超时槽函数：用于实时获取时间和硬盘容量
	void WiredNetSlot(const QString &strCmdOut); // 以太网检测槽函数
	void WifiNetSlot(const QString &strCmdOut); // wifi检测槽函数

signals:
	void PauseSignal(); // 暂停录制信号

private:
	void InitPowerMonitoring(); // 初始化电量控件
	void InitNetwork(); // 初始化网络相关
	void updataWin(); // 更新窗口
	void CheckNet(); // 定时检查以太网和wifi，已确定网络图标							

	/* 子界面 */
	QWidget *m_pWidgetTop; // 顶部子界面
	QWidget *m_pWidgetCenter; // 中部子界面
	QWidget *m_pWidgetBottom; // 中部子界面
	QWidget *m_pWidgetRecord; // 为了保持"录制按钮"与"录制时间"对齐

	/* 视频播放Frame窗口 */
	MpvPlayer *mpvPlayer; // mpv播放器对象
	QFrame *m_pVedioFrame; // 视频播放Frame窗口
	QWidget *m_pVideoWidget; // 视频播放Widget窗口

	/* 顶栏 */
	QLabel *m_pLabTime; // 时间标签
	QLabel *m_pLabIPText; // IP文本标签
	QLabel *m_pLabIP; // IP标签
	QLabel *m_pLabHardDiskText; // 硬盘文本标签
	QLabel *m_pLabHardDisk; // 硬盘标签
	BatteryItem *m_pBatteryItem;  // 电池标签
	QPushButton *m_pBtnNetwork; // 网络按钮
	QPushButton *m_pBtnSysSet; // 系统设置按钮
	QPushButton *m_pBtnShutdown; // 关机按钮

	/* 侧边栏 */
	QPushButton *m_pBtnReview; // 课程回顾按钮
	QPushButton *m_pBtnSplitSet; // 分屏设置按钮
	QPushButton *m_pBtnOSD; // OSD按钮

	/* 底栏 */
	QPushButton *m_pBtnRecord; // 录制按钮
	QLabel *m_pLabRecord; // 录制计时标签
	QPushButton *m_pBtnPause; // 暂停录制按钮
	QPushButton *m_pBtnLockVGA; // 锁定VGA按钮
	QPushButton *m_pBtnLive; // 直播按钮
	QPushButton *m_pBtnSwitch; // 切换按钮
	QPushButton *m_pBtnTrack; // 跟踪按钮
	QPushButton *m_pBtnLockScr; // 锁屏按钮

	/* 标志位 */
	bool m_isLive; // 是否在直播的标志位
	bool m_isRecord; // 是否在录制的标志位
	bool m_isPause; // 是否在暂停的标志位
	bool m_isLockVGA; // 是否已锁定VGA的标志位
	bool m_isSwitch; // 是否已自动切换的标志位
	bool m_isTrack; // 是否已自动跟踪的标志位
	bool bHaveWired = false; // 有已连接wifi的标志位
	bool m_bHaveWifi = false; // 有网线插入的标志位

	/* 时间控制相关变量 */
	int m_recordTime = 0; // 录制时间
	QTime m_pTimeRecord; // 录制时间类对象
	QTimer *m_pTimerRecord; // 录制定时器
	QTimer *m_pSysTimer; // 系统时间定时器
	int timeIDPower = -1; // 电量定时器ID
	int timeIDNetCheck = -2; // 网络检测定时器ID
	int timeIDRecord = -3; // 录制状态检测定时器ID

	/* 配置相关变量 */
	QString m_hostIP; // 录播主机IP
	QString m_httpAds; // http地址
	QString m_strFreeCap; // 可用硬盘容量
	QString m_strTotalCap; // 总硬盘容量

	QUdpSocket *m_UdpSocket; // UDP套接字对象
};
