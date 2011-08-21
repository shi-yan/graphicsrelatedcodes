#include "MultiviewBar.h"
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <iostream>

MultiviewBar::MultiviewBar(bool _isHorizontal,QWidget * parent, Qt::WindowFlags f):QWidget(parent,f),isHorizontal(_isHorizontal),oldx(0),oldy(0)
{
}

MultiviewBar::~MultiviewBar(void)
{
}

void MultiviewBar::mousePressEvent(QMouseEvent *event)
{
	isPressed=true;
	oldx=event->globalPos().x();
	oldy=event->globalPos().y();
	event->accept();

};

void MultiviewBar::mouseMoveEvent(QMouseEvent * event)
{
	if(isPressed)
	{
		if(isHorizontal)
		{
			emit barDraged(event->globalPos().y()-oldy);
		}
		else
		{
			emit barDraged(event->globalPos().x()-oldx);
		}

		oldx=event->globalPos().x();
		oldy=event->globalPos().y();
		event->accept();

	}
};

	void MultiviewBar::enterEvent ( QEvent * event ) 
	{
		if(isHorizontal)
			setCursor(Qt::SplitVCursor);
		else
			setCursor(Qt::SplitHCursor);
		event->accept();

	}

	void MultiviewBar::leaveEvent ( QEvent * event )
	{
		setCursor(Qt::ArrowCursor);
		event->accept();

	}

void MultiviewBar::mouseReleaseEvent(QMouseEvent *event)
{
	isPressed=false;
	oldx=0;
	oldy=0;
	event->accept();

};

void MultiviewBar::paintEvent ( QPaintEvent * event )
{
	QPainter painter(this);
	painter.fillRect(QRect(0,0,size().width(),size().height()),QColor(223,230,221));
	//painter.fillRect(QRect(0,0,size().width(),size().height()),QColor(255,0,0));
	painter.end();
}