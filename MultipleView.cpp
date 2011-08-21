
#include <GL/glew.h>
#include "MultipleView.h"

#include <QtGui/QPainter>
#include <QtGui/QResizeEvent>
#include <iostream>
#include <QtGui/QApplication>
#include "GLCanvas.h"
#include "CoordinateGrid.h"
#include "Scene.h"
#include <QtGui/QPaintEngine>
#include <QtGui/QGraphicsItem>

#include <QtGui/QGraphicsProxyWidget>

#include "UserCameraManager.h"

static bool initialized=false;

MultipleView::MultipleView(QWidget * parent):QGraphicsScene(parent),x(-1),y(-1),layout(Four),oldWidth(-1),oldHeight(-1),currentCanvas(0)
{
	

	for(int i=0;i<4;++i)
	{
		widgets[i]=0;
		widgetProxies[i]=0;
	}

	setStickyFocus(true);
	setSceneRect(QRectF(0,0,800,600));
	joint=new MultiviewJoint();
	left=new MultiviewBar(true);
	right=new MultiviewBar(true);
	down=new MultiviewBar(false);
	up=new MultiviewBar(false);

	objectLevelSelectButton=new MultipleViewToolButton();
	objectLevelSelectButton->setCursor(QCursor(Qt::PointingHandCursor));
	objectLevelSelectButton->setGeometry(29,29,29,29);
	objectLevelSelectButton->setText("");

	QIcon iconObjectLevel;
	iconObjectLevel.addPixmap(QPixmap(QString::fromUtf8("ObjectLevelIcon.png")), QIcon::Normal, QIcon::On);
	objectLevelSelectButton->setIcon(iconObjectLevel);
	objectLevelSelectButton->setCheckable(true);
	objectLevelSelectButton->setChecked(false);
	
	facetLevelSelectButton=new MultipleViewToolButton();
	facetLevelSelectButton->setCursor(QCursor(Qt::PointingHandCursor));
	facetLevelSelectButton->setGeometry(29,29,29,29);
	facetLevelSelectButton->setText("");
	
	QIcon iconFacetLevel;    
	iconFacetLevel.addPixmap(QPixmap(QString::fromUtf8("FacetLevelIcon.png")), QIcon::Normal, QIcon::On);   
	facetLevelSelectButton->setIcon(iconFacetLevel);    
	facetLevelSelectButton->setCheckable(true);
	facetLevelSelectButton->setChecked(false);
	
	edgeLevelSelectButton=new MultipleViewToolButton();
	edgeLevelSelectButton->setCursor(QCursor(Qt::PointingHandCursor));
	edgeLevelSelectButton->setGeometry(29,29,29,29);
	edgeLevelSelectButton->setText("");
		
	QIcon iconEdgeLevel;
	iconEdgeLevel.addPixmap(QPixmap(QString::fromUtf8("EdgeLevelIcon.png")), QIcon::Normal, QIcon::On);
	edgeLevelSelectButton->setIcon(iconEdgeLevel);
	edgeLevelSelectButton->setCheckable(true);
	edgeLevelSelectButton->setChecked(false);

	pointLevelSelectButton=new MultipleViewToolButton();
	pointLevelSelectButton->setCursor(QCursor(Qt::PointingHandCursor));
	pointLevelSelectButton->setGeometry(29,29,29,29);
	pointLevelSelectButton->setText("");

	QIcon iconPointLevel;
	iconPointLevel.addPixmap(QPixmap(QString::fromUtf8("PointLevelIcon.png")), QIcon::Normal, QIcon::On);
	pointLevelSelectButton->setIcon(iconPointLevel);
	pointLevelSelectButton->setCheckable(true);
	pointLevelSelectButton->setChecked(false);

	fourButton=new MultipleViewToolButton();
	fourButton->setCursor(QCursor(Qt::PointingHandCursor));
	fourButton->setGeometry(29,29,29,29);
	fourButton->setText("");

	QIcon iconFour;
	iconFour.addPixmap(QPixmap(QString::fromUtf8("FourIcon.png")), QIcon::Normal, QIcon::On);
	fourButton->setIcon(iconFour);
	fourButton->setCheckable(true);	
	fourButton->setChecked(false);
	 
	threeButton=new MultipleViewToolButton();
	threeButton->setCursor(QCursor(Qt::PointingHandCursor));
	threeButton->setGeometry(29,29,29,29);
	threeButton->setText("");

	QIcon iconThree;
	iconThree.addPixmap(QPixmap(QString::fromUtf8("ThreeIcon.png")), QIcon::Normal, QIcon::On);
	threeButton->setIcon(iconThree);
	threeButton->setCheckable(true);
	threeButton->setChecked(false);
	 
	twoButton=new MultipleViewToolButton();
	twoButton->setCursor(QCursor(Qt::PointingHandCursor));
	twoButton->setGeometry(29,29,29,29);
	twoButton->setText("");

	QIcon iconTwo;
	iconTwo.addPixmap(QPixmap(QString::fromUtf8("TwoIcon.png")), QIcon::Normal, QIcon::On);
	twoButton->setIcon(iconTwo);
	twoButton->setChecked(false);
	twoButton->setCheckable(true);

	singleButton=new MultipleViewToolButton();	
	singleButton->setCursor(QCursor(Qt::PointingHandCursor));
	singleButton->setGeometry(29,29,29,29);
	singleButton->setText("");
	 
	QIcon iconSingle;
	iconSingle.addPixmap(QPixmap(QString::fromUtf8("SingleIcon.png")), QIcon::Normal, QIcon::On);
	singleButton->setIcon(iconSingle);
	singleButton->setCheckable(true);
	singleButton->setChecked(false);

	connect(left,SIGNAL(barDraged(int)),this,SLOT(leftDraged(int)));
	connect(right,SIGNAL(barDraged(int)),this,SLOT(rightDraged(int)));
	connect(up,SIGNAL(barDraged(int)),this,SLOT(upDraged(int)));
	connect(down,SIGNAL(barDraged(int)),this,SLOT(downDraged(int)));
	connect(joint,SIGNAL(jointDraged(int,int)),this,SLOT(jointDraged(int,int)));

	connect(fourButton,SIGNAL(clicked()),this,SLOT(fourButtonClicked()));
	connect(threeButton,SIGNAL(clicked()),this,SLOT(threeButtonClicked()));
	connect(twoButton,SIGNAL(clicked()),this,SLOT(twoButtonClicked()));
	connect(singleButton,SIGNAL(clicked()),this,SLOT(singleButtonClicked()));

	for(int i=0;i<4;++i)
		widgets[i]=0;
	
	QGraphicsProxyWidget *pw=addWidget(joint);
	pw->setZValue(5);

        /*pw=addWidget(up);
	pw->setZValue(5);

	pw=addWidget(down);
	pw->setZValue(5);

	pw=addWidget(right);
	pw->setZValue(5);

	pw=addWidget(left);
	pw->setZValue(5);

	pw=addWidget(fourButton);
	pw->setZValue(10);

	pw=addWidget(singleButton);
	pw->setZValue(10);

	pw=addWidget(twoButton);
	pw->setZValue(10);

	pw=addWidget(threeButton);
	pw->setZValue(10);

	pw=addWidget(pointLevelSelectButton);
	pw->setZValue(10);

	pw=addWidget(objectLevelSelectButton);
	pw->setZValue(10);

	pw=addWidget(edgeLevelSelectButton);
	pw->setZValue(10);

	pw=addWidget(facetLevelSelectButton);
	pw->setZValue(10);
            */
	foreach (QGraphicsItem *item, items()) 	
	{
        item->setFlag(QGraphicsItem::ItemIsMovable);
        item->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    }

	connect(this,SIGNAL(sceneRectChanged(const QRectF &)),this,SLOT(onResize(const QRectF &)));

	connect(joint,SIGNAL(jointDragFinished()),this,SLOT(onDragFinished()));
}

