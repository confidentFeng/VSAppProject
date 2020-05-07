#include "LoadWin.h"

LoadWin::LoadWin(QDialog *parent)
	: QDialog(parent)
{
	/* �������ý���-��ʼ�� */
	this->setFixedSize(800, 800);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);"));

	/* gif��ǩ-��ʼ�� */
	QMovie *pMovie = new QMovie(":/MainWindow/image/videoSwitch.gif");
	m_pLabGif = new QLabel(this);
	m_pLabGif->setFixedSize(400, 400);
	m_pLabGif->setScaledContents(true);
	m_pLabGif->setMovie(pMovie);
	pMovie->start();
}

LoadWin::~LoadWin()
{

}