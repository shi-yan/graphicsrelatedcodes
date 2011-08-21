#pragma once
#include "DockWidget.h"
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>
#include <QtGui/QComboBox>

class CreateCameraDialog:public DockWidget
{
	Q_OBJECT
public:

    QWidget *dockWidgetContents;
    QGridLayout *gridLayout;
    QLabel *nameLabel;
    QLineEdit *cameraNameLineEdit;
    QLabel *nearPlaneLabel;
    QDoubleSpinBox *nearPlaneDoubleSpinBox;
    QLabel *fromLabel;
    QDoubleSpinBox *farPlaneDoubleSpinBox;
    QLabel *farPlaneLabel;
    QLabel *fromXLabel;
    QLabel *fromYLabel;
    QLabel *fromZLabel;
    QLabel *toLabel;
    QLabel *toXLabel;
    QLabel *toYLabel;
    QLabel *toZLabel;
    QPushButton *createPushButton;
    QSpacerItem *verticalSpacer;
    QDoubleSpinBox *fromXDoubleSpinBox;
    QDoubleSpinBox *fromYDoubleSpinBox;
    QDoubleSpinBox *fromZDoubleSpinBox;
    QDoubleSpinBox *toXDoubleSpinBox;
    QDoubleSpinBox *toYDoubleSpinBox;
    QDoubleSpinBox *toZDoubleSpinBox;
	    
	QLabel *fovLabel;    
	QDoubleSpinBox *fovDoubleSpinBox;

	QLabel *cameraTypeLabel;
    QComboBox *cameraTypeComboBox;
public:
	CreateCameraDialog(QString &title,QWidget *parent=0);
	~CreateCameraDialog(void);

	public slots:
		void onCreateCamera();


};
