#include <GL/glew.h>
#include "GLCanvas.h"
#include <QWheelEvent>
#include <QTime>
#include <QPainter>
#include "Plane3.h"
#include "segment3.h"
#include "intersection3.h"
#include "CoordinateGrid.h"
#include "Scene.h"
#include <QGLContext>
#include <QGLFramebufferObject>
#include "UserCameraManager.h"
#include <QApplication>
#include "CustomCursorManager.h"
#include <QHash>
#include "VectorField.h"
#include "drawillustrativedata.h"
GLuint GLCanvas::fbo=0;
GLuint GLCanvas::renderbuffer=0;

void GLCanvas::saveCamera(const QString &filename)
{
	if(currentCamera)
        currentCamera->save(filename);
}

void GLCanvas::loadCamera(const QString &filename)
{
	if(currentCamera)
                currentCamera->load(filename);
}

void GLCanvas::paintInfo(QPainter &painter)
{
	painter.setRenderHints(QPainter::HighQualityAntialiasing);
	painter.setBackground (  QBrush (QColor(255,255,255,0)) );
        /*if(isActivated)
	{
		painter.setPen(QColor(176,98,62,255));
		painter.drawRect(QRect(0,0,rect().width()-1,rect().height()-1));
	}
	else
	{
		painter.setPen(QColor(158,177,162,180));
		painter.drawRect(QRect(0,0,rect().width(),rect().height()));
	}

	painter.setPen(QColor(169,186,167,180));
	painter.drawRect(QRect(1,1,rect().width()-2,rect().height()-2));

	painter.setPen(QColor(182,198,180,180));
	painter.drawRect(QRect(2,2,rect().width()-4,rect().height()-4));
	painter.setPen(QColor(197,211,194,180));
	painter.drawRect(QRect(3,3,rect().width()-6,rect().height()-6));
	painter.setPen(QColor(44,54,53));
	painter.setFont(QFont("Arial", 10));
	painter.drawText(QRect(5,5,280,20),Qt::AlignLeft,currentCamera->cameraName());
*/
	if(manipulateType==MCamera && isShowManipulateStatus)
	{
					//QRect rr=rect();
		switch(manipulateStatus)
		{
		case None:
			break;
	
		case Rotate:		

			painter.drawImage(rect().width()*0.5-100,rect().height()*0.5-50,QImage("ManipulateStatusBk.png"));
			painter.setPen(Qt::white);
			painter.setFont(QFont("Arial", 30));
			painter.drawText(QRect(0,0,rect().width(),rect().height()), Qt::AlignCenter, "Rotate");
			break;
	
		case Zoom:
			painter.drawImage(rect().width()*0.5-100,rect().height()*0.5-50,QImage("ManipulateStatusBk.png"));
			painter.setPen(Qt::white);
			painter.setFont(QFont("Arial", 30));
			painter.drawText(QRect(0,0,rect().width(),rect().height()), Qt::AlignCenter, "Zoom");
			break;
	
		case Pan:
			painter.drawImage(rect().width()*0.5-100,rect().height()*0.5-50,QImage("ManipulateStatusBk.png"));
			painter.setPen(Qt::white);
			painter.setFont(QFont("Arial", 30));
			painter.drawText(QRect(0,0,rect().width(),rect().height()), Qt::AlignCenter, "Pan");
			break;
	
		default:
			break;
		}
	}
	else if(manipulateType==MObject && selectionType!=NoSelection)
	{
		int minSelectionX=selectionBeginX<selectionEndX?selectionBeginX:selectionEndX;
		int maxSelectionX=selectionBeginX>=selectionEndX?selectionBeginX:selectionEndX;

		int minSelectionY=selectionBeginY<selectionEndY?selectionBeginY:selectionEndY;
		int maxSelectionY=selectionBeginY>=selectionEndY?selectionBeginY:selectionEndY;

		QBrush brush(QColor::fromRgb(62, 142, 183, 100));

		painter.fillRect(QRect(minSelectionX,minSelectionY,maxSelectionX-minSelectionX,maxSelectionY-minSelectionY),brush);

		painter.setPen(QColor::fromRgb(51, 114, 135, 180));

		painter.drawRect(QRect(minSelectionX,minSelectionY,maxSelectionX-minSelectionX,maxSelectionY-minSelectionY));
	}

/*	if(isShowCameraInfo && currentCamera->isShowInfo())
	{
		painter.setPen(QColor(59,90,74));
		painter.setFont(QFont("Arial", 9));
		painter.drawText(QRect(5,rect().height()-55,200,50),Qt::AlignLeft,currentCamera->getCameraInfo());
	}
*/
	//painter.end();

}

