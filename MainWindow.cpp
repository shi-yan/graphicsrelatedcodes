#include "Scene.h"
#include "MainWindow.h"

#include "GlobalProgressBar.h"
#include <QDateTime>
#include "UserCameraManager.h"
#include "DynamicAction.h"
#include "CameraPropertyDialog.h"
#include "CameraPropertyModel.h"
#include "SceneManagerModel.h"

#include <QtGui/QPixmap>
#include <QtGui/QDesktopWidget>
#include <QtCore/QTimer>
#include "CustomCursorManager.h"


MainWindow::MainWindow(void):QMainWindow(0),activatedCanvas(0)
{     
	if (objectName().isEmpty())  
		setObjectName(QString::fromUtf8("MainWindow"));
    
	CustomCursorManager::getSingleton().init();
	
	
	datasetLoaderDialog=new DatasetLoader("Dataset Loader",this);
	addDockWidget(static_cast<Qt::DockWidgetArea>(2), datasetLoaderDialog);
	
        streamlineGeneratorDialog=new StreamlineGenerator("Streamline Generator",this);
        addDockWidget(static_cast<Qt::DockWidgetArea>(2),streamlineGeneratorDialog);

	downSamplerDialog=new DownSampler("Down Sampler",this);
	addDockWidget(static_cast<Qt::DockWidgetArea>(2),downSamplerDialog);
	
//vectorFieldAbstractor=new VectorFieldAbstractor("Vector Field Abstractor", this);
//addDockWidget(static_cast<Qt::DockWidgetArea>(8),vectorFieldAbstractor);

        clusterColorDialog=new ClusterColorDialog("Cluster Color",this);
        addDockWidget(static_cast<Qt::DockWidgetArea>(8),clusterColorDialog);

//featureDetectorDialog=new FeatureDetector("Feature Detector",this);
//addDockWidget(static_cast<Qt::DockWidgetArea>(8),featureDetectorDialog);

        autoSeedingDialog=new AutoSeedingDialog("AutoSeeding",this);
        addDockWidget(static_cast<Qt::DockWidgetArea>(8),autoSeedingDialog);

drawIllustrativeDialog=new DrawIllustrative("Illustrative Visualization",this);
addDockWidget(static_cast<Qt::DockWidgetArea>(8),drawIllustrativeDialog);
	
	actionExit = new QAction(this);
	actionOpen = new QAction(this);
	actionSave = new QAction(this);
	actionSave_as = new QAction(this);
	actionFrom_Obj = new QAction(this);
	actionFrom_3DS = new QAction(this);
	actionTo_Obj = new QAction(this);
	actionTo_3DS = new QAction(this);
	
	actionCreateOrthogonalCamera=new MenuItemWithOptionButtonAction(this);
	actionCreateOrthogonalCamera->setText(tr("Create Orthogonal Camera"));
	
	actionCreatePerspectiveCamera=new MenuItemWithOptionButtonAction(this);
	actionCreatePerspectiveCamera->setText(tr("Create Perspective Camera"));
	
	actionCreateCameraFromView=new QAction(this);
	actionCreateCameraFromView->setText(tr("Create Camera from View"));
	
	mainView=new MultipleView();
	view=new GraphicsViewBackground();

	view->init();
	view->setScene(mainView);
	setCentralWidget(view);
	
	canvas1=new GLCanvas();
	canvas3=new GLCanvas();
	canvas2=new GLCanvas();
	canvas0 = new GLCanvas();    
	
	canvas1->setObjectName(QString::fromUtf8("canvas1"));
	canvas3->setObjectName(QString::fromUtf8("canvas3"));
	canvas2->setObjectName(QString::fromUtf8("canvas2"));
	canvas0->setObjectName(QString::fromUtf8("canvas0"));
	
	mainView->setWidget(0,canvas0);
	mainView->setWidget(1,canvas1);
	mainView->setWidget(2,canvas2);
	mainView->setWidget(3,canvas3);
	
	menubar = new QMenuBar(this);
	menubar->setGeometry(QRect(0, 0, 800, 21));
	setMenuBar(menubar);
	statusbar = new QStatusBar(this);
	
	menuFile = new QMenu(menubar);
   	menuEdit=new QMenu(menubar);
	menuCreate=new QMenu(menubar);
	menuDisplay=new QMenu(menubar);
	
	menuHelp = new QMenu(menubar);
	statusbar->setStyleSheet(QApplication::translate("MainWindow", " QStatusBar {background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(29, 54, 50, 255), stop:1 rgba(77, 98, 93, 255));height:10px;  spacing: 3px;   }  QStatusBar::item { border: 0px solid red;border-radius: 0px;padding: 200px;}", 0, QApplication::UnicodeUTF8));
	setStatusBar(statusbar);

	statusbar->setSizeGripEnabled(false);
	
	statusBarSpacerLabel=new QLabel(statusbar);
	statusBarSpacerLabel->setText("status information shows here!");
	globalProgressBar=new QProgressBar(statusbar);
	globalProgressBar->setGeometry(QRect(400, 370, 118, 10));
	globalProgressBar->setAutoFillBackground(false);
	
	QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(globalProgressBar->sizePolicy().hasHeightForWidth());
	globalProgressBar->setSizePolicy(sizePolicy);
	globalProgressBar->setAutoFillBackground(false);

	globalProgressBar->setValue(50);
	globalProgressBar->setTextVisible(false); 
	globalProgressBar->setStyleSheet(QApplication::translate("MainWindow", "QProgressBar { width:100px;\n"
															 "	background-color: rgb(54, 66, 65);\n"
															 "     border: 1px solid black; height:12px;padding:1px;\n"
															 "     border-radius: 4px;margin: 2px;\n"
															 
															 " }\n"
															 "\n"
															 " QProgressBar::chunk {\n"
															 "     width: 20px;  padding: 4px;\n"
															 "	background-color: rgb(247, 129, 31);\n"
															 " }", 0, QApplication::UnicodeUTF8));
	

        screenshotButton=new StatusbarButton(statusbar);
        screenshotButton->setText(QString("Screenshot"));
        saveCameraButton=new StatusbarButton(statusbar);
        saveCameraButton->setText(QString("Save Camera"));
        loadCameraButton=new StatusbarButton(statusbar);
        loadCameraButton->setText(QString("Load Camera"));

	
	lockSelectionButton=new StatusbarButton(statusbar);
	lockSelectionButton->setText(QString("Lock Selection"));
	lockSelectionButton->setCursor(QCursor(Qt::PointingHandCursor));
	
	frameCameraButton=new StatusbarButton(statusbar);
	frameCameraButton->setText(QString("Frame Camera"));
	frameCameraButton->setCursor(QCursor(Qt::PointingHandCursor));
	cameraSelectButton=new StatusbarButton(statusbar);
	sceneManagerButton=new StatusbarButton(statusbar);
	
	sceneManagerButton->setText(QString("Scene Manager"));
	sceneManagerButton->setCheckable(true);
	quickSaveButton=new StatusbarButton(statusbar);
	quickSaveButton->setText(QString("Save"));



	displayModeButton=new StatusbarButton(statusbar);
	displayModeButton->setText(QString("Display Mode"));
	
	
	cameraSelectButton->setObjectName(QString::fromUtf8("pushButton"));

	quickSaveButton->setCursor(QCursor(Qt::PointingHandCursor));
	sceneManagerButton->setCursor(QCursor(Qt::PointingHandCursor));
	cameraSelectButton->setCursor(QCursor(Qt::PointingHandCursor));
	screenshotButton->setCursor(QCursor(Qt::PointingHandCursor));
	screenshotButton->setObjectName(tr("screenshotbutton"));
	screenshotButton->setCheckable(false);
	cameraSelectButton->setText(QString("Camera"));
	screenshotButton->setText(QString("Screenshot"));
	cameraSelectMenu=new QMenu(cameraSelectButton);
	
	actionPerspectiveCamera=new QAction(this);
	actionPerspectiveCamera->setData(QVariant(GLCanvas::Perspective));
	actionPerspectiveCamera->setText(QString("Perspective"));
	
	actionLeftCamera=new QAction(this);
	actionLeftCamera->setData(QVariant(GLCanvas::Left));
	actionLeftCamera->setText(QString("Left"));
	
	actionRightCamera=new QAction(this);
	actionRightCamera->setData(QVariant(GLCanvas::Right));
	actionRightCamera->setText(QString("Right"));
	
	actionTopCamera=new QAction(this);
	actionTopCamera->setData(QVariant(GLCanvas::Top));
	actionTopCamera->setText(QString("Top"));
	
	actionBottomCamera=new QAction(this);
	actionBottomCamera->setData(QVariant(GLCanvas::Bottom));
	actionBottomCamera->setText(QString("Bottom"));
	
	actionFrontCamera=new QAction(this);
	actionFrontCamera->setData(QVariant(GLCanvas::Front));
	actionFrontCamera->setText(QString("Front"));
	
	actionBackCamera=new QAction(this);	
	actionBackCamera->setData(QVariant(GLCanvas::Back));
	actionBackCamera->setText(QString("Back"));	
	
	menuUserCameras=new QMenu(cameraSelectMenu);
	menuUserCameras->setStyleSheet(QApplication::translate("MainWindow", " QMenu {\n"
														   "  \n"
														   "	font: 8pt \"Arial\";\n"
														   "	background-color: rgb(42, 55, 55);\n"
														   "     margin: 0px; /* some spacing around the menu */\n"
														   "    border: 1px solid rgb(42,55,55); \n"
														   " }\n"
														   "\n"
														   " QMenu::item {\n"
														   "	color: rgb(174, 182, 177);\n"
														   "     padding: 2px 25px 2px 20px;\n"
														   "     border: 1px solid transparent; /* reserve space for selection border */\n"
														   " }\n"
														   "\n"
														   " QMenu::item:selected {\n"
														   "background: rgb(51, 114, 135);\n"
														   "	color: rgb(255, 255, 255);\n"
														   "     \n"
														   " }\n"
														   "\n"
														   " QMenu::separator {\n"
														   "     height: 1px;\n"
														   "    \n"
														   "	background-color: rgb(102, 117, 112);\n"
														   "     margin-left: 10px;\n"
														   "     margin-right: 5px;\n"
														   " }", 0, QApplication::UnicodeUTF8));
	
	menuUserCameras->setTitle("User Cameras");
	menuUserCameras->setEnabled(false);
	
	cameraSelectMenu->addAction(menuUserCameras->menuAction());
	cameraSelectMenu->addSeparator();
	cameraSelectMenu->addAction(actionPerspectiveCamera);	
	cameraSelectMenu->addAction(actionLeftCamera);	
	cameraSelectMenu->addAction(actionRightCamera);
	
	cameraSelectMenu->addAction(actionTopCamera);	
	cameraSelectMenu->addAction(actionBottomCamera);
	cameraSelectMenu->addAction(actionFrontCamera);
	cameraSelectMenu->addAction(actionBackCamera);
	
	connect(actionPerspectiveCamera,SIGNAL(triggered())	,this,	SLOT( perspectiveCameraOnTrigger()));
	connect(actionLeftCamera,SIGNAL(triggered()),this,SLOT(  leftCameraOnTrigger()));
	connect(actionRightCamera,SIGNAL(triggered()),this,SLOT(  rightCameraOnTrigger()));
	
	connect(actionFrontCamera,SIGNAL(triggered()),this,SLOT(  frontCameraOnTrigger()));
	connect(actionBackCamera,SIGNAL(triggered()),this,SLOT(  backCameraOnTrigger()));
	connect(actionTopCamera,SIGNAL(triggered()),this, SLOT( topCameraOnTrigger()));
	connect (actionBottomCamera,SIGNAL(triggered()),this,SLOT( bottomCameraOnTrigger()));
	
	connect(screenshotButton,SIGNAL(clicked()),this,SLOT(onScreenshot()));
	connect(actionCreatePerspectiveCamera,SIGNAL(triggered()),this,SLOT(onCreatePerspectiveCamera()));
	connect(actionCreateOrthogonalCamera,SIGNAL(triggered()),this,SLOT(onCreateOrthogonalCamera()));
	connect(actionCreateCameraFromView,SIGNAL(triggered()),this,SLOT(onCreateCameraFromView()));

	connect(actionCreatePerspectiveCamera,SIGNAL(optionButtonTriggered()),this,SLOT(onCreatePerspectiveCameraWithOption()));
	connect(actionCreateOrthogonalCamera,SIGNAL(optionButtonTriggered()),this,SLOT(onCreateOrthogonalCameraWithOption()));
	
	
	cameraSelectMenu->setStyleSheet(QApplication::translate("MainWindow", " QMenu {\n"
															"  \n"
															"	font: 8pt \"Arial\";\n"
															"	background-color: rgb(42, 55, 55);\n"
															"     margin: 0px; /* some spacing around the menu */\n"
															"    border: 1px solid rgb(42,55,55); \n"
															" }\n"
															"\n"
															" QMenu::item {\n"
															"	color: rgb(174, 182, 177);\n"
															"     padding: 2px 25px 2px 20px;\n"
															"     border: 1px solid transparent; /* reserve space for selection border */\n"
															" }\n"
															"\n"
															" QMenu::item:selected {\n"
															"background: rgb(51, 114, 135);\n"
															"	color: rgb(255, 255, 255);\n"
															"     \n"
															" }\n"
															"\n"
															" QMenu::separator {\n"
															"     height: 1px;\n"
															"    \n"
															"	background-color: rgb(102, 117, 112);\n"
															"     margin-left: 10px;\n"
															"     margin-right: 5px;\n"
															" }", 0, QApplication::UnicodeUTF8));
	

	
	
	menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
	
	
	
	menuFile->setStyleSheet(QApplication::translate("MainWindow", " QMenu {\n"
													"  \n"
													"	font: 8pt \"Arial\";\n"
													"	background-color: rgb(42, 55, 55);\n"
													"     margin: 0px; /* some spacing around the menu */\n"
													"    border: 1px solid rgb(42,55,55); \n"
													" }\n"
													"\n"
													" QMenu::item {\n"
													"	color: rgb(174, 182, 177);\n"
													"     padding: 2px 25px 2px 20px;\n"
													"     border: 1px solid transparent; /* reserve space for selection border */\n"
													" }\n"
													"\n"
													" QMenu::item:selected {\n"
													"background: rgb(51, 114, 135);\n"
													"	color: rgb(255, 255, 255);\n"
													"     \n"
													" }\n"
													"\n"
													" QMenu::separator {\n"
													"     height: 1px;\n"
													"    \n"
													"	background-color: rgb(102, 117, 112);\n"
													"     margin-left: 10px;\n"
													"     margin-right: 5px;\n"
													" }", 0, QApplication::UnicodeUTF8));
	

	
	
	menuEdit->setStyleSheet(QApplication::translate("MainWindow", " QMenu {\n"
													"  \n"
													"	font: 8pt \"Arial\";\n"
													"	background-color: rgb(42, 55, 55);\n"
													"     margin: 0px; /* some spacing around the menu */\n"
													"    border: 1px solid rgb(42,55,55); \n"
													" }\n"
													"\n"
													" QMenu::item {\n"
													"	color: rgb(174, 182, 177);\n"
													"     padding: 2px 25px 2px 20px;\n"
													"     border: 1px solid transparent; /* reserve space for selection border */\n"
													" }\n"
													"\n"
													" QMenu::item:selected {\n"
													"background: rgb(51, 114, 135);\n"
													"	color: rgb(255, 255, 255);\n"
													"     \n"
													" }\n"
													"\n"
													" QMenu::separator {\n"
													"     height: 1px;\n"
													"    \n"
													"	background-color: rgb(102, 117, 112);\n"
													"     margin-left: 10px;\n"
													"     margin-right: 5px;\n"
													" }", 0, QApplication::UnicodeUTF8));
	
	

	menuCreate->setStyleSheet(QApplication::translate("MainWindow", " QMenu {\n"
													  "  \n"
													  "	font: 8pt \"Arial\";\n"
													  "	background-color: rgb(42, 55, 55);\n"
													  "     margin: 0px; /* some spacing around the menu */\n"
													  "    border: 1px solid rgb(42,55,55); \n"
													  " }\n"
													  "\n"
													  " QMenu::item {\n"
													  "	color: rgb(174, 182, 177);\n"
													  "     padding: 2px 25px 2px 20px;\n"
													  "     border: 1px solid transparent; /* reserve space for selection border */\n"
													  " }\n"
													  "\n"
													  " QMenu::item:selected {\n"
													  "background: rgb(51, 114, 135);\n"
													  "	color: rgb(255, 255, 255);\n"
													  "     \n"
													  " }\n"
													  "\n"
													  " QMenu::separator {\n"
													  "     height: 1px;\n"
													  "    \n"
													  "	background-color: rgb(102, 117, 112);\n"
													  "     margin-left: 10px;\n"
													  "     margin-right: 5px;\n"
													  " }", 0, QApplication::UnicodeUTF8));
	

	menuDisplay->setStyleSheet(QApplication::translate("MainWindow", " QMenu {\n"
													   "  \n"
													   "	font: 8pt \"Arial\";\n"
													   "	background-color: rgb(42, 55, 55);\n"
													   "     margin: 0px; /* some spacing around the menu */\n"
													   "    border: 1px solid rgb(42,55,55); \n"
													   " }\n"
													   "\n"
													   " QMenu::item {\n"
													   "	color: rgb(174, 182, 177);\n"
													   "     padding: 2px 25px 2px 20px;\n"
													   "     border: 1px solid transparent; /* reserve space for selection border */\n"
													   " }\n"
													   "\n"
													   " QMenu::item:selected {\n"
													   "background: rgb(51, 114, 135);\n"
													   "	color: rgb(255, 255, 255);\n"
													   "     \n"
													   " }\n"
													   "\n"
													   " QMenu::separator {\n"
													   "     height: 1px;\n"
													   "    \n"
													   "	background-color: rgb(102, 117, 112);\n"
													   "     margin-left: 10px;\n"
													   "     margin-right: 5px;\n"
													   " }", 0, QApplication::UnicodeUTF8));
	
	

	
	
	
	cameraSelectButton->setMenu(cameraSelectMenu);
	
	
	
	statusbar->addPermanentWidget(statusBarSpacerLabel,1);
	
	
         statusbar->addPermanentWidget(saveCameraButton);
         statusbar->addPermanentWidget(loadCameraButton);

	statusbar->addPermanentWidget(quickSaveButton);
	statusbar->addPermanentWidget(sceneManagerButton);
	statusbar->addPermanentWidget(screenshotButton);
	statusbar->addPermanentWidget(lockSelectionButton);
	statusbar->addPermanentWidget(displayModeButton);
	
	statusbar->addPermanentWidget(cameraSelectButton);		

	statusbar->addPermanentWidget(frameCameraButton);
	statusbar->addPermanentWidget(globalProgressBar);
	
	
	menubar->addAction(menuFile->menuAction());
	menubar->addAction(menuCreate->menuAction());
	menubar->addAction(menuDisplay->menuAction());
	menubar->addAction(menuHelp->menuAction());

	menuImport = new QMenu(menuFile);
	menuImport->setTitle(tr("Import"));
	menuExport = new QMenu(menuFile);
	menuExport->setTitle(tr("Export"));

	menuCreateCamera=new QMenu(menuFile);
	menuCreateCamera->setTitle(tr("Create Camera"));

	menuFile->addAction(actionOpen);
	menuFile->addAction(actionSave);
	menuFile->addAction(actionSave_as);
	menuFile->addSeparator();
	menuFile->addAction(menuImport->menuAction());
	menuFile->addAction(menuExport->menuAction());
	menuFile->addSeparator();
	menuFile->addAction(actionExit);

	menuImport->addAction(actionFrom_Obj);
	menuImport->addAction(actionFrom_3DS);
	menuExport->addAction(actionTo_Obj);
	menuExport->addAction(actionTo_3DS);

	menuCreate->addAction(menuCreateCamera->menuAction());
	menuCreateCamera->addAction(	 actionCreateOrthogonalCamera);
	menuCreateCamera->addAction(actionCreatePerspectiveCamera);
	menuCreateCamera->addAction(actionCreateCameraFromView);

	actionOpen->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
	actionSave->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
	actionSave_as->setText(QApplication::translate("MainWindow", "Save as ...", 0, QApplication::UnicodeUTF8));
	actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
	
	actionFrom_Obj->setText(QApplication::translate("MainWindow", "From Obj", 0, QApplication::UnicodeUTF8));
	actionFrom_3DS->setText(QApplication::translate("MainWindow", "From 3DS", 0, QApplication::UnicodeUTF8));
	actionTo_Obj->setText(QApplication::translate("MainWindow", "To OBJ", 0, QApplication::UnicodeUTF8));
	actionTo_3DS->setText(QApplication::translate("MainWindow", "To 3DS", 0, QApplication::UnicodeUTF8));

	QObject::connect(actionExit, SIGNAL(triggered(bool)), this, SLOT(exitTriggered(bool)));
	

	mainView->switchLayout(MultipleView::Single);
	menubar->setStyleSheet(QApplication::translate("MainWindow", "QMenuBar{\n"
												   "background-color: rgb(223, 230, 222);\n"
												   "	font: 8pt \"Arial\";\n"
												   "}\n"
												   "\n"
												   " QMenuBar::item {\n"
												   "	font: 8pt \"Arial\";\n"
												   "     background: transparent;\n"
												   "	color: rgb(51, 114, 135);\n"
												   " }\n"
												   "\n"
												   " QMenuBar::item:selected { /* when selected using mouse or keyboard */\n"
												   "    \n"
												   "	\n"
												   "	\n"
												   "	font: 8pt \"Arial\";\n"
												   "	background: transparent;\n"
												   "	color: rgb(176, 98, 62);\n"
												   " }\n"
												   "\n"
												   " QMenuBar::item:pressed {\n"
												   "    	font: 8pt \"Arial\";\n"
												   "	background-color: rgb(197, 211, 194);\n"
												   " }\n"
												   "\n"
												   "QMenu {\n"
												   "     background-color: #ABABAB; /* sets background of the menu */\n"
												   "     border: 1px solid black;\n"
												   " }\n"
												   "\n"
												   " QMenu::item {\n"
												   "     /* sets background of menu item. set this to something non-transparent\n"
												   "         if you want menu color and menu item color to be different */\n"
												   "     background-color: transparent;\n"
												   " }\n"
												   "\n"
												   " QMenu::item:selected { /* when user selects item using mouse or keyboard */\n"
												   "     background-color: #654321;\n"
												   " }", 0, QApplication::UnicodeUTF8));
	
	
	menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
	menuFile->setStyleSheet(QApplication::translate("MainWindow", " QMenu {\n"
													"  \n"
													"	font: 8pt \"Arial\";\n"
													"	background-color: rgb(42, 55, 55);\n"
													"     margin: 0px; /* some spacing around the menu */\n"
													"    border: 1px solid rgb(42,55,55); \n"
													" }\n"
													"\n"
													" QMenu::item {\n"
													"	color: rgb(174, 182, 177);\n"
													"     padding: 2px 25px 2px 20px;\n"
													"     border: 1px solid transparent; /* reserve space for selection border */\n"
													" }\n"
													"\n"
													" QMenu::item:selected {\n"
													"background: rgb(51, 114, 135);\n"
													"	color: rgb(255, 255, 255);\n"
													"     \n"
													" }\n"
													"\n"
													" QMenu::separator {\n"
													"     height: 1px;\n"
													"    \n"
													"	background-color: rgb(102, 117, 112);\n"
													"     margin-left: 10px;\n"
													"     margin-right: 5px;\n"
													" }", 0, QApplication::UnicodeUTF8));
    
	
	menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
	menuDisplay->setTitle(tr("Display"));
	menuEdit->setTitle(tr("Edit"));
	menuCreate->setTitle(tr("Create"));
	
	setStyleSheet(QApplication::translate("MainWindow", "QMainWindow::separator {\n"
										  "     background: rgb(214,222,212);\n"
										  "     width: 1px; /* when vertical */\n"
										  "     height: 1px; /* when horizontal */\n"
										  " }\n"
										  "\n"
										  " QMainWindow::separator:hover {\n"
										  "     background: rgb(239,243,239);\n"
										  " }", 0, QApplication::UnicodeUTF8));
	
	canvas0->switchCamera(GLCanvas::Top);
	canvas1->switchCamera(GLCanvas::Front);
	canvas2->switchCamera(GLCanvas::Left);
	canvas3->switchCamera(GLCanvas::Perspective);
	
	
	//	 cameraPropertyDialog->addObject(canvas3->getCurrentCamera());
	
	mainView->canvas3OnActivate();
	
	connect((&UserCameraManager::getSingleton()),SIGNAL(onCameraAdded(int)),this,SLOT(onUserCameraAdded(int)));
	connect(screenshotButton,SIGNAL(clicked()),this,SLOT(onScreenshotClicked()));
	
	//mainView->createPerspectiveCamera();
	// cameraPropertyDialog->addModel(new CameraPropertyModel(0));
	// sceneManagerDialog->addModel(new SceneManagerModel());
	
        connect(saveCameraButton,SIGNAL(clicked()),this,SLOT(onSaveCameraClicked()));
        connect(loadCameraButton,SIGNAL(clicked()),this,SLOT(onLoadCameraClicked()));
}

