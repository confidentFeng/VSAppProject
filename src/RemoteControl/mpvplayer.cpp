#include "mpvplayer.h"

// 唤醒函数
static void wakeup(void *ctx)
{
	// 此回调可从任何mpv线程调用（但也可以从调用mpv API的线程递归地返回）
	// 只是需要通知要唤醒的Qt GUI线程（以便它可以使用mpv_wait_event（）），并尽快返回
	MpvPlayer *mvpPlayer = (MpvPlayer *)ctx;
	emit mvpPlayer->mpv_events();
}

MpvPlayer::MpvPlayer(QWidget *parent) :
	QWidget(parent)
{
	m_isLiveFlag = false;

	// 创建mvpPlayer
	create_mvpPlayer(parent);
}

MpvPlayer::~MpvPlayer()
{
	if (mpv)
		mpv_terminate_destroy(mpv);
}

// 创建mvpPlayer
void MpvPlayer::create_mvpPlayer(QWidget *videoWin)
{
	// 创建mpv实例
	mpv = mpv_create();
	if (!mpv)
		throw std::runtime_error("can't create mpv instance");

	// 将视频子窗口的窗口ID传递给mpv wid选项
	int64_t wid = videoWin->winId();
	mpv_set_option(mpv, "wid", MPV_FORMAT_INT64, &wid);

	// 使用低延迟配置(延时缩小到0.4秒左右)
	mpv_set_option_string(mpv, "profile", "low-latency");
	// 调整播放速度(因为拉流有延时和缓冲，所以要追赶播放)
	mpv_set_option_string(mpv, "speed", "1.05");
	// 是否启用硬件解码(默认开启，故这里可以注释掉)
	mpv_set_option_string(mpv, "hwdec", "yes");
	// 设置不计时(不需要音视频同步，就可以这样设置)
	mpv_set_option_string(mpv, "untimed", "yes");

	// 让我们通过MPV_EVENT_PROPERTY_CHANGE接收属性更改事件，如果这属性更改了
	mpv_observe_property(mpv, 0, "time-pos", MPV_FORMAT_DOUBLE);

	// 请求级别为"info"或更高级别的日志消息。它们以MPV_EVENT_LOG_MESSAGE的形式接收
	mpv_request_log_messages(mpv, "info");

	// 从这里开始，将调用唤醒功能。 回调可以来自任何线程，因此我们使用QueuedConnection机制以线程安全的方式中继唤醒
	connect(this, &MpvPlayer::mpv_events, this, &MpvPlayer::on_mpv_events,
		Qt::QueuedConnection);
	mpv_set_wakeup_callback(mpv, wakeup, this);

	// 判断mpv实例是否成功初始化
	if (mpv_initialize(mpv) < 0)
		throw std::runtime_error("mpv failed to initialize");
}

// 这个槽函数由 wakeup()调用（通过mpv_events信号）
void MpvPlayer::on_mpv_events()
{
	// 处理所有事件，直到事件队列为空
	while (mpv)
	{
		mpv_event *event = mpv_wait_event(mpv, 0);
		if (event->event_id == MPV_EVENT_NONE)
			break;
		handle_mpv_event(event);
	}
}

// 处理mpv事件
void MpvPlayer::handle_mpv_event(mpv_event *event)
{
	switch (event->event_id)
	{
		// 属性改变事件发生
	case MPV_EVENT_PROPERTY_CHANGE:
	{
		mpv_event_property *prop = (mpv_event_property *)event->data;

		if (strcmp(prop->name, "time-pos") == 0)
		{
			if (prop->format == MPV_FORMAT_DOUBLE)
			{
				// 获得播放时间
				//double time = *(double *)prop->data;
				//qDebug() << "time: " << QString::number(time, 10, 2);
			}
			else if (prop->format == MPV_FORMAT_NONE)
			{
				// 该属性不可用，可能意味着播放已停止
				emit mpv_palyEnd();
				qDebug() << "paly end!";
			}
		}
	}
	break;

	// log信息事件发生
	case MPV_EVENT_LOG_MESSAGE:
	{
		qDebug() << "play start";
		m_isLiveFlag = true;
		emit mpv_palyStart(); // 发射播放开始的信号

		struct mpv_event_log_message *msg = (struct mpv_event_log_message *)event->data;
		qDebug() << "[" << msg->prefix << "] " << msg->level << ": " << msg->text;
		break;
	}

	// palyer退出事件发生
	case MPV_EVENT_SHUTDOWN:
	{
		mpv_terminate_destroy(mpv);
		mpv = NULL;
	}
	break;

	default:;
	}
}

// 设置mpv属性
void MpvPlayer::setProperty(const QString &name, const QString &value)
{
	mpv_set_option_string(mpv, name.toLatin1().data(), value.toLatin1().data());
}

// 获得mpv属性
QString MpvPlayer::getProperty(const QString &name) const
{
	return (QString)mpv_get_property_string(mpv, name.toLatin1().data());
}

// 播放视频
int MpvPlayer::play(QString filename)
{
	if (mpv)
	{
		const QByteArray c_filename = filename.toUtf8();
		const char *args[] = { "loadfile", c_filename.data(), NULL };
		// 与mpv_command相同，但异步运行命令来避免阻塞，直到进程终止
		return mpv_command_async(mpv, 0, args);
	}

	return 0;
}

// 是否在直播
bool MpvPlayer::isLive()
{
	return m_isLiveFlag;
}