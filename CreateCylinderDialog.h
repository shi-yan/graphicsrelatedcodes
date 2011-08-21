#pragma once

#include "DockWidget.h"


#include <QtGui/QApplication>
#include <QtGui/QComboBox>
#include <QtGui/QDockWidget>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

class CreateCylinderDialog:public DockWidget
{

	Q_OBJECT
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *axisTypeLabel;
    QComboBox *axisTypeComboBox;
    QLabel *xLabel;
    QDoubleSpinBox *xDoubleSpinBox;
    QLabel *yLabel;
    QDoubleSpinBox *yDoubleSpinBox;
    QLabel *zLabel;
    QDoubleSpinBox *zDoubleSpinBox;
    QLabel *radiusLabel;
    QLabel *heightLabel;
    QDoubleSpinBox *radiusDoubleSpinBox;
    QDoubleSpinBox *heightDoubleSpinBox;
    QLabel *longitudeSegmentLabel;
    QLabel *radiusSegmentLabel;
    QLabel *heightSegmentLabel;
    QSpinBox *longitudeSpinBox;
    QSpinBox *radiusSpinBox;
    QSpinBox *heightSpinBox;
    QPushButton *applyPushButton;
    QSpacerItem *verticalSpacer;

public:
	CreateCylinderDialog(QString &title,QWidget *parent=0);
	~CreateCylinderDialog(void);
};