MainWindow::~MainWindow(void)
{
}

void MainWindow::exitTriggered ( bool checked )  
{
	close();
	QApplication::exit(0);
}

void MainWindow::perspectiveCameraOnTrigger()
{
	
		mainView->switchCamera(GLCanvas::Perspective);
	
}

void MainWindow::leftCameraOnTrigger()
{
	
		mainView->switchCamera(GLCanvas::Left);
				//activatedCanvas->update();

}

void MainWindow::rightCameraOnTrigger()
{
	
		mainView->switchCamera(GLCanvas::Right);
				//activatedCanvas->update();

}

void MainWindow::frontCameraOnTrigger()
{
	

		mainView->switchCamera(GLCanvas::Front);
				//activatedCanvas->update();

	
}

void MainWindow::backCameraOnTrigger()
{

		mainView->switchCamera(GLCanvas::Back);
	
}

void MainWindow::topCameraOnTrigger()
{
		if(activatedCanvas)
	{
		activatedCanvas->switchCamera(GLCanvas::Top);
			//	activatedCanvas->update();

	}
}

void MainWindow::bottomCameraOnTrigger()
{
		if(activatedCanvas)
	{
		activatedCanvas->switchCamera(GLCanvas::Bottom);
			//	activatedCanvas->update();

	}
}