//如果当前active的canvas 在switch layout之后 隐藏了，要在此之前把current canvas改正过来。

void MultipleView::onDragFinished()
{
	if(widgets[3])
		widgets[3]->cacheSelectionBuffer();

	if(widgets[2])
		widgets[2]->cacheSelectionBuffer();

	if(widgets[1])
		widgets[1]->cacheSelectionBuffer();

	if(widgets[0])
		widgets[0]->cacheSelectionBuffer();
}

void MultipleView::onResize(const QRectF &rect)
{



		  /*foreach (QGraphicsItem *item, items()) 
			{
        item->setFlag(QGraphicsItem::ItemIsMovable);
        item->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
		item->setPos(400,400);
    }*/

	if(x==-1 && y==-1)
	{
		x=rect.width()*0.5f;
		y=rect.height()*0.5f;
		oldWidth=rect.width();
		oldHeight=rect.height();
		refreshBarPositions();
	}
	else
	{
		switch(layout)
		{
			case Single:
				updateBarPositions();
				break;
	
			case Four:
				if(oldWidth==-1 && oldHeight==-1)
				{
					refreshBarPositions();
				}
				else
				{
					float xR=(float)x/(float)(oldWidth);
					float yR=(float)y/(float)(oldHeight);

					x=(int)(xR*rect.width());
					y=(int)(yR*rect.height());

					oldWidth=rect.width();
					oldHeight=rect.height();

					updateBarPositions();
				}
				break;
		}


		singleButton->setGeometry(rect.width()-29-10,rect.height()*0.5f-1-29-2-29,29,29);
		twoButton->setGeometry(rect.width()-29-10,rect.height()*0.5f-1-29,29,29);
		threeButton->setGeometry(rect.width()-29-10,rect.height()*0.5f+1,29,29);
		fourButton->setGeometry(rect.width()-29-10,rect.height()*0.5f+1+29+2,29,29);

		pointLevelSelectButton->setGeometry(10,rect.height()*0.5f-1-29-2-29,29,29);
		edgeLevelSelectButton->setGeometry(10,rect.height()*0.5f-1-29,29,29);
		facetLevelSelectButton->setGeometry(10,rect.height()*0.5f+1,29,29);
		objectLevelSelectButton->setGeometry(10,rect.height()*0.5f+1+29+2,29,29);
	}


	if(widgets[3])
		widgets[3]->setSceneSize(QSize(rect.width(),rect.height()));

	if(widgets[2])
		widgets[2]->setSceneSize(QSize(rect.width(),rect.height()));

	if(widgets[1])
		widgets[1]->setSceneSize(QSize(rect.width(),rect.height()));

	if(widgets[0])
		widgets[0]->setSceneSize(QSize(rect.width(),rect.height()));

	
	update();

}

