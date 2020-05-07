
#ifndef MPVPLAYER_H
#define MPVPLAYER_H

#include <QMainWindow>
#include <QDebug>
#include <mpv\client.h> // MPV��ͷ�ļ�

// ���mpv��̬���ӿ�
#pragma comment(lib,"mpv/libmpv.dll.a")

class MpvPlayer : public QWidget
{
	Q_OBJECT

public:
	MpvPlayer(QWidget *parent);
	virtual ~MpvPlayer();

	void create_mvpPlayer(QWidget *videoWin); // ����mvpPlayer
	void setProperty(const QString &name, const QString &value); // ����mpv����
	QString getProperty(const QString &name) const; // ���mpv����
	int play(QString filename); // ������Ƶ

	bool isLive(); // �Ƿ���ֱ��

	private slots:
	void on_mpv_events(); // ����ۺ����� wakeup()���ã�ͨ��mpv_events�źţ�

signals:
	void mpv_events(); // ����on_mpv_events()�ۺ������ź�
	void mpv_palyStart(); // ���ſ�ʼ���ź�
	void mpv_palyEnd(); // ���Ž������ź�

private:
	void handle_mpv_event(mpv_event *event); // ����mpv�¼�

	mpv_handle *mpv;
	bool m_isLiveFlag; // �Ƿ���ֱ���ı�־λ
};

#endif // MPVPLAYER_H
