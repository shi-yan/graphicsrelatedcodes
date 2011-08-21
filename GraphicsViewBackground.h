#pragma once

#include <QtGui/QGraphicsView>
#include <QtGui/QResizeEvent>
#include <QtOpenGL/QGLWidget>

class GraphicsViewBackground:public QGraphicsView
{
	Q_OBJECT
public:
	QGLWidget *GLViewport;
    public:
		GraphicsViewBackground(QWidget *parent=0):QGraphicsView(parent),GLViewport(0)
        {
            setWindowTitle(tr("Pillow Modeller 2.0"));
				setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
			//setStickyFocus(true);
			GLViewport=new QGLWidget(QGLFormat(QGL::SampleBuffers));
			GLViewport->setAutoFillBackground(false);
			GLViewport->makeCurrent();
			setViewport(GLViewport);
			setStyleSheet(tr("QGraphicsView{border:none;}"));
        }

		~GraphicsViewBackground();
		void init();
    
    protected:
        void resizeEvent(QResizeEvent *event) 
		{
			if (scene())
			{
				scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
			}

            QGraphicsView::resizeEvent(event);
        }

	
};