GLCanvas::GLCanvas(QWidget *parent):QWidget(parent),manipulateStatus(None),isShowCameraInfo(true),isShowManipulateStatus(true),isActivated(false),perspectiveCamera(),currentCamera(0),
leftCamera(FixedOrthogonalCamera::Left),
rightCamera(FixedOrthogonalCamera::Right),
topCamera(FixedOrthogonalCamera::Top),
bottomCamera(FixedOrthogonalCamera::Bottom),
frontCamera(FixedOrthogonalCamera::Front),
backCamera(FixedOrthogonalCamera::Back),
cameraType(Perspective),cameraRatio(1.0f),_rect()
,
	 selectionBeginX(-1),
	 selectionBeginY(-1),
	selectionEndX(-1),
	 selectionEndY(-1),
	 manipulateType(MObject),
	 selectionType(NoSelection)
{



	upColor.r=204;
	upColor.g=217;
	upColor.b=200;
	upColor.a=255;

	lowColor.r=178;
	lowColor.g=195;
	lowColor.b=176;
	lowColor.a=255;

	lowColor;



	//setAutoFillBackground(false);
	//setAttribute(Qt::WA_DeleteOnClose,true);
	//setFocusPolicy(Qt::StrongFocus);
	setAutoFillBackground(false);

//	currentCamera=&perspectiveCamera;

	switchCamera(Perspective);

		setMouseTracking (true);


                connect(&VectorField::getSingleton(),SIGNAL(dataUpdated()),this,SLOT(onDataUpdated()));
}

void GLCanvas::onDataUpdated()
{
    if(currentCamera->getCameraType()==Camera::Perspective)
    {
        GGL::Point3f to(VectorField::getSingleton().xSize*0.5f,VectorField::getSingleton().ySize*0.5f,VectorField::getSingleton().zSize*0.5f);
        GGL::Point3f from(VectorField::getSingleton().xSize*1.5f,VectorField::getSingleton().ySize*1.5f,VectorField::getSingleton().zSize*1.5f);

        currentCamera->lookAt(from,to);
    }
}

void GLCanvas::clearViewport()
{
	glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

	glDisable(GL_LIGHTING);

	glDisable(GL_LIGHT0);

	glDisable(GL_COLOR_MATERIAL);

	glDisable(GL_DEPTH_TEST);

	glDepthMask(false);

	glBegin(GL_QUADS);
	glColor3ub(lowColor.r,lowColor.g,lowColor.b);
	glVertex2f(-1,-1);
	glVertex2f(1,-1);
	glColor3ub(upColor.r,upColor.g,upColor.b);
	glVertex2f(1,1);
	glVertex2f(-1,1);

	glEnd();

	glDepthMask(true);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

}

void GLCanvas::onCameraPropertyChanged(Camera *camera)
{
	if(currentCamera==camera)
	{
		update();
	}
}

void GLCanvas::switchCamera(int type)
{
	if(type>=-7 && type<0)
	{
		if(currentCamera)
		{
			QObject::disconnect(currentCamera,SIGNAL(onPropertyChanged(Camera *)),this,SLOT(onCameraPropertyChanged(Camera *)));
		}
		
		switch(cameraType=type)	
		{
		case Perspective:
			currentCamera=&perspectiveCamera;
			break;
		case Left:
			currentCamera=&leftCamera;
			break;
		case Right:
			currentCamera=&rightCamera;
			break;
		case Top:
			currentCamera=&topCamera;
			break;
		case Bottom:
			currentCamera=&bottomCamera;
			break;
		case Front:
			currentCamera=&frontCamera;
			break;
		case Back:
			currentCamera=&backCamera;
			break;
		}
		connect( currentCamera, SIGNAL(onPropertyChanged(Camera *)),this,SLOT(onCameraPropertyChanged(Camera*)));
		
	}
	else if(type>=0)
	{
		if(currentCamera)
		{
			QObject::disconnect(currentCamera,SIGNAL(onPropertyChanged(Camera *)),this,SLOT(onCameraPropertyChanged(Camera *)));
		}

		Camera *newCamera=UserCameraManager::getSingleton().getCameraByID(type);

		if(newCamera)
		{
			currentCamera=newCamera;
		}

		connect( currentCamera, SIGNAL(onPropertyChanged(Camera *)),this,SLOT(onCameraPropertyChanged(Camera*)));

	}
	
	update();
}


GLCanvas::~GLCanvas(void)
{
}

void GLCanvas::fakeRotate()
{
	currentCamera->onDragBegin(10,10,Camera::Rotate);
	currentCamera->onMouseMove(20,10);
	currentCamera->onDragStop();
	
	update();
}

