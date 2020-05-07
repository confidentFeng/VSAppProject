#include "common.h"

Common::Common()
{

}

Common::~Common()
{

}

// ÷¥––CMD√¸¡Ó
QString Common::ExecuteCmd2(const QString& strCmd)
{
	QProcess cmd;
	cmd.start(strCmd);
	cmd.waitForStarted();
	cmd.waitForFinished();
	return QString::fromLocal8Bit(cmd.readAllStandardOutput());
}
