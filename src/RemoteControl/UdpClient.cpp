#include "UdpClient.h"
#include <QNetworkInterface>

UdpClient::UdpClient()
{
	// 创建UDP套接字对象
	m_UdpSocket = new QUdpSocket();
							
}

UdpClient::~UdpClient()
{
	
}

// UDP发送数据
void UdpClient::SendData(const int& type, const int& subType, const int &msgValue)
{
	stDirMsg stSendMsg;
	strncpy(stSendMsg.pDirMsgHead, "**Head**ROCPOW**", 16);
	stSendMsg.nMainType = type;
	stSendMsg.nSubType = subType;
	stSendMsg.nMsgValue = msgValue;
	stSendMsg.nMsgDataLen = 0;
	stSendMsg.pMsgData = NULL;
	strncpy(stSendMsg.pDirMsgTail, "**ROCPOW**Tail**", 16);
	QByteArray arrSendData;
	arrSendData.append((char*)&stSendMsg, sizeof(stSendMsg));

	// 每次发送都读取配置文件，以防切换了录播主机，而m_hostIP没有更新
	QString iniFilePath = QApplication::applicationDirPath() + "/config.ini";
	QSettings *iniRead = new QSettings(iniFilePath, QSettings::IniFormat);
	m_hostIP = iniRead->value("hostIP").toString();
	m_hostPort = iniRead->value("hostPort").toInt();
	qDebug() << "hostIP: " << m_hostIP;
	qDebug() << "hostPort: " << m_hostPort;
	// 读入完成后删除指针
	delete iniRead;

	// 发送数据到制定的地址和端口号
	m_UdpSocket->writeDatagram(arrSendData, QHostAddress(m_hostIP), m_hostPort);
}
