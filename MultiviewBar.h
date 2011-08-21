#pragma once
#include <QtGui/QWidget>

class MultiviewBar:public QWidget
{
		Q_OBJECT
private:
	bool isHorizontal;
	bool isPressed;
	int oldx;
	int oldy;

signals:
	void barDraged(int value);

public:
	MultiviewBar(bool _isHorizontal=true,QWidget * parent = 0, Qt::WindowFlags f = 0);
	~MultiviewBar(void);

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent *event);
	void paintEvent ( QPaintEvent * event );
	void enterEvent ( QEvent * event ) ;
	void leaveEvent ( QEvent * event );
};
