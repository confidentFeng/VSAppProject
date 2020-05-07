
#ifndef MPVPLAYER_H
#define MPVPLAYER_H

#include <QMainWindow>
#include <QDebug>
#include <mpv\client.h> // MPV库头文件

// 添加mpv静态链接库
#pragma comment(lib,"mpv/libmpv.dll.a")

class MpvPlayer : public QWidget
{
	Q_OBJECT

public:
	MpvPlayer(QWidget *parent);
	virtual ~MpvPlayer();

	void create_mvpPlayer(QWidget *videoWin); // 创建mvpPlayer
	void setProperty(const QString &name, const QString &value); // 设置mpv属性
	QString getProperty(const QString &name) const; // 获得mpv属性
	int play(QString filename); // 播放视频

	bool isLive(); // 是否在直播

	private slots:
	void on_mpv_events(); // 这个槽函数由 wakeup()调用（通过mpv_events信号）

signals:
	void mpv_events(); // 触发on_mpv_events()槽函数的信号
	void mpv_palyStart(); // 播放开始的信号
	void mpv_palyEnd(); // 播放结束的信号

private:
	void handle_mpv_event(mpv_event *event); // 处理mpv事件

	mpv_handle *mpv;
	bool m_isLiveFlag; // 是否在直播的标志位
};

#endif // MPVPLAYER_H