void MainWindow::onScreenshot()
{
    //    QPixmap screenshot(mainView->currentCanvas->rect().size());
        //QPainter painter(&screenshot);

	// print, fitting the viewport contents into a full page
    QDateTime dateTime = QDateTime::currentDateTime();
         //   QString dateTimeString = ;
        view->GLViewport->grabFrameBuffer().save(QString("screenshot_%1.png").arg(dateTime.toString()));


  //      f.save("screenshot.png");
}

void MainWindow::onCreatePerspectiveCamera()
{
	mainView->createPerspectiveCamera();
	menuCreate->hide();
}

void MainWindow::onCreateOrthogonalCamera()
{

}

void MainWindow::onCreateCameraFromView()
{

}

void MainWindow::onCreatePerspectiveCameraWithOption()
{
}

void MainWindow::onCreateOrthogonalCameraWithOption()
{
}

void MainWindow::onUserCameraAdded(int cameraID)
{
	//’‚¿Ô“™◊¢“‚£¨µ± µœ÷ÕÍload fileµƒ ±∫Ú£¨»Áπ˚≥°æ∞¿Ô√Ê“—æ≠”–”√ªß∂®“Âµƒ…„”∞ª˙£¨“™º«µ√call’‚¿Ô°£≤ª»ªƒ¨»œµƒmenuUserCamera «disableµƒ
	//¡ÌÕ‚∫‹∂‡class£¨¿˝»Ácamera∂º√ª µœ÷operator=
	//”–≥Ø“ª»’ªπ“™ºÏ≤Èvirtual ~
	menuUserCameras->setEnabled(true);
	UserCameraManager::getSingleton().setUserCameraMenu(*menuUserCameras);

	QList<QAction *> actionList=menuUserCameras->actions();

	QList<QAction *>::iterator iter=actionList.begin();

	for(;iter!=actionList.end();++iter)
	{
		connect((DynamicAction*)(*iter),SIGNAL(triggered(QAction*)),this,SLOT(onSwitchUserCamera(QAction*)));
	}

}