void MultipleView::jointDraged(int _x,int _y)
{
	x+=_x;
	y+=_y;

	if(x<0) x=0;
	if(x>sceneRect().width()) x=sceneRect().width();

	if(y<0) y=0;
	if(y>sceneRect().height()) y=sceneRect().height();

	updateBarPositions();


	update();

	//repaint();
}

void MultipleView::leftDraged(int value)
{

	y+=value;
	if((y)<0)
		y=0;
	if(y>sceneRect().height())
		y=sceneRect().height();

	updateBarPositions();

	update();
}

void MultipleView::rightDraged(int value)
{
	y+=value;
	if(y<0) y=0;
	if(y>sceneRect().height())
		y=sceneRect().height();

	updateBarPositions();
	update();
}

void MultipleView::upDraged(int value)
{
	x+=value;
	if(x<0) x=0;
	if(x>sceneRect().width())
		x=sceneRect().width();

	updateBarPositions();
	update();
}

void MultipleView::drawBackground(QPainter *painter, const QRectF &)
{
  /*  if (painter->paintEngine()->type() != QPaintEngine::OpenGL) {
        qWarning("OpenGLScene: drawBackground needs a QGLWidget to be set as viewport on the graphics view");
        return;
    }*/

	   
	painter->beginNativePainting();
 

		
	
	glClearColor(0.8,0.85098,0.78,1.0);
	//glClearColor(1,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

	


		if(widgets[2] && widgets[2]->isVisible())
		{
			((GLCanvas*)widgets[2])->fakePaintEvent();
		}

		if(widgets[1] && widgets[1]->isVisible())
		{
			((GLCanvas*)widgets[1])->fakePaintEvent();
		}

		if(widgets[0] && widgets[0]->isVisible())
		{
				((GLCanvas*)widgets[0])->fakePaintEvent();
		}

		if(widgets[3] && widgets[3]->isVisible())
		{
			((GLCanvas*)widgets[3])->fakePaintEvent();
		}


	glViewport(sceneRect().x(),sceneRect().y(),sceneRect().width(),sceneRect().height());

	glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

	glDisable(GL_DEPTH_TEST);

   
    painter->endNativePainting();
}

