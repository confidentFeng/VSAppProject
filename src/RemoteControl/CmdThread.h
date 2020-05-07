#pragma once
#include "common.h"
#include "MyPromptBox.h"
#include <QThread>

class CmdThread : public QThread
{
	Q_OBJECT

public:
	CmdThread(QString strCmd);
	~CmdThread();

protected:
	virtual void run() Q_DECL_OVERRIDE
	{
		QProcess cmd;
		cmd.start(m_strCmd);
		cmd.waitForStarted();
		cmd.waitForFinished();
		emit resultReady(QString::fromLocal8Bit(cmd.readAllStandardOutput()));

		// ִ����һ������󣬾�������ֹ
		requestInterruption();
		quit();
		wait();
	}

signals:
	void resultReady(const QString &strCmdOut);

private:
	QString m_strCmd;
};
