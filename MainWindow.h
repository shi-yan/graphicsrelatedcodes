#pragma once

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QDockWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QVBoxLayout>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QtGui/QMenu>


#include "GLCanvas.h"
#include "MultipleView.h"
#include "DockWidget.h"

#include "GraphicsViewBackground.h"
#include "CameraPropertyDialog.h"

#include "StatusbarButton.h"

#include "MenuItemWithOptionButton.h"

#include "CreateCameraDialog.h"
#include "CreateBoxDialog.h"
#include "CreateBallDialog.h"
#include "CreateCylinderDialog.h"

#include "ColorPickerDialog.h"
#include "SceneManagerDialog.h"

#include "DatasetLoader.h"
#include "DownSampler.h"
#include "streamlinegenerator.h"
#include "VectorFieldAbstractor.h"
#include "FeatureDetector.h"
#include "drawillustrative.h"
#include "clustercolordialog.h"
#include "autoseedingdialog.h"

class DynamicAction;

class MainWindow:public QMainWindow
{
	Q_OBJECT
private:
	GLCanvas *activatedCanvas;
	public:
    GLCanvas *canvas0;
	GLCanvas *canvas2;
	GLCanvas *canvas3;
	GLCanvas *canvas1;
  
	QMenuBar *menubar;
    QStatusBar *statusbar;
	QMenu *menuFile;
	QMenu *menuEdit;
	QMenu *menuCreate;
	QMenu *menuDisplay;
    QMenu *menuHelp;
    QMenu *menuImport;
    QMenu *menuExport;
	QMenu *menuCreateCamera;

	QMenu *cameraSelectMenu;
	QAction *actionExit;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionFrom_Obj;
    QAction *actionFrom_3DS;
    QAction *actionTo_Obj;
    QAction *actionTo_3DS;
	
	QAction *actionPerspectiveCamera;
	QAction *actionLeftCamera;
	QAction *actionRightCamera;
	QAction *actionTopCamera;
	QAction *actionBottomCamera;
	QAction *actionFrontCamera;
	QAction *actionBackCamera;
	QMenu *menuUserCameras;

	MenuItemWithOptionButtonAction *actionCreateOrthogonalCamera;
	MenuItemWithOptionButtonAction *actionCreatePerspectiveCamera;
	QAction *actionCreateCameraFromView;


	GraphicsViewBackground *view;
	MultipleView *mainView;

	StatusbarButton *frameCameraButton;
	StatusbarButton *cameraSelectButton;
	StatusbarButton *screenshotButton;
	StatusbarButton *sceneManagerButton;
	StatusbarButton *quickSaveButton;
	StatusbarButton *displayModeButton;
	StatusbarButton *lockSelectionButton;
	StatusbarButton *saveCameraButton;
	StatusbarButton *loadCameraButton;
	CreateCameraDialog *createCameraDialog;

	CreateBoxDialog *createBoxDialog;
	CreateBallDialog *createBallDialog;
	CreateCylinderDialog *createCylinderDialog;
        ClusterColorDialog *clusterColorDialog;

    QLabel *statusBarSpacerLabel;
	CameraPropertyDialog *cameraPropertyDialog;
	SceneManagerDialog *sceneManagerDialog;
	ColorPickerDialog *colorPickerDialog;
	
	DatasetLoader *datasetLoaderDialog;
	DownSampler *downSamplerDialog;
        StreamlineGenerator *streamlineGeneratorDialog;
        VectorFieldAbstractor *vectorFieldAbstractor;
        FeatureDetector *featureDetectorDialog;
        DrawIllustrative *drawIllustrativeDialog;
        AutoSeedingDialog *autoSeedingDialog;

public slots:
	void exitTriggered ( bool checked = false );
	void onScreenshotClicked();
	void updatess();
	
private slots:
	void onScreenshot();
	void perspectiveCameraOnTrigger();
	void leftCameraOnTrigger();
	void rightCameraOnTrigger();
	void frontCameraOnTrigger();
	void backCameraOnTrigger();
	void topCameraOnTrigger();
	void bottomCameraOnTrigger();
	void onCreatePerspectiveCamera();
	void onCreateOrthogonalCamera();
	void onCreateCameraFromView();
	void onCreatePerspectiveCameraWithOption();
	void onCreateOrthogonalCameraWithOption();
	void onUserCameraAdded(int);
	void onSwitchUserCamera(QAction*);
	void onSaveCameraClicked();
	void onLoadCameraClicked();

public:
	MainWindow(void);
	~MainWindow(void);
};
