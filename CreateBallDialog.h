#pragma once

#include "DockWidget.h"

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDockWidget>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>


class CreateBallDialog:public DockWidget
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
    QDoubleSpinBox *radiusDoubleSpinBox;
    QSpinBox *longitudeSegmentSpinBox;
    QLabel *longitudeSegmentLabel;
    QLabel *latitudeSegmentLabel;
    QSpinBox *latitudeSegmentSpinBox;
    QPushButton *applyPushButton;
    QSpacerItem *verticalSpacer;
public:
	CreateBallDialog(QString &title,QWidget *parent=0);
	~CreateBallDialog(void);
};