void MultipleView::downDraged(int value)
{
	x+=value;
	if(x<0) x=0;
	if(x>sceneRect().width())
	 x=sceneRect().width();

	updateBarPositions();
	update();
}


void MultipleView::canvas0OnActivate()
{
	currentCanvas=widgets[0];
	if(widgets[0])
	{
		widgets[0]->isActivated=true;
		widgets[0]->update();
		setFocusItem (widgetProxies[0]);
		widgets[0]->setFocus();
		widgetProxies[0]->setFocus();
		setActiveWindow(widgetProxies[0]);
	}
	
	if(widgets[1])
	{
		widgets[1]->isActivated=false;
		widgets[1]->update();
	}
	
	if(widgets[2])
	{
		widgets[2]->isActivated=false;
		widgets[2]->update();
	}
	
	if(widgets[3])
	{
		widgets[3]->isActivated=false;
		widgets[3]->update();
	}


}

void MultipleView::canvas1OnActivate()
{
	currentCanvas=widgets[1];
	
	if(widgets[0])
	{
		widgets[0]->isActivated=false;
		widgets[0]->update();
	}
	
		if(widgets[1])
	{
		widgets[1]->isActivated=true;
		widgets[1]->update();
		setFocusItem (widgetProxies[1]);
		widgets[1]->setFocus();
		widgetProxies[1]->setFocus();
		setActiveWindow(widgetProxies[1]);
	}
	
	if(widgets[2])
	{
		widgets[2]->isActivated=false;
		widgets[2]->update();
	}
	
	if(widgets[3])
	{
		widgets[3]->isActivated=false;
		widgets[3]->update();
	}

}

void MultipleView::canvas2OnActivate()
{
	currentCanvas=widgets[2];
	if(widgets[0])
	{
		widgets[0]->isActivated=false;
		widgets[0]->update();
	}
	
		if(widgets[2])
	{
		widgets[2]->isActivated=true;
		widgets[2]->update();
		setFocusItem (widgetProxies[2]);
		widgets[2]->setFocus();
		widgetProxies[2]->setFocus();
		setActiveWindow(widgetProxies[2]);
	}
	
	if(widgets[1])
	{
		widgets[1]->isActivated=false;
		widgets[1]->update();
	}
	
	if(widgets[3])
	{
		widgets[3]->isActivated=false;
		widgets[3]->update();
	}
}

void MultipleView::canvas3OnActivate()
{
	currentCanvas=widgets[3];
	if(widgets[0])
	{
		widgets[0]->isActivated=false;
		widgets[0]->update();
	}
	
	if(widgets[3])
	{
		widgets[3]->isActivated=true;
		widgets[3]->update();
		setFocusItem (widgetProxies[3]);
		widgets[3]->setFocus();
		widgetProxies[3]->setFocus();
		setActiveWindow(widgetProxies[3]);
	}
	
	if(widgets[2])
	{
		widgets[2]->isActivated=false;
		widgets[2]->update();
	}
	
	if(widgets[1])
	{
		widgets[1]->isActivated=false;
		widgets[1]->update();
	}
}


void MultipleView::setWidget(int id,GLCanvas *_widget)
{
	if(id>=0 && id<=3){
		widgets[id]=_widget;

	_widget->setAutoFillBackground(false);

	QPalette palette = _widget->palette();
palette.setBrush(QPalette::Base, Qt::transparent);
_widget->setStyleSheet("background: transparent"); 

_widget->setPalette(palette);
_widget->setAttribute(Qt::WA_OpaquePaintEvent, false);
	
	widgetProxies[id]=addWidget(_widget);


widgetProxies[id]->setZValue(1);

	   
       widgetProxies[id]->setFlag(QGraphicsItem::ItemIsMovable);
      widgetProxies[id]->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
	


/*
	fourButton->raise();
	threeButton->raise();
	twoButton->raise();
	singleButton->raise();

	objectLevelSelectButton->raise();
	facetLevelSelectButton->raise();
	edgeLevelSelectButton->raise();
	pointLevelSelectButton->raise();*/


		switch(id)
		{
		case 0:
				connect(widgets[0],SIGNAL(onActivate()),this,SLOT(canvas0OnActivate()));
			break;
		case 1:
			connect(widgets[1],SIGNAL(onActivate()),this,SLOT(canvas1OnActivate()));
			break;
		case 2:
			connect(widgets[2],SIGNAL(onActivate()),this,SLOT(canvas2OnActivate()));
			break;
		case 3:connect(widgets[3],SIGNAL(onActivate()),this,SLOT(canvas3OnActivate()));
			break;
		}
	}
}