void MainWindow::onSwitchUserCamera(QAction *action)
{
	int cameraID=action->data().toInt();
	mainView->switchCamera(cameraID);
}

static QTimer *timer;

void MainWindow::onSaveCameraClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
          tr("Save Camera"), "./", tr("Camera Files (*.cam)"));

    if(!fileName.isEmpty())
        mainView->saveCamera(fileName);

	//view->update();
}

void MainWindow::onLoadCameraClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
          tr("Open Camera"), "./", tr("Camera Files (*.cam)"));
    if(!fileName.isEmpty())
        mainView->loadCamera(fileName);
	view->update();



}

void MainWindow::onScreenshotClicked()
{

	timer=new QTimer(this);

	
     connect(timer, SIGNAL(timeout()), this, SLOT(updatess()));
     timer->start(1000);
	/*	mainView->currentCanvas->screenshot(0);
	for(int i=1;i<100;++i)
	{
		Scene::getSingleton().loadNext();
		mainView->currentCanvas->screenshot(i);
	

	}*/

//updatess();

}

static int shotcount=0;

void MainWindow::updatess()
{

#ifdef POINTBASE

	if(shotcount==3500) exit(0);
		QPixmap originalPixmap = QPixmap::grabWindow(QApplication::desktop()->winId());

		originalPixmap.save(QString("ani\\klm-new2out%1.png").arg(shotcount++));

			Scene::getSingleton().loadNext(shotcount);

			mainView->update();
	view->update();
		//canvas3->fakeRotate();
#endif
}
