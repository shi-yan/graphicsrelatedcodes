#pragma once
#include <QtGui/QAction>

class DynamicAction:public QAction
{
	Q_OBJECT
public:
	DynamicAction(QObject *parent=0 );
	~DynamicAction(void);
signals:
	void triggered(QAction *);
	private slots:
		void onBaseTriggered();
};
