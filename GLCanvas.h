#pragma once
#include <QtOpenGL/QGLWidget>
#include <QtCore/QMap>
#include <QtGui/QFont>
#include <iostream>
#include "Point2.h"
#include "PerspectiveCamera.h"
#include "FixedOrthogonalCamera.h"
#include "drawillustrativedata.h"

struct TEMPColor
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

class GLCanvas:public QWidget
{
	Q_OBJECT
private:
	QRect _rect;
	QSize sceneSize;

public:
	QRect & rect()
	{
		return _rect;
	};

	void setSceneSize(QSize _size)
	{
		sceneSize=_size;
		
		DrawIllustrativeData::getSingleton().resize(sceneSize.width(),sceneSize.height());
		
	}

	void setGeometry(int x, int y, int width, int height)
	{
		QWidget::setGeometry(x,y,width,height);
		_rect=QRect(x,y,width,height);
		//cacheSelectionBuffer();
	}

public:
	enum CameraType
	{
		Perspective =-7,
		Left = -1,
		Right = -2,
		Top = -3,
		Bottom = -4,
		Front =-5,
		Back =-6,
	};

private:
	enum ManipulateStatus
	{
		None,
		Rotate,
		Pan,
		Zoom,
	};

	enum SelectionType
	{
		NoSelection,
		FrontOnly,
		FrontAndBack,
	};

	enum ManipulateType
	{
		MCamera,
		MObject,
	};

	int selectionBeginX;
	int selectionBeginY;
	int selectionEndX;
	int selectionEndY;



	enum ManipulateType manipulateType;
	enum ManipulateStatus manipulateStatus;
	enum SelectionType selectionType;
public:
		static GLuint fbo;
		static GLuint renderbuffer;

public:
	GLCanvas(QWidget *parent=0);
	~GLCanvas(void);
	void fakePaintEvent();
		
	Camera *getCurrentCamera()
	{
		return currentCamera;
	}
private:
	Camera *currentCamera;
	PerspectiveCamera perspectiveCamera;
	FixedOrthogonalCamera leftCamera;
	FixedOrthogonalCamera rightCamera;
	FixedOrthogonalCamera topCamera;
	FixedOrthogonalCamera bottomCamera;
	FixedOrthogonalCamera frontCamera;
	FixedOrthogonalCamera backCamera;

	int cameraType;

	float cameraRatio;

	bool testIsOverElement(int x,int y);

	bool testIsOverGlyph(int x,int y);

public:
	QSize minimumSizeHint() const;
	QSize sizeHint() const;

	void switchCamera(int type);

	void fakeRotate();

	TEMPColor upColor;
	TEMPColor lowColor;


private:
	void setLightModel();
	void setView();
	void setViewForSelection(int x,int y,int width,int height);
	void clearViewport();

	
	QImage colorCodeSelectionBuffer;

	
	void pointSelection(int x,int y);
	void areaSelection(int x,int y,int width,int height);


	public slots:
		void onCameraPropertyChanged(Camera *);
  	  
public:
	void cacheSelectionBuffer();

	bool isShowCameraInfo;
	bool isShowManipulateStatus;
	bool isActivated;

public:
	void paintEvent ( QPaintEvent * event);
	
	void paintInfo(QPainter &painter);
	void resizeGL(int width, int height);
	void keyReleaseEvent ( QKeyEvent * event ); 
	void keyPressEvent ( QKeyEvent * event ); 
	
	

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseDoubleClickEvent ( QMouseEvent * event );
	void wheelEvent(QWheelEvent *event);

        void saveCamera(const QString &filename);
        void loadCamera(const QString &filename);


	void screenshot(int id);

signals:
	void onActivate();

        private slots:
        void onDataUpdated();
};

