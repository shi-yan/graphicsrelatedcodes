#pragma once
#include <QtGui/QWidget>

class MultiviewJoint:public QWidget
{
	Q_OBJECT
private:

	bool isPressed;
	int oldx;
	int oldy;


signals:
	void jointDraged(int x,int y);
	void jointDragFinished();


public:
	MultiviewJoint(QWidget * parent = 0, Qt::WindowFlags f = 0);
	~MultiviewJoint(void);

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent *event);
	void paintEvent ( QPaintEvent * event );
	void enterEvent ( QEvent * event ) ;
	void leaveEvent ( QEvent * event );
};