void GLCanvas::fakePaintEvent()
{
	//glClear(GL_COLOR_BUFFER_BIT);

	glViewport(rect().x(),sceneSize.height()-(rect().y()+rect().height()),rect().width(),rect().height());
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	clearViewport();

	
	setView();
	CoordinateGrid::getSingleton().draw(CoordinateGrid::XY);
	Scene::getSingleton().testDrawForPillow(currentCamera);
	glEnable(GL_DEPTH_TEST);
	
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void GLCanvas::paintEvent ( QPaintEvent * event )   
{

	QPainter painter(this);

	paintInfo(painter);

	painter.end();
}


void GLCanvas::resizeGL(int width, int height)
{
	glViewport(0,0, width, height);

	cameraRatio=(float)rect().width()/ (float)rect().height();
	
	DrawIllustrativeData::getSingleton().resize(width,height);


/*	perspectiveCamera.width=width;
	perspectiveCamera.height=height;
	perspectiveCamera.ratio=ratio;

	leftCamera.width=width;
	leftCamera.height=height;
	leftCamera.ratio=ratio;

	rightCamera.width=width;
	rightCamera.height=height;
	rightCamera.ratio=ratio;

	topCamera.width=width;
	topCamera.height=height;
	topCamera.ratio=ratio;

	bottomCamera.width=width;
	bottomCamera.height=height;
	bottomCamera.ratio=ratio;

	frontCamera.width=width;
	frontCamera.height=height;
	frontCamera.ratio=ratio;

	backCamera.width=width;
	backCamera.height=height;
	backCamera.ratio=ratio;*/

	




	//update();	
};

void GLCanvas::keyReleaseEvent ( QKeyEvent * event )
{
	event->accept();
	manipulateStatus=None;
	manipulateType=MObject;
	//update();

float k=	currentCamera->fov();
}; 

void GLCanvas::keyPressEvent ( QKeyEvent * event )
{
	printf("key:%d",event->key());
	event->accept();
	switch(event->key())
	{
		case 16777251:
			manipulateType=MCamera;
			QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
		break;
	}
	//update();
}; 

void GLCanvas::mousePressEvent(QMouseEvent *event)
{
	if(isActivated)
	{	
		switch(event->button())
		{
			case Qt::LeftButton:
			{
                                //if(manipulateType==MCamera)
                                //{
					manipulateStatus=Rotate;
					currentCamera->onDragBegin(event->x(),event->y(),Camera::Rotate);
                                /*}
				else if(manipulateType==MObject)
				{
					selectionType=GLCanvas::FrontOnly;
					
					selectionEndX=selectionBeginX=event->x();
					selectionEndY=selectionBeginY=event->y();
                                }*/
			}
			break;
	
			case Qt::MidButton:
                                /*if(manipulateType==MCamera)
                                {*/
					manipulateStatus=Pan;
					currentCamera->onDragBegin(event->x(),event->y(),Camera::Pan);
                                /*}
				else if(manipulateType==MObject)
				{
					selectionType=FrontAndBack;

					selectionEndX=selectionBeginX=event->x();
					selectionEndY=selectionBeginY=event->y();
                                }*/
				break;
	
			case Qt::RightButton:
                                /*if(manipulateType==MCamera)
                                {*/
					manipulateStatus=Zoom;
					currentCamera->onDragBegin(event->x(),event->y(),Camera::Zoom);
                                //}
				break;
		}
	}
	else
	{
		isActivated=true;
		emit onActivate();
	}

	event->accept();
	update();
}

bool GLCanvas::testIsOverGlyph(int x,int y)
{
	setViewForSelection(x,y,3,3);
	return Scene::getSingleton().isGlyphOn(x,y,currentCamera);
}

bool GLCanvas::testIsOverElement(int x,int y)
{
	if(colorCodeSelectionBuffer.valid(x,y))
	{
		QRgb color=colorCodeSelectionBuffer.pixel(x,y);

		QColor black;
		black.setRgb(0,0,0);
		if(color==black.rgb())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

void GLCanvas::mouseMoveEvent(QMouseEvent *event)
{
        /*if(manipulateType==MCamera)
        {*/
		currentCamera->onMouseMove(event->x(),event->y());
        /*}
	else if(manipulateType==MObject)
	{
        }*/
	event->accept();
	update();
};

void GLCanvas::mouseReleaseEvent(QMouseEvent *event)
{	

        /*if(manipulateType==MCamera)
        {*/
		manipulateStatus=None;
		currentCamera->onDragStop();
		//manipulateType=MObject;
	
                cacheSelectionBuffer();
        /*}
	else if(manipulateType==MObject)
	{
		int minSelectionX=selectionBeginX<selectionEndX?selectionBeginX:selectionEndX;
		int maxSelectionX=selectionBeginX>=selectionEndX?selectionBeginX:selectionEndX;

		int minSelectionY=selectionBeginY<selectionEndY?selectionBeginY:selectionEndY;
		int maxSelectionY=selectionBeginY>=selectionEndY?selectionBeginY:selectionEndY;
		
		areaSelection(minSelectionX,minSelectionY,maxSelectionX-minSelectionX,maxSelectionY-minSelectionY);
		selectionType=NoSelection;
        }*/
	
	update();	
};

void GLCanvas::mouseDoubleClickEvent ( QMouseEvent * event ) 
{
};

void GLCanvas::wheelEvent(QWheelEvent *e)
{
	const int WHEEL_STEP = 60;
	float notch = e->delta()/ float(WHEEL_STEP);
	if(manipulateType==MCamera)
	{
		currentCamera->onMouseWheel(notch);
	}
	update();	
};

QSize GLCanvas::minimumSizeHint() const
{
	return QSize(400,300);
}

QSize GLCanvas::sizeHint() const
{
	return QSize(400,300);
}

	
void GLCanvas::pointSelection(int x,int y)
{
	
}

void GLCanvas::screenshot(int id)
{
	glEnable(GL_DEPTH_TEST);
	QGLFramebufferObject testfbo(QSize(rect().width(),rect().height()));

	if(testfbo.bind())
	{
		
		fakePaintEvent();

		char fname[256];
		sprintf(fname,"imageout%d.png",id);

		QImage a=testfbo.toImage();
		a.save(fname);
		testfbo.release();
	}

}

void GLCanvas::cacheSelectionBuffer()
{
	QGLFramebufferObject testfbo(QSize(rect().width(),rect().height()));

	if(testfbo.bind())
	{
		glClearColor(1.0f,1.0f,1.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glViewport(0,0,rect().width(),rect().height());

		setView();
	
		Scene::getSingleton().drawForSelectionStencil();

		colorCodeSelectionBuffer=testfbo.toImage();

		//colorCodeSelectionBuffer.save("testout.png");
		
		testfbo.release();
	}
}

void GLCanvas::areaSelection(int x,int y,int width,int height)
{

	/*
	QGLFramebufferObject testfbo(QSize(width,height));

	if(testfbo.bind())
	{
		glClearColor(1.0f,1.0f,1.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glViewport(rect().x()+x,sceneSize.height()-(rect().y()+y+height),width,height);

		

		setViewForSelection(x,y,width,height);

		Scene::getSingleton().drawForSelectionColorCode();

		QImage a=testfbo.toImage();
		//a.save("a.png");
		testfbo.release();

		QHash<unsigned int,unsigned int> selectionHash;

		for(int ix=0;ix<width;++ix)
		{
			for(int iy=0;iy<height;++iy)
			{
				if(a.valid(ix,iy))
				{
					QRgb color=a.pixel(ix,iy);


					QColor temp(color);
		
					struct TempColor colorCode;
					colorCode.r=temp.red();
					colorCode.g=temp.green();
					colorCode.b=temp.blue();
					colorCode.a=0;

					int id=color2UInt(colorCode);

					if(id!=backgroundID)
						selectionHash[id]=id;



				}
			}
		}

		Scene::getSingleton().select(selectionHash,false);
	}*/



		/*QGLFramebufferObject testfbo(QSize(width,height));

	if(testfbo.bind())
	{
		glClearColor(1.0f,1.0f,1.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		setViewForSelection(x,y,width,height);

		Scene::getSingleton().draw();

		QImage a=testfbo.toImage();
		a.save("a.png");
		testfbo.release();
	}*/




}

void GLCanvas::setViewForSelection(int x,int y,int width,int height)
{
	glViewport(0,0,rect().width(),rect().height());
	cameraRatio=(float)rect().width()/(float)rect().height();
	currentCamera->setCameraForSelection(x,y,width,height,rect().width(),rect().height(),cameraRatio);
	glViewport(0,0,width,height);
}

void GLCanvas::setView()
{
/*	GLfloat fAspect = (GLfloat)rect().width()/ rect().height();
	camera.nearPlane =0.1f;
	camera.farPlane =  1000.0f;
*/
	//glViewport(0,0, rect().width(), rect().height());
	
	//_rect=QRect(0,0,800,600);
	cameraRatio=(float)rect().width()/(float)rect().height();
	currentCamera->setCamera(rect().width(),rect().height(),cameraRatio);



   	/*	
		glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(60, (float)camera.width/(float)camera.height, camera.nearPlane, camera.farPlane);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera.from[0],camera.from[1],camera.from[2] ,camera.to[0],camera.to[1], camera.to[2], camera.up[0],camera.up[1],camera.up[2]);
*/
//	Scene::getSingleton().setShaderParameters(*currentCamera);
	
	//glGetShaderiv();
};
