#include "CmdThread.h"

CmdThread::CmdThread(QString strCmd)
{
	m_strCmd = strCmd;
}

CmdThread::~CmdThread()
{
	// «Î«Û÷’÷π
	requestInterruption();
	quit();
	wait();
}