void MultipleView::switchLayout(LAYOUT _layout)
{
	switch(layout=_layout)
	{
	case Four:
		{
			if(widgets[3]!=0)
			{
				widgets[3]->setHidden(false);
				widgets[3]->setDisabled(false);
			}

			if(widgets[2]!=0)
			{
				widgets[2]->setHidden(false);
				widgets[2]->setDisabled(false);
			}

			if(widgets[1]!=0)
			{
				widgets[1]->setHidden(false);
				widgets[1]->setDisabled(false);
			}

			if(widgets[0]!=0)
			{
				widgets[0]->setHidden(false);
				widgets[0]->setDisabled(false);
			}

			up->setHidden(false);
			up->setDisabled(false);

			down->setHidden(false);
			down->setDisabled(false);

			left->setHidden(false);
			left->setDisabled(false);

			right->setHidden(false);
			right->setDisabled(false);

			joint->setHidden(false);
			joint->setDisabled(false);
		}
		break;
	case UpLeftRight:
		{
			if(widgets[3])
			{
				widgets[3]->setDisabled(false);
				widgets[3]->setHidden(false);
			}

			if(widgets[2])
			{
				widgets[2]->setDisabled(false);
				widgets[2]->setHidden(false);
			}
			
			if(widgets[3])
			{
				widgets[1]->setHidden(true);
				widgets[1]->setDisabled(true);
			}

			if(widgets[0])
			{
				widgets[0]->setHidden(false);
				widgets[0]->setDisabled(false);
			}
			

			up->setHidden(true);
			up->setDisabled(true);

			down->setHidden(false);
			down->setDisabled(false);

			left->setHidden(false);
			left->setDisabled(false);

			right->setHidden(false);
			right->setDisabled(false);

			joint->setHidden(false);
			joint->setDisabled(false);
		}
		break;
	case LeftRightDown:
		{
			if(widgets[3])
			{
				widgets[3]->setDisabled(false);
				widgets[3]->setHidden(false);
			}

			if(widgets[2])
			{
				widgets[2]->setDisabled(true);
				widgets[2]->setHidden(true);
			}

			if(widgets[1]){
			widgets[1]->setHidden(false);
			widgets[1]->setDisabled(false);
			}

			if(widgets[0])
			{
						widgets[0]->setHidden(false);
			widgets[0]->setDisabled(false);
			}

			up->setHidden(false);
			up->setDisabled(false);

			down->setHidden(true);
			down->setDisabled(true);

			left->setHidden(false);
			left->setDisabled(false);

			right->setHidden(false);
			right->setDisabled(false);

			joint->setHidden(false);
			joint->setDisabled(false);
		}
		break;
	case UpDownRight:
		{

			if(widgets[3]!=0)
			{
				widgets[3]->setDisabled(false);
				widgets[3]->setHidden(false);
			}
			
			if(widgets[2]!=0)
			{
				widgets[2]->setDisabled(false);
				widgets[2]->setHidden(false);
			}

			if(widgets[1]!=0)
			{
				widgets[1]->setHidden(true);
				widgets[1]->setDisabled(true);
			}

			if(widgets[0]!=0)
			{			
				widgets[0]->setHidden(false);
				widgets[0]->setDisabled(false);
			}

			up->setHidden(false);
			up->setDisabled(false);

			down->setHidden(false);
			down->setDisabled(false);

			left->setHidden(false);
			left->setDisabled(false);

			right->setHidden(true);
			right->setDisabled(true);

			joint->setHidden(false);
			joint->setDisabled(false);
		}
		break;
	case LeftUpDown:
		{

			if(widgets[3]!=0)
			{
				widgets[3]->setDisabled(false);
				widgets[3]->setHidden(false);
			}

			if(widgets[2]!=0)
			{
				widgets[2]->setDisabled(false);
				widgets[2]->setHidden(false);
		}

			if(widgets[1]!=0)
			{
				widgets[1]->setDisabled(false);
				widgets[1]->setHidden(false);
			}
			if(widgets[0]!=0)
			{
				widgets[0]->setDisabled(true);
				widgets[0]->setHidden(true);
}

			up->setHidden(false);
			up->setDisabled(false);

			down->setHidden(false);
			down->setDisabled(false);

			left->setHidden(true);
			left->setDisabled(true);

			right->setHidden(false);
			right->setDisabled(false);

			joint->setHidden(false);
			joint->setDisabled(false);
		}
		break;
	case UpDown:
		{
			if(widgets[3]!=0)
			{
				widgets[3]->setDisabled(false);
				widgets[3]->setHidden(false);
			}
			if(widgets[2]!=0)
			{
				widgets[2]->setDisabled(true);
				widgets[2]->setHidden(true);
			}
			if(widgets[1]!=0)
			{
				widgets[1]->setDisabled(false);
				widgets[1]->setHidden(false);
			}

			if(widgets[0]!=0)
			{
				widgets[0]->setDisabled(true);
				widgets[0]->setHidden(true);
			}

			up->setHidden(true);
			up->setDisabled(true);

			down->setHidden(true);
			down->setDisabled(true);

			left->setHidden(false);
			left->setDisabled(false);

			right->setHidden(true);
			right->setDisabled(true);

			joint->setHidden(true);
			joint->setDisabled(true);
		}
		break;
	case LeftRight:
		{
			if(widgets[3]!=0)
			{
				widgets[3]->setDisabled(false);
				widgets[3]->setHidden(false);
			}

			if(widgets[2]!=0)
			{
				widgets[2]->setDisabled(false);
				widgets[2]->setHidden(false);
			}

			if(widgets[1]!=0)
			{
				widgets[1]->setDisabled(true);
				widgets[1]->setHidden(true);
			}

			if(widgets[0]!=0)
			{
				widgets[0]->setDisabled(true);
				widgets[0]->setHidden(true);
			}
						
			up->setHidden(false);
			up->setDisabled(false);

			down->setHidden(true);
			down->setDisabled(true);

			left->setHidden(true);
			left->setDisabled(true);

			right->setHidden(true);
			right->setDisabled(true);

			joint->setHidden(true);
			joint->setDisabled(true);
		}
		break;
	case Single:
		{
			if(widgets[3]!=0)
			{
				widgets[3]->setDisabled(false);
				widgets[3]->setHidden(false);
			}
			
			if(widgets[2]!=0)
			{
				widgets[2]->setDisabled(true);
				widgets[2]->setHidden(true);
			}
			
			if(widgets[1]!=0)
			{
				widgets[1]->setDisabled(true);
				widgets[1]->setHidden(true);
			}
			
			if(widgets[0]!=0)
			{
				widgets[0]->setDisabled(true);
				widgets[0]->setHidden(true);
			}
						
			up->setHidden(true);
			up->setDisabled(true);

			down->setHidden(true);
			down->setDisabled(true);

			left->setHidden(true);
			left->setDisabled(true);

			right->setHidden(true);
			right->setDisabled(true);

			joint->setHidden(true);
			joint->setDisabled(true);
		}
		break;
	}

	updateBarPositions();
}

