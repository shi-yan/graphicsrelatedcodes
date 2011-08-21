#pragma once
#include <QtGui/QDockWidget>

class CreateDialog:public QDockWidget
{
public:
	CreateDialog(QWidget *_parent=0);
	~CreateDialog(void);
};
