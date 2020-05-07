#include "UdpClient.h"
#include <QNetworkInterface>

UdpClient::UdpClient()
{
	// ����UDP�׽��ֶ���
	m_UdpSocket = new QUdpSocket();
							
}

UdpClient::~UdpClient()
{
	
}

// UDP��������
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

	// ÿ�η��Ͷ���ȡ�����ļ����Է��л���¼����������m_hostIPû�и���
	QString iniFilePath = QApplication::applicationDirPath() + "/config.ini";
	QSettings *iniRead = new QSettings(iniFilePath, QSettings::IniFormat);
	m_hostIP = iniRead->value("hostIP").toString();
	m_hostPort = iniRead->value("hostPort").toInt();
	qDebug() << "hostIP: " << m_hostIP;
	qDebug() << "hostPort: " << m_hostPort;
	// ������ɺ�ɾ��ָ��
	delete iniRead;

	// �������ݵ��ƶ��ĵ�ַ�Ͷ˿ں�
	m_UdpSocket->writeDatagram(arrSendData, QHostAddress(m_hostIP), m_hostPort);
}