void MultipleView::fakePaintEvent()
{
	
	
}

void MultipleView::updateBarPositions()
{
	switch(layout)
	{
		case Four:
		{		

			left->setGeometry(0,y-2,x-2,4);
			right->setGeometry(x+2,y-2,sceneRect().width()-x+2,4);
			up->setGeometry(x-2,0,4,y-2);
			down->setGeometry(x-2,y+2,4,sceneRect().height()-y+2);
			joint->setGeometry(x-2,y-2,4,4);

			if(widgets[3]!=0)
			{

				widgets[3]->setGeometry(x+2,y+2,(sceneRect().width()-x)-2,(sceneRect().height()-y)-2);
			}

			if(widgets[2]!=0)
			{
				widgets[2]->setGeometry(0,y+2,x-2,(sceneRect().height()-y)-2);
			}

			if(widgets[1]!=0)
			{
				widgets[1]->setGeometry(x+2,0,(sceneRect().width()-x)-2,y-2);
			}

			if(widgets[0]!=0)
			{
				
				widgets[0]->setGeometry(0,0,x-2,y-2);
			}	
		}	
		break;
		
		case UpLeftRight:
		{		
			left->setGeometry(0,y-2,x-2,4);
			right->setGeometry(x+2,y-2,sceneRect().width()-x+2,4);
			up->setGeometry(x-2,0,4,y-2);
			down->setGeometry(x-2,y+2,4,sceneRect().height()-y+2);
			joint->setGeometry(x-2,y-2,4,4);
		
			if(widgets[3]!=0)
			{
				widgets[3]->setGeometry(x+2,y+2,(sceneRect().width()-x)-2,(sceneRect().height()-y)-2);
			//	widgets[3]->move(x+2,y+2);
			}

			if(widgets[2]!=0)
			{
				widgets[2]->setGeometry(0,y+2,x-2,(sceneRect().height()-y)-2);
				//widgets[2]->move(0,y+2);
			}



			if(widgets[0]!=0)
			{
				widgets[0]->setGeometry(0,0,sceneRect().width(),sceneRect().height()-y-2);
				//widgets[0]->move(0,0);
			}
		}
		break;
		
		case LeftRightDown:		
		{		
			left->setGeometry(0,y-2,x-2,4);
			right->setGeometry(x+2,y-2,sceneRect().width()-x+2,4);
			up->setGeometry(x-2,0,4,y-2);
			down->setGeometry(x-2,y+2,4,sceneRect().height()-y+2);
			joint->setGeometry(x-2,y-2,4,4);

			if(widgets[3]!=0)
			{
				widgets[3]->setGeometry(0,y+2,sceneRect().width(),(sceneRect().height()-y)-2);
			
			}



			if(widgets[1]!=0)
			{
				widgets[1]->setGeometry(x+2,0,(sceneRect().width()-x)-2,y-2);
				//widgets[1]->move(x+2,0);
			}

			if(widgets[0]!=0)
			{
				widgets[0]->setGeometry(0,0,x-2,y-2);
			}
		}
		break;
		
		case UpDownRight:		
		{		
			left->setGeometry(0,y-2,x-2,4);
			right->setGeometry(x+2,y-2,sceneRect().width()-x+2,4);
			up->setGeometry(x-2,0,4,y-2);
			down->setGeometry(x-2,y+2,4,sceneRect().height()-y+2);
			joint->setGeometry(x-2,y-2,4,4);

			if(widgets[3]!=0)
			{
				widgets[3]->setGeometry(x+2,0,(sceneRect().width()-x)-2,sceneRect().height());
			}

			if(widgets[2]!=0)
			{
				widgets[2]->setGeometry(0,y+2,x-2,(sceneRect().height()-y)-2);
			}



			if(widgets[0]!=0)
			{
				widgets[0]->setGeometry(0,0,x-2,y-2);
				
			}
		}
		break;

		case LeftUpDown:
		{
			left->setGeometry(0,y-2,x-2,4);
			right->setGeometry(x+2,y-2,sceneRect().width()-x+2,4);
			up->setGeometry(x-2,0,4,y-2);
			down->setGeometry(x-2,y+2,4,sceneRect().height()-y+2);
			joint->setGeometry(x-2,y-2,4,4);
		
			if(widgets[3]!=0)
			{
				widgets[3]->setGeometry(x+2,y+2,(sceneRect().width()-x)-2,(sceneRect().height()-y)-2);
				//widgets[3]->move(x+2,y+2);
			}

			if(widgets[1]!=0)
			{
				widgets[1]->setGeometry(x+2,0,(sceneRect().width()-x)-2,y-2);
			//	widgets[1]->move(x+2,0);
			}

			if(widgets[0]!=0)
			{
				widgets[0]->setGeometry(0,0,x-2,sceneRect().height());
			//	widgets[0]->move(0,0);
			}
		}
		break;

		case UpDown:
		{
			left->setGeometry(0,y-2,sceneRect().width(),4);
			
			if(widgets[3]!=0)
			{
				widgets[3]->setGeometry(0,y+2,sceneRect().width(),sceneRect().height()-y-2);
				//widgets[3]->move(0,y+2);
			}

			if(widgets[1]!=0)
			{
				widgets[1]->setGeometry(0,0,sceneRect().width(),y-2);
				//widgets[1]->move(0,0);
			}
		}
		break;
		
		case LeftRight:
		{
			up->setGeometry(x-2,0,4,sceneRect().height());
		
			if(widgets[3]!=0)
			{
				widgets[3]->setGeometry(x+2,0,sceneRect().width()-x-2,sceneRect().height());
				//widgets[3]->move(x+2,0);
			}

			if(widgets[2]!=0)
			{
			widgets[2]->setGeometry(0,0,x-2,sceneRect().height());
		//		widgets[2]->move(0,0);
			}
		}
		break;

		case Single:
		{
			if(widgets[3]!=0)
			{
				widgets[3]->setGeometry(0,0,sceneRect().width(),sceneRect().height());
			}
		}
		break;
	}
}

