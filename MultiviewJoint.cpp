#include "MultiviewJoint.h"
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>


MultiviewJoint::MultiviewJoint(QWidget * parent, Qt::WindowFlags f):QWidget(parent, f),oldx(0),oldy(0),isPressed(false)
{
}

MultiviewJoint::~MultiviewJoint(void)
{
}


void MultiviewJoint::mousePressEvent(QMouseEvent *event)
{
	isPressed=true;
	oldx=event->globalPos().x();
	oldy=event->globalPos().y();
	event->accept();

}

void MultiviewJoint::mouseMoveEvent(QMouseEvent * event)
{
	if(isPressed)
	{
		emit jointDraged(event->globalPos().x()-oldx,event->globalPos().y()-oldy);
		oldx=event->globalPos().x();
		oldy=event->globalPos().y();
	}
	event->accept();

}
	
void MultiviewJoint::mouseReleaseEvent(QMouseEvent *event)
{
	isPressed=false;
	oldx=0;
	oldy=0;
	event->accept();
	emit jointDragFinished();
}

void MultiviewJoint::paintEvent ( QPaintEvent * event )
{
	QPainter painter(this);
	painter.fillRect(QRect(0,0,size().width(),size().height()),QColor(222,230,221));
	painter.end();
}

void MultiviewJoint::enterEvent ( QEvent * event )
{
	setCursor(Qt::SizeAllCursor);
}

void MultiviewJoint::leaveEvent ( QEvent * event )
{
	setCursor(Qt::ArrowCursor);
}
