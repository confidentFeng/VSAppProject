#pragma once
#include "common.h"
#include <QMovie>

class LoadWin : public QDialog
{
	Q_OBJECT

public:
	LoadWin(QDialog *parent = Q_NULLPTR);
	~LoadWin();

private:
	QLabel *m_pLabGif; // gif±Í«©
};
