#include "common.h"

Common::Common()
{

}

Common::~Common()
{

}

// ִ��CMD����
QString Common::ExecuteCmd(const QString& strCmd)
{
	QProcess cmd;
	cmd.start(strCmd);
	cmd.waitForStarted();
	cmd.waitForFinished();
	return QString::fromLocal8Bit(cmd.readAllStandardOutput());
}
