#include "mpvplayer.h"

// ���Ѻ���
static void wakeup(void *ctx)
{
	// �˻ص��ɴ��κ�mpv�̵߳��ã���Ҳ���Դӵ���mpv API���̵߳ݹ�ط��أ�
	// ֻ����Ҫ֪ͨҪ���ѵ�Qt GUI�̣߳��Ա�������ʹ��mpv_wait_event�������������췵��
	MpvPlayer *mvpPlayer = (MpvPlayer *)ctx;
	emit mvpPlayer->mpv_events();
}

MpvPlayer::MpvPlayer(QWidget *parent) :
	QWidget(parent)
{
	m_isLiveFlag = false;

	// ����mvpPlayer
	create_mvpPlayer(parent);
}

MpvPlayer::~MpvPlayer()
{
	if (mpv)
		mpv_terminate_destroy(mpv);
}

// ����mvpPlayer
void MpvPlayer::create_mvpPlayer(QWidget *videoWin)
{
	// ����mpvʵ��
	mpv = mpv_create();
	if (!mpv)
		throw std::runtime_error("can't create mpv instance");

	// ����Ƶ�Ӵ��ڵĴ���ID���ݸ�mpv widѡ��
	int64_t wid = videoWin->winId();
	mpv_set_option(mpv, "wid", MPV_FORMAT_INT64, &wid);

	// ʹ�õ��ӳ�����(��ʱ��С��0.4������)
	mpv_set_option_string(mpv, "profile", "low-latency");
	// ���������ٶ�(��Ϊ��������ʱ�ͻ��壬����Ҫ׷�ϲ���)
	mpv_set_option_string(mpv, "speed", "1.05");
	// �Ƿ�����Ӳ������(Ĭ�Ͽ��������������ע�͵�)
	mpv_set_option_string(mpv, "hwdec", "yes");
	// ���ò���ʱ(����Ҫ����Ƶͬ�����Ϳ�����������)
	mpv_set_option_string(mpv, "untimed", "yes");

	// ������ͨ��MPV_EVENT_PROPERTY_CHANGE�������Ը����¼�����������Ը�����
	mpv_observe_property(mpv, 0, "time-pos", MPV_FORMAT_DOUBLE);

	// ���󼶱�Ϊ"info"����߼������־��Ϣ��������MPV_EVENT_LOG_MESSAGE����ʽ����
	mpv_request_log_messages(mpv, "info");

	// �����￪ʼ�������û��ѹ��ܡ� �ص����������κ��̣߳��������ʹ��QueuedConnection�������̰߳�ȫ�ķ�ʽ�м̻���
	connect(this, &MpvPlayer::mpv_events, this, &MpvPlayer::on_mpv_events,
		Qt::QueuedConnection);
	mpv_set_wakeup_callback(mpv, wakeup, this);

	// �ж�mpvʵ���Ƿ�ɹ���ʼ��
	if (mpv_initialize(mpv) < 0)
		throw std::runtime_error("mpv failed to initialize");
}

// ����ۺ����� wakeup()���ã�ͨ��mpv_events�źţ�
void MpvPlayer::on_mpv_events()
{
	// ���������¼���ֱ���¼�����Ϊ��
	while (mpv)
	{
		mpv_event *event = mpv_wait_event(mpv, 0);
		if (event->event_id == MPV_EVENT_NONE)
			break;
		handle_mpv_event(event);
	}
}

// ����mpv�¼�
void MpvPlayer::handle_mpv_event(mpv_event *event)
{
	switch (event->event_id)
	{
		// ���Ըı��¼�����
	case MPV_EVENT_PROPERTY_CHANGE:
	{
		mpv_event_property *prop = (mpv_event_property *)event->data;

		if (strcmp(prop->name, "time-pos") == 0)
		{
			if (prop->format == MPV_FORMAT_DOUBLE)
			{
				// ��ò���ʱ��
				//double time = *(double *)prop->data;
				//qDebug() << "time: " << QString::number(time, 10, 2);
			}
			else if (prop->format == MPV_FORMAT_NONE)
			{
				// �����Բ����ã�������ζ�Ų�����ֹͣ
				emit mpv_palyEnd();
				qDebug() << "paly end!";
			}
		}
	}
	break;

	// log��Ϣ�¼�����
	case MPV_EVENT_LOG_MESSAGE:
	{
		qDebug() << "play start";
		m_isLiveFlag = true;
		emit mpv_palyStart(); // ���䲥�ſ�ʼ���ź�

		struct mpv_event_log_message *msg = (struct mpv_event_log_message *)event->data;
		qDebug() << "[" << msg->prefix << "] " << msg->level << ": " << msg->text;
		break;
	}

	// palyer�˳��¼�����
	case MPV_EVENT_SHUTDOWN:
	{
		mpv_terminate_destroy(mpv);
		mpv = NULL;
	}
	break;

	default:;
	}
}

// ����mpv����
void MpvPlayer::setProperty(const QString &name, const QString &value)
{
	mpv_set_option_string(mpv, name.toLatin1().data(), value.toLatin1().data());
}

// ���mpv����
QString MpvPlayer::getProperty(const QString &name) const
{
	return (QString)mpv_get_property_string(mpv, name.toLatin1().data());
}

// ������Ƶ
int MpvPlayer::play(QString filename)
{
	if (mpv)
	{
		const QByteArray c_filename = filename.toUtf8();
		const char *args[] = { "loadfile", c_filename.data(), NULL };
		// ��mpv_command��ͬ�����첽��������������������ֱ��������ֹ
		return mpv_command_async(mpv, 0, args);
	}

	return 0;
}

// �Ƿ���ֱ��
bool MpvPlayer::isLive()
{
	return m_isLiveFlag;
}