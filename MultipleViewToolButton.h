#pragma once
#include <QtGui/QPushButton>

class MultipleViewToolButton:public QPushButton
{
	Q_OBJECT
public:
	MultipleViewToolButton(QWidget *parent=0);
	~MultipleViewToolButton(void);

void paintEvent(QPaintEvent *);
};
