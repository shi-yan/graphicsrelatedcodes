#pragma once
#include <QtGui/QPushButton>

class StatusbarButton:public QPushButton
{
public:
	StatusbarButton(QWidget *parent=0);
	~StatusbarButton(void);
};
