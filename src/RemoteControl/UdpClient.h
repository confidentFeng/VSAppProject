// UDP����������
#pragma once
#include <QUdpSocket>
#include "common.h"

typedef struct  stDirMsg
{
	char	pDirMsgHead[16];
	int		nMainType;
	int		nSubType;
	int		nMsgValue;
	int     nMsgDataLen;
	char	*pMsgData;
	char    pDirMsgTail[16];
}Dir_Msg_S;

class UdpClient : public QWidget
{
	Q_OBJECT

public:
	UdpClient();
	~UdpClient();
	static UdpClient *Get()
	{
		static UdpClient ct;
		return &ct;
	}
	void SendData(const int& type, const int& subType, const int& msgValue); // UDP��������

private:
	QUdpSocket *m_UdpSocket; // UDP�׽��ֶ���
	QString m_hostIP; // UDP������IP
	int m_hostPort; // UDP�˿ں�
};