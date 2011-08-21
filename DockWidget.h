#pragma once
#include <QtGui/QDockWidget>



class DockWidget:public QDockWidget
{
	Q_OBJECT
public:
        DockWidget(const QString &title,QWidget *parent);


	~DockWidget(void);
};
