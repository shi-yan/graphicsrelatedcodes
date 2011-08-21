#pragma once
#include <QtGui/QGraphicsScene>
#include "MultiviewJoint.h"
#include "MultiviewBar.h"
#include <QtGui/QPushButton>
#include "GLCanvas.h"
#include <QtGui/QGraphicsScene>

#include "MultipleViewToolButton.h"

class MultipleView:public QGraphicsScene
{
Q_OBJECT
public:
	MultipleView(QWidget * parent=0);
	~MultipleView(void);

	public:
	enum LAYOUT
	{
		Four,
		UpLeftRight,
		LeftRightDown,
		UpDownRight,
		LeftUpDown,
		UpDown,
		LeftRight,
		Single
	};

public:
	GLCanvas *widgets[4];
	GLCanvas *currentCanvas;
	QGraphicsProxyWidget *widgetProxies[4];

private:
	MultipleViewToolButton *fourButton;
	MultipleViewToolButton *threeButton;
	MultipleViewToolButton *twoButton;
	MultipleViewToolButton *singleButton;

	MultipleViewToolButton *objectLevelSelectButton;
	MultipleViewToolButton *facetLevelSelectButton;
	MultipleViewToolButton *edgeLevelSelectButton;
	MultipleViewToolButton *pointLevelSelectButton;

private:
	MultiviewJoint *joint;
	MultiviewBar *left;
	MultiviewBar *right;
	MultiviewBar *up;
	MultiviewBar *down;
	LAYOUT layout;

private:
	int x;
	int y;

	int oldWidth;
	int oldHeight;

public:
	void drawBackground(QPainter *painter, const QRectF &rect);
	void setWidget(int id,GLCanvas *_widget);
	void refreshBarPositions();
	void updateBarPositions();
	void switchLayout(LAYOUT _layout);

public slots :
		void canvas0OnActivate();
		void canvas1OnActivate();
		void canvas2OnActivate();
		void canvas3OnActivate();
		void onDragFinished();

	void leftDraged(int value);
	void rightDraged(int value);
	void upDraged(int value);
	void downDraged(int value);
	void jointDraged(int _x,int _y);

	void singleButtonClicked();
	void twoButtonClicked();
	void threeButtonClicked();
	void fourButtonClicked();

	

	void onResize(const QRectF &rect);

public:

	void fakePaintEvent();

	void createPerspectiveCamera();
	void createOrthogonalCamera();

	void switchCamera(int);

        void saveCamera(const QString &filename);
        void loadCamera(const QString &filename);


protected :
	void initializeGL();
	void paintGL();
	void resizeEvent ( QResizeEvent * event ) ;



};
