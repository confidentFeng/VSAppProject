#include "CmdThread.h"

CmdThread::CmdThread(QString strCmd)
{
	m_strCmd = strCmd;
}

CmdThread::~CmdThread()
{
	// ������ֹ
	requestInterruption();
	quit();
	wait();
}