void MultipleView::refreshBarPositions()
{
	x=sceneRect().width()*0.5f;
	y=sceneRect().height()*0.5f;

	left->setGeometry(0,y-2,sceneRect().width()*0.5f-2,4);

	right->setGeometry(x+2,y-2,sceneRect().width()*0.5f-2,4);


	up->setGeometry(x-2,0,4,sceneRect().height()*0.5f-2);

	down->setGeometry(x-2,y+2,4,sceneRect().height()*0.5f-2);

	joint->setGeometry(x-2,y-2,4,4);

}

void MultipleView::resizeEvent ( QResizeEvent * event )
{
}

void MultipleView::paintGL()
{
	
	//if(widgets[3])
	//	((GLCanvas*)widgets[3])->fakePaintEvent();
}


/*void MultipleView::paintEvent ( QPaintEvent * event )
{

	makeCurrent();

	if(widgets[3])
		((GLCanvas*)widgets[3])->fakePaintEvent();

	QPainter painter(this);

	printf("#%d,%d#",size().height(),size().width());
	painter.fillRect(QRect(0,0,size().width(),size().height()),QColor(204,217,200));
	painter.end();
	event->accept();
}*/

MultipleView::~MultipleView(void)
{
}

void MultipleView::initializeGL()
{
	if(initialized==false)
	{
		initialized=true;
	glShadeModel(GL_SMOOTH);
	glPixelStorei(GL_PACK_ROW_LENGTH, 0);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glEnable(GL_DEPTH_TEST);

	//currentCamera->lookAt(GGL::Point3f(50,50,50),GGL::Point3f(0,0,0));

	GLenum err = glewInit();
	if (err != GLEW_OK ) 	
	{
		assert(0);
	}
	
	CoordinateGrid::getSingleton().prepare();

//	Scene::getSingleton().init();
	}
};



void MultipleView::singleButtonClicked()
{
	if(singleButton->isChecked()==true)
	{
		singleButton->setChecked(true);
		twoButton->setChecked(false);
		threeButton->setChecked(false);
		fourButton->setChecked(false);

		switchLayout(Single);

		update();
	}
	
}

void MultipleView::twoButtonClicked()
{
	if(twoButton->isChecked()==true)
	{
		singleButton->setChecked(false);
		twoButton->setChecked(true);
		threeButton->setChecked(false);
		fourButton->setChecked(false);

		switchLayout(LeftRight);

		update();
	}
}

void MultipleView::threeButtonClicked()
{
	if(threeButton->isChecked()==true)
	{
		singleButton->setChecked(false);
		twoButton->setChecked(false);
		threeButton->setChecked(true);
		fourButton->setChecked(false);

		switchLayout(UpDownRight);

		update();
	}
}

void MultipleView::fourButtonClicked()
{
	if(fourButton->isChecked()==true)
	{
		singleButton->setChecked(false);
		twoButton->setChecked(false);
		threeButton->setChecked(false);
		fourButton->setChecked(true);

		switchLayout(Four);

		update();
	}
}

void MultipleView:: createPerspectiveCamera()
{
	if(currentCanvas!=0)
	{
		PerspectiveCamera *camera=new PerspectiveCamera(tr("Unnamed Camera"));
		camera->setFov(45.0f);

		int cameraID=UserCameraManager::getSingleton().addCamera(camera);
		currentCanvas->switchCamera(cameraID);
	}
}

void MultipleView::createOrthogonalCamera()
{

}

void MultipleView::switchCamera(int cameraID)
{
	if(currentCanvas)
	{
		currentCanvas->switchCamera(cameraID);
	}
}

void MultipleView::saveCamera(const QString &filename)
{
	if(currentCanvas)
	{
                currentCanvas->saveCamera(filename);
	}
}

void MultipleView::loadCamera(const QString &filename)
{
	if(currentCanvas)
	{
                currentCanvas->loadCamera(filename);
	}
}
